
#ifndef _GRAPHICS_
#define _GRAPHICS_

#include "base.h"
#include "madmath.h"


typedef struct {
	Vec3 position;
	Color normal;
	Vec2 tex_coord;
	Color color;
} GFX_Vertex;

#define GFX_VERTEX_SIZE   (sizeof(GFX_Vertex))

typedef enum {
	GFX_BUFFER_INDEX_TYPE_16,
	GFX_BUFFER_INDEX_TYPE_32,
} GFX_BufferIndexType;

typedef struct {

	// Vertices
	GFX_Vertex *vertices;
	u32 vertices_count;
	u32 vertices_cap;
	GLuint VBO;

	GFX_BufferIndexType index_type;
	
	// Indices
	void *indices;
	u32	indices_count;
	u32 indices_cap;
	GLuint EBO;

} GFX_Buffer;


// Setups the basic renderer, it will allow you to draw various types of figures,
// moreover, is possible that other kinds of renderer are dependant of this.
// To clean the resources GFX_Deinit has to be called.
int
GFX_Init(void);

// Cleans all the resources used by the renderer.
void
GFX_Deinit(void);

void
GFX_Begin(void);

void
GFX_End(void);

int
GFX_Create_buffer(GFX_Buffer *buffer_out, void *vertices_mem, u32 vertices_mem_size, void *indices_mem, u32 indices_mem_size, GFX_BufferIndexType);

void
GFX_Destroy_buffer(GFX_Buffer *buffer);

void
GFX_Clear_buffer_data(GFX_Buffer *buffer);

void
GFX_Upload_buffer_to_gpu(GFX_Buffer *buffer);

GFX_Vertex *
GFX_Alloc_vertices(GFX_Buffer *buffer, u32 count, u32 *base_index);

void *
GFX_Alloc_indices(GFX_Buffer *buffer, u32 count);

u32
GFX_Get_remaining_vertices(GFX_Buffer *buffer);

u32
GFX_Get_remaining_indices(GFX_Buffer *buffer);

void
GFX_Draw_buffer(GFX_Buffer *buffer);

// Sets the 4x4 matrix to apply over each vertex position on the shader NOTE that this call will
// flush the buffer with the previus matrix values
void
GFX_Set_matrix(Mat4 matrix);

// Gets the current matrix
Mat4
GFX_Get_matrix(void);

void
GFX_Set_light_dir(Vec3 light_dir);

GLuint
GFX_Default_texture(void);

// Sets the current texture to be used. NOTE that if the render was currently drawing something
// with texture, it will be flushed.
void
GFX_Set_texture(GLuint texture);

// Gets the current texture
GLuint
GFX_Get_texture(void);

void
GFX_Flush(void);

static inline void
GFX_Draw_triangle_ex(Vec3 v0, Vec3 v1, Vec3 v2, Color n0, Color n1, Color n2, Vec2 uv0, Vec2 uv1,
		Vec2 uv2, Color c0, Color c1, Color c2);

static inline void
GFX_Draw_quad_ex(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color n0, Color n1, Color n2, Color n3,
		Vec2 uv0, Vec2 uv1, Vec2 uv2, Vec2 uv3, Color c0, Color c1, Color c2, Color c3);

void
GFX_Draw_quad(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 v3, Color color);

void
GFX_Draw_rect(Vec2 pos, f32 width, f32 height, Color color);

void
GFX_Draw_triangle(Vec2 v0, Vec2 v1, Vec2 v2, Color color);

void
GFX_Draw_line(Vec2 src, Vec2 dst, f32 thickness, Color color);

void
GFX_Draw_textured_quad(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 v3, Vec2 uv0, Vec2 uv1, Vec2 uv2, Vec2 uv3, Color color);

void
GFX_Draw_textured_triangle(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 uv0, Vec2 uv1, Vec2 uv2, Color color);

void
GFX_Draw_circle(Vec2 pos, f32 radius, Color color);

void
GFX_Draw_triangle_3D(Vec3 v0, Vec3 v1, Vec3 v2, Color color);

void
GFX_Draw_quad_3D(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color color);

void
GFX_Draw_cube(Vec3 pos, float width, float height, float length, Color color);

void
GFX_Draw_cylinder(Vec3 pos, float up_radius, float down_radius, float length, Color color);

void
GFX_Draw_sphere(Vec3 pos, float radius, Color color);

void
GFX_Draw_torus(Vec3 pos, float radius0, float radius1, Color color);





///////////////////////////////////////////////////////////////////////////////////////
//
//
//                              IMPLEMENTATION STARTS
//
//
///////////////////////////////////////////////////////////////////////////////////////






// 64K vertices and indices
#define VERTICES_BUFFER_MAX_SIZE_BYTES (GFX_VERTEX_SIZE*64*1024)
#define INDICES_BUFFER_MAX_SIZE_BYTES (2*64*1024)


#define MAX_BUFFER_VERTICES  (VERTICES_BUFFER_MAX_SIZE_BYTES/GFX_VERTEX_SIZE)


// 
// All the internal data used by the renderer
//
static struct {

    Mat4 matrix; // Current matrix that will be send to the shader
	Vec3 light_dir;
	GLuint texture;

	u8 vertices_mem[VERTICES_BUFFER_MAX_SIZE_BYTES];
	u8 indices_mem[INDICES_BUFFER_MAX_SIZE_BYTES];
	
	GFX_Buffer buffer;


	// Shader used to draw the triangles
	struct {
		GLuint id;
		GLint position;
		GLint normal;
		GLint tex_coord;
		GLint color;
		GLint vmat;
		GLint texture;
		GLint light_dir;
	} default_shader;

	GLuint default_texture;

} GFX__data = {0};


// Makes a shader from a string (Documented above)
int
Make_shader_from_string(GLuint *shader_result, const char *shader_source, GLenum shader_type) {
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	GLint shader_compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
	if (shader_compiled != GL_TRUE){
		GLsizei log_length = 0;
		static GLchar message[1024];
		glGetShaderInfoLog(shader, 1024, &log_length, message);
		fprintf(stderr, "--- SHADER --- \n\n'%s'\\n compilation error:\n%.*s\n", shader_source, log_length, message);
		return -1;
	}

	*shader_result = shader;
	return 0;
}


// Makes a shader program from 2 shader strings (Documented above)
int
Make_program_from_strings(GLuint *program, const char *vertex_shader_source, const char *fragment_shader_source) {
	GLuint vertex_shader;
	if (Make_shader_from_string(&vertex_shader, vertex_shader_source, GL_VERTEX_SHADER) != 0) {
		return -1;
	}
	GLuint fragment_shader;
	if (Make_shader_from_string(&fragment_shader, fragment_shader_source, GL_FRAGMENT_SHADER) != 0) {
		return -1;
	}

	GLuint shader_program  = glCreateProgram();      // create program object
	glAttachShader(shader_program, vertex_shader);   // and attach both...
	glAttachShader(shader_program, fragment_shader); // ... shaders to it

	glLinkProgram(shader_program);   // link the program

	// We can delete de shaders here
	glDetachShader(shader_program, vertex_shader);
	glDeleteShader(vertex_shader);
	glDetachShader(shader_program, fragment_shader);
	glDeleteShader(fragment_shader);

	*program = shader_program;
	return 0;
}



typedef enum {
	LOC_TYPE_ATTRIB,
	LOC_TYPE_UNIFORM,
} LocationType;

bool
Program_get_location(GLint *result, GLuint program_id, LocationType location_type, const char *location_name) {
	if (location_type == LOC_TYPE_ATTRIB) {
		GLint loc = glGetAttribLocation(program_id, location_name);
		if (loc < 0) {
			fprintf(stderr, "Unable to get '%s' attrib location\n", location_name);
			return false;
		}
		else {
			*result = loc;
			return true;
		}
	}
	else if (location_type == LOC_TYPE_UNIFORM) {
		GLint loc = glGetUniformLocation(program_id, location_name);
		if (loc < 0) {
			fprintf(stderr, "Unable to get '%s' uniform location\n", location_name);
			return false;
		}
		else {
			*result = loc;
			return true;
		}
	}
	return false;
}


// Documented above
int
GFX_Init(void) {

	GFX_Create_buffer(
		&GFX__data.buffer,
		GFX__data.vertices_mem,
		VERTICES_BUFFER_MAX_SIZE_BYTES,
		GFX__data.indices_mem,
		INDICES_BUFFER_MAX_SIZE_BYTES,
		GFX_BUFFER_INDEX_TYPE_16);

	//
	//
	// ALL THIS FOR TEXTURED TRIANGLES
	//
	//

	if (0 != Make_program_from_strings(
			&GFX__data.default_shader.id,

			// Vertex shader
			"#version 100\n"
			
			"uniform mat4 vmat;\n"
			
			"attribute vec3 position;\n"
			"attribute vec4 normal;\n"
			"attribute vec2 tex_coord;\n"
			"attribute mediump vec4 color;\n"
			
			"varying mediump vec2 pixel_uv;\n"
			"varying mediump vec3 pixel_normal;\n"
			"varying mediump vec4 pixel_color;\n"
			
			"void main()\n"
			"{\n"
				"gl_Position = vec4(position, 1.0) * vmat;\n"
				"pixel_uv    = tex_coord;\n"
				"pixel_normal= normalize(normal.xyz*2.0-vec3(1,1,1));\n"
				"pixel_color = color;\n"
			"}\n",

			// Fragment shader
			"#version 100\n"
			
			"varying mediump vec2 pixel_uv;\n"
			"varying mediump vec3 pixel_normal;\n"
			"varying mediump vec4 pixel_color;\n"
			"uniform sampler2D texture;\n"
			"uniform mediump vec3 light_dir;\n"
			
			"void main()\n"
			"{\n"
				"mediump float intensity = max(-dot(light_dir, normalize(pixel_normal)), 0.3);\n"
				"mediump vec4  tex_color = texture2D(texture, pixel_uv);\n"
				"gl_FragColor = tex_color * pixel_color * vec4(vec3(intensity), 1.0);\n"
			"}\n"

			)) goto render_setup_error;


	glUseProgram(GFX__data.default_shader.id);

	{ // Populate all the shader locations
		GLuint prog_id = GFX__data.default_shader.id;

		if (!Program_get_location(&GFX__data.default_shader.position, prog_id, LOC_TYPE_ATTRIB, "position"))
			goto render_setup_error;
		if (!Program_get_location(&GFX__data.default_shader.normal, prog_id, LOC_TYPE_ATTRIB, "normal"))
			goto render_setup_error;
		if (!Program_get_location(&GFX__data.default_shader.tex_coord, prog_id, LOC_TYPE_ATTRIB, "tex_coord"))
			goto render_setup_error;
		if (!Program_get_location(&GFX__data.default_shader.color, prog_id, LOC_TYPE_ATTRIB, "color"))
			goto render_setup_error;
		if (!Program_get_location(&GFX__data.default_shader.vmat, prog_id, LOC_TYPE_UNIFORM, "vmat"))
			goto render_setup_error;
		if (!Program_get_location(&GFX__data.default_shader.light_dir, prog_id, LOC_TYPE_UNIFORM, "light_dir"))
			goto render_setup_error;
		if (!Program_get_location(&GFX__data.default_shader.texture, prog_id, LOC_TYPE_UNIFORM, "texture"))
			goto render_setup_error;
	}

	static u8 default_texture[] = {
		0xFF, 0xFF, 0xFF, 0xFF,   0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF,   0xFF, 0xFF, 0xFF, 0xFF
	};

	// Generates the default texture
	glGenTextures(1, &GFX__data.default_texture);
    glBindTexture(GL_TEXTURE_2D, GFX__data.default_texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, default_texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GFX__data.texture = GFX__data.default_texture;

    GFX_Set_matrix(M4_Diagonal(1.0f));
	GFX_Set_light_dir(V3(0, 0, -1));

	return 0;
	
	render_setup_error:
		GFX_Deinit();
		return -1;
}

// Documented above
void
GFX_Deinit(void) {
	// Clean the shader program
	glDeleteProgram(GFX__data.default_shader.id);
	// Clean VBO
	GFX_Destroy_buffer(&GFX__data.buffer);
	glDeleteTextures(1, &GFX__data.default_texture);
	memset(&GFX__data, 0, sizeof(GFX__data));
}



// Documented above
void
GFX_Flush(void) {
	GFX_Upload_buffer_to_gpu(&GFX__data.buffer);
	GFX_Draw_buffer(&GFX__data.buffer);
	GFX_Clear_buffer_data(&GFX__data.buffer);
}



void
GFX_Begin(void) {
	glUseProgram(GFX__data.default_shader.id);

	glActiveTexture(GL_TEXTURE0);
    glUniform1i(GFX__data.default_shader.texture, 0);
	glBindTexture(GL_TEXTURE_2D, GFX__data.texture);

	glUniform3f(GFX__data.default_shader.light_dir, 0.0f, 0.0f, -1.0f);
}



void
GFX_End(void) {
	GFX_Flush();
}


int
GFX_Create_buffer(GFX_Buffer *buffer_out, void *vertices_mem, u32 vertices_mem_size, void *indices_mem, u32 indices_mem_size, GFX_BufferIndexType index_type) {
	GFX_Buffer result = {0};
	GLuint buffer_objects[2];
	glGenBuffers(2, buffer_objects);
	result.VBO = buffer_objects[0];
	result.EBO = buffer_objects[1];

	glBindBuffer(GL_ARRAY_BUFFER, result.VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_mem_size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_mem_size, NULL, GL_DYNAMIC_DRAW);

	result.vertices       = vertices_mem;
	result.vertices_cap   = vertices_mem_size / GFX_VERTEX_SIZE;
	result.vertices_count = 0;

	result.indices       = indices_mem;
	if (index_type == GFX_BUFFER_INDEX_TYPE_16) {
		result.indices_cap   = indices_mem_size / 2;
	}
	else {
		result.indices_cap   = indices_mem_size / 4;
	}

	result.indices_count = 0;

	result.index_type = index_type;

	*buffer_out = result;

	return 0;
}

void
GFX_Destroy_buffer(GFX_Buffer *buffer) {
	GLuint buffer_objects[] = {buffer->VBO, buffer->EBO};
	glDeleteBuffers(0, buffer_objects);
	*buffer = (GFX_Buffer){0};
}


void
GFX_Clear_buffer_data(GFX_Buffer *buffer) {
	buffer->vertices_count  = 0;
	buffer->indices_count = 0;
}

void
GFX_Upload_buffer_to_gpu(GFX_Buffer *buffer) {

	u32 bytes_of_vertices  = GFX_VERTEX_SIZE * buffer->vertices_count;
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, bytes_of_vertices, buffer->vertices);
	u32 bytes_of_indices;
	if (buffer->index_type == GFX_BUFFER_INDEX_TYPE_16) {
		bytes_of_indices = 2 * buffer->indices_count;
	}
	else {
		bytes_of_indices = 4 * buffer->indices_count;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, bytes_of_indices, buffer->indices);

}


GFX_Vertex *
GFX_Alloc_vertices(GFX_Buffer *buffer, u32 count, u32 *base_index) {
	if ((buffer->vertices_cap - buffer->vertices_count) < count) return NULL;
	GFX_Vertex *result = &buffer->vertices[buffer->vertices_count];
	if (base_index) *base_index = buffer->vertices_count;
	buffer->vertices_count += count;
	return result;
}

void *
GFX_Alloc_indices(GFX_Buffer *buffer, u32 count) {
	if (buffer->indices_cap - buffer->indices_count < count) return NULL;
	void *result;
	if (buffer->index_type == GFX_BUFFER_INDEX_TYPE_16) {
		u16 *indices16 = (u16 *)buffer->indices;
		result = &indices16[buffer->indices_count];
	}
	else {
		u32 *indices32 = (u32 *)buffer->indices;
		result = &indices32[buffer->indices_count];
	}

	buffer->indices_count += count;

	return result;
}


u32
GFX_Get_remaining_vertices(GFX_Buffer *buffer) {
	return buffer->vertices_cap - buffer->vertices_count;
}


u32
GFX_Get_remaining_indices(GFX_Buffer *buffer) {
	return buffer->indices_cap - buffer->indices_count;
}


void
GFX_Draw_buffer(GFX_Buffer *buffer) {
	glBindBuffer(GL_ARRAY_BUFFER, buffer->VBO);
	unsigned int stride = 3*4 + 4 + 2*4 + 4; // 3 floats + 4 bytes + 2 floats + 4 bytes
    glEnableVertexAttribArray(GFX__data.default_shader.position);
	glVertexAttribPointer(GFX__data.default_shader.position, 3, GL_FLOAT, false, stride, (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(GFX__data.default_shader.normal);
	glVertexAttribPointer(GFX__data.default_shader.normal, 3, GL_UNSIGNED_BYTE, true, stride, (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(GFX__data.default_shader.tex_coord);
	glVertexAttribPointer(GFX__data.default_shader.tex_coord, 2, GL_FLOAT, false, stride, (void*)(4*sizeof(float)));
    glEnableVertexAttribArray(GFX__data.default_shader.color);
	glVertexAttribPointer(GFX__data.default_shader.color, 4, GL_UNSIGNED_BYTE, true, stride, (void*)(6*sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->EBO);
	GLenum index_type = (buffer->index_type == GFX_BUFFER_INDEX_TYPE_16) ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
	glDrawElements(GL_TRIANGLES, buffer->indices_count, index_type, 0);
}


GLuint
GFX_Default_texture(void) {
	return GFX__data.default_texture;
}

// Doc above
void
GFX_Set_texture(GLuint texture) {
	if (GFX__data.texture != texture) {
		GFX_Flush();
		GFX__data.texture = texture;
		glBindTexture(GL_TEXTURE_2D, GFX__data.texture);
	}
}


// Doc above
GLuint
GFX_Get_texture(void) {
	return GFX__data.texture;
}


//Documented above
void
GFX_Set_matrix(Mat4 matrix) {
	GFX_Flush();
    GFX__data.matrix = matrix;
    glUniformMatrix4fv(GFX__data.default_shader.vmat, 1, GL_FALSE, (GLfloat *)&GFX__data.matrix);
}


//Documented above
Mat4
GFX_Get_matrix(void) {
    return GFX__data.matrix;
}

//Documented above
void
GFX_Set_light_dir(Vec3 light_dir) {
	GFX_Flush();
	glUniform3f(GFX__data.default_shader.light_dir, light_dir.x, light_dir.y, light_dir.z);
    GFX__data.light_dir = light_dir;
}



static inline void
GFX_Draw_triangle_ex(Vec3 v0, Vec3 v1, Vec3 v2, Color n0, Color n1, Color n2, Vec2 uv0, Vec2 uv1, Vec2 uv2, Color c0, Color c1, Color c2) {

	if (GFX_Get_remaining_vertices(&GFX__data.buffer) < 3 || GFX_Get_remaining_indices(&GFX__data.buffer) < 3) GFX_Flush();

	u32 base_index;
	GFX_Vertex *verts = GFX_Alloc_vertices(&GFX__data.buffer, 3, &base_index);

	verts[0].position  = v0;
	verts[0].normal    = n0;
	verts[0].tex_coord = uv0;
	verts[0].color     = c0;

	verts[1].position  = v1;
	verts[1].normal    = n1;
	verts[1].tex_coord = uv1;
	verts[1].color     = c1;

	verts[2].position  = v2;
	verts[2].normal    = n2;
	verts[2].tex_coord = uv2;
	verts[2].color     = c2;

	u16 *indices = (u16 *)GFX_Alloc_indices(&GFX__data.buffer, 3);
	indices[0] = (u16)base_index+0;
	indices[1] = (u16)base_index+1;
	indices[2] = (u16)base_index+2;
}


static inline void
GFX_Draw_quad_ex(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color n0, Color n1, Color n2, Color n3, Vec2 uv0, Vec2 uv1, Vec2 uv2, Vec2 uv3, Color c0, Color c1, Color c2, Color c3) {
	
	if (GFX_Get_remaining_vertices(&GFX__data.buffer) < 4 || GFX_Get_remaining_indices(&GFX__data.buffer) < 6) GFX_Flush();

	u32 base_index;
	GFX_Vertex *verts = GFX_Alloc_vertices(&GFX__data.buffer, 4, &base_index);

	verts[0].position  = v0;
	verts[0].normal    = n0;
	verts[0].tex_coord = uv0;
	verts[0].color     = c0;

	verts[1].position  = v1;
	verts[1].normal    = n1;
	verts[1].tex_coord = uv1;
	verts[1].color     = c1;

	verts[2].position  = v2;
	verts[2].normal    = n2;
	verts[2].tex_coord = uv2;
	verts[2].color     = c2;

	verts[3].position  = v3;
	verts[3].normal    = n3;
	verts[3].tex_coord = uv3;
	verts[3].color     = c3;

	u16 *indices = (u16 *)GFX_Alloc_indices(&GFX__data.buffer, 6);
	indices[0] = (u16)base_index+0;
	indices[1] = (u16)base_index+1;
	indices[2] = (u16)base_index+2;
	indices[3] = (u16)base_index+0;
	indices[4] = (u16)base_index+2;
	indices[5] = (u16)base_index+3;

}



// Documented above
void
GFX_Draw_triangle(Vec2 v0, Vec2 v1, Vec2 v2, Color color) {
	GFX_Draw_triangle_ex(
		V3(v0.x, v0.y, 0),
		V3(v1.x, v1.y, 0),
		V3(v2.x, v2.y, 0),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		V2(0, 0),
		V2(1, 0),
		V2(1, 1),
		color,
		color,
		color
	);
}

void
GFX_Draw_textured_triangle(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 uv0, Vec2 uv1, Vec2 uv2, Color color) {
	GFX_Draw_triangle_ex(
		V3(v0.x, v0.y, 0),
		V3(v1.x, v1.y, 0),
		V3(v2.x, v2.y, 0),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		uv0,
		uv1,
		uv2,
		color,
		color,
		color
	);
}

// Documented above
void
GFX_Draw_quad(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 v3, Color color) {
	GFX_Draw_quad_ex(
		V3(v0.x, v0.y, 0),
		V3(v1.x, v1.y, 0),
		V3(v2.x, v2.y, 0),
		V3(v3.x, v3.y, 0),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		V4_To_Color(V4(0, 0, 1, 0)),
		V2(0, 0),
		V2(1, 0),
		V2(1, 1),
		V2(0, 1),
		color,
		color,
		color,
		color
	);
}

// Documented above
void
GFX_Draw_line(Vec2 src, Vec2 dst, f32 thickness, Color color) {
	
	Vec2 norm_dir = V2_Normalize(V2_Sub(dst, src));

	f32 thick_half = thickness * 0.5f;
	Vec2 up   = V2_Mulf(V2(-norm_dir.y, norm_dir.x), thick_half);
	Vec2 down = V2_Mulf(V2(norm_dir.y, -norm_dir.x), thick_half);

	Vec2 v0 = V2_Add(src, up);
	Vec2 v1 = V2_Add(src, down);
	Vec2 v2 = V2_Add(dst, down);
	Vec2 v3 = V2_Add(dst, up);
	GFX_Draw_quad(v0, v1, v2, v3, color);
}

// Documented above
void
GFX_Draw_rect(Vec2 pos, f32 width, f32 height, Color color) {
	GFX_Draw_quad(
		pos,
		V2(pos.x + width, pos.y),
		V2(pos.x + width, pos.y + height),
		V2(pos.x,         pos.y + height),
		color);
}




// Documented above
void
GFX_Draw_textured_quad(Vec2 v0, Vec2 v1, Vec2 v2, Vec2 v3, Vec2 uv0, Vec2 uv1, Vec2 uv2, Vec2 uv3, Color color) {
	Vec3 v3_0 = V3(v0.x, v0.y, 0);
	Vec3 v3_1 = V3(v1.x, v0.y, 0);
	Vec3 v3_2 = V3(v2.x, v2.y, 0);
	Vec3 v3_3 = V3(v3.x, v3.y, 0);
	Color n = V4_To_Color(V4(0, 0, 1, 0));
	Color c = color;
	GFX_Draw_quad_ex(v3_0, v3_1, v3_2, v3_3, n, n, n, n, uv0, uv1, uv2, uv3, c, c, c, c);
}



void
GFX_Draw_circle(Vec2 center, f32 radius, Color color) {
	static const int SUBDIVISIONS = 30;
	f32 theta = 2*PI32/(f32)SUBDIVISIONS;
	f32 cos_theta = Cos(theta);
	f32 sin_theta = Sin(theta);

	Vec2 p0 = V2(radius, 0);
	for (int i = 0; i <= SUBDIVISIONS; ++i) {
		Vec2 p1 = V2(p0.x * cos_theta - p0.y * sin_theta, p0.x * sin_theta + p0.y * cos_theta);
		GFX_Draw_triangle(center, V2_Add(center, p0), V2_Add(center, p1), color);
		p0 = p1;
	}
}


void
GFX_Draw_triangle_3D(Vec3 v0, Vec3 v1, Vec3 v2, Color color) {
	Vec3 n = V3_Cross3(v0, v1, v2);
	n = V3(n.x, -n.y, n.z); // FIXME(Tano) Why is the y inverteeeeed
	Color nc = V4_To_Color((Vec4){.xyz = n});
	GFX_Draw_triangle_ex(v0, v1, v2, nc, nc, nc, V2(0, 0), V2(1, 0), V2(1, 1), color, color, color);
}


void
GFX_Draw_quad_3D(Vec3 v0, Vec3 v1, Vec3 v2, Vec3 v3, Color color) {
	GFX_Draw_triangle_3D(v0, v1, v2, color);
	GFX_Draw_triangle_3D(v0, v2, v3, color);
}

void
GFX_Draw_cube(Vec3 pos, float width, float height, float length, Color color) {

		Vec3 corner_front_bottom_left  = V3_Add(V3(-0.5f * width, -0.5f * height,  0.5f * length), pos);
		Vec3 corner_front_bottom_right = V3_Add(V3( 0.5f * width, -0.5f * height,  0.5f * length), pos);
		Vec3 corner_front_up_right     = V3_Add(V3( 0.5f * width,  0.5f * height,  0.5f * length), pos);
		Vec3 corner_front_up_left      = V3_Add(V3(-0.5f * width,  0.5f * height,  0.5f * length), pos);
		Vec3 corner_back_bottom_left   = V3_Add(V3(-0.5f * width, -0.5f * height, -0.5f * length), pos);
		Vec3 corner_back_bottom_right  = V3_Add(V3( 0.5f * width, -0.5f * height, -0.5f * length), pos);
		Vec3 corner_back_up_right      = V3_Add(V3( 0.5f * width,  0.5f * height, -0.5f * length), pos);
		Vec3 corner_back_up_left       = V3_Add(V3(-0.5f * width,  0.5f * height, -0.5f * length), pos);

		Color normal_front = V4_To_Color(V4( 0,  0,  1,  0));
		Color normal_back  = V4_To_Color(V4( 0,  0, -1,  0));
		Color normal_up    = V4_To_Color(V4( 0,  1,  0,  0));
		Color normal_down  = V4_To_Color(V4( 0, -1,  0,  0));
		Color normal_left  = V4_To_Color(V4(-1,  0,  0,  0));
		Color normal_right = V4_To_Color(V4( 1,  0,  0,  0));

		GFX_Draw_quad_ex(
				corner_front_bottom_left,
				corner_front_bottom_right,
				corner_front_up_right,
				corner_front_up_left,
				normal_front, normal_front, normal_front, normal_front,
				V2(1, 1), V2(0, 1), V2(0, 0), V2(1, 0),
				color, color, color, color);

		GFX_Draw_quad_ex(
				corner_front_bottom_right,
				corner_back_bottom_right,
				corner_back_up_right,
				corner_front_up_right,
				normal_right, normal_right, normal_right, normal_right,
				V2(1, 1), V2(0, 1), V2(0, 0), V2(1, 0),
				color, color, color, color);
		
		GFX_Draw_quad_ex(
				corner_back_bottom_right,
				corner_back_bottom_left,
				corner_back_up_left,
				corner_back_up_right,
				normal_back, normal_back, normal_back, normal_back,
				V2(1, 1), V2(0, 1), V2(0, 0), V2(1, 0),
				color, color, color, color);

		GFX_Draw_quad_ex(
				corner_back_bottom_left,
				corner_front_bottom_left,
				corner_front_up_left,
				corner_back_up_left,
				normal_left, normal_left, normal_left, normal_left,
				V2(1, 1), V2(0, 1), V2(0, 0), V2(1, 0),
				color, color, color, color);

		GFX_Draw_quad_ex(
				corner_front_up_left,
				corner_front_up_right,
				corner_back_up_right,
				corner_back_up_left,
				normal_up, normal_up, normal_up, normal_up,
				V2(1, 1), V2(0, 1), V2(0, 0), V2(1, 0),
				color, color, color, color);

		GFX_Draw_quad_ex(
				corner_front_bottom_right,
				corner_front_bottom_left,
				corner_back_bottom_left,
				corner_back_bottom_right,
				normal_down, normal_down, normal_down, normal_down,
				V2(1, 1), V2(0, 1), V2(0, 0), V2(1, 0),
				color, color, color, color);
}


void
GFX_Draw_cylinder(Vec3 pos, float up_radius, float down_radius, float length, Color color) {
	int SUBDIVISIONS = 40;
	f32 theta = 2*PI32/(f32)SUBDIVISIONS;
	f32 cos_theta = Cos(theta);
	f32 sin_theta = Sin(theta);
	
	Vec3 up_center   = V3_Add(pos, V3(0,  0.5f * length, 0));
	Vec3 down_center = V3_Add(pos, V3(0, -0.5f * length, 0));
	
	f32 slope = (down_radius - up_radius) / length;

	Color normal_up   = V4_To_Color(V4(0,  1, 0, 0));
	Color normal_down = V4_To_Color(V4(0, -1, 0, 0));

	Vec3 p0 = V3(1, 0, 0);
	Color n0 = V4_To_Color(V4(p0.x, slope, p0.z, 0));
	Vec3 up0   = V3_Add(up_center, V3_Mulf(p0, up_radius));
	Vec3 down0 = V3_Add(down_center, V3_Mulf(p0, down_radius));
	for (int i = 1; i <= SUBDIVISIONS; ++i) {
		Vec3 p1 = V3(0, 0, 0);
		p1.x = p0.x * cos_theta - p0.z * sin_theta;
		p1.z = p0.x * sin_theta + p0.z * cos_theta;

		Color n1   = V4_To_Color(V4(p1.x, slope, p1.z, 0));
		Vec3 up1   = V3_Add(up_center, V3_Mulf(p1, up_radius));
		Vec3 down1 = V3_Add(down_center, V3_Mulf(p1, down_radius));
		
		Vec2 cap_uv0 = V2(0.5f, 0.5f);
		Vec2 cap_uv1; {
			float m = 0.5f/Max(Abs(p0.x), Abs(p0.z));
			cap_uv1 = V2(p0.x*m+0.5f, p0.z*m+0.5f);
		}
		Vec2 cap_uv2; {
			float m = 0.5f/Max(Abs(p1.x), Abs(p1.z));
			cap_uv2 = V2(p1.x*m+0.5f, p1.z*m+0.5f);
		}
		
		GFX_Draw_triangle_ex(
				up_center, up1, up0,
				normal_up, normal_up, normal_up,
				cap_uv0, cap_uv2, cap_uv1,
				color, color, color);

		Vec2 uv0 = V2((float)(i)/(f32)SUBDIVISIONS, 1);
		Vec2 uv1 = V2((float)(i-1)/(f32)SUBDIVISIONS, 1);
		Vec2 uv2 = V2((float)(i-1)/(f32)SUBDIVISIONS, 0);
		Vec2 uv3 = V2((float)(i)/(f32)SUBDIVISIONS, 0);
		GFX_Draw_quad_ex(down1, down0, up0, up1, n1, n0, n0, n1, uv0, uv1, uv2, uv3, color, color, color, color);
		//GFX_Draw_quad_3D(down1, down0, up0, up1, color);

		GFX_Draw_triangle_ex(
				down_center, down0, down1,
				normal_down, normal_down, normal_down,
				cap_uv0, cap_uv1, cap_uv2,
				color, color, color);

		p0 = p1;
		n0 = n1;
		up0 = up1;
		down0 = down1;
	}
}

void
GFX_Draw_sphere(Vec3 pos, float radius, Color color) {
	int SUBDIVISIONS0 = 20;
	int SUBDIVISIONS1 = 40;
	f32 theta0 = PI32/(f32)SUBDIVISIONS0;
	f32 theta1 = 2*PI32/(f32)SUBDIVISIONS1;
	f32 cos_theta0 = Cos(theta0);
	f32 sin_theta0 = Sin(theta0);
	f32 cos_theta1 = Cos(theta1);
	f32 sin_theta1 = Sin(theta1);
	
	Vec3 half_circle_p0 = V3(0, radius, 0);
	for (int i0 = 1; i0 <= SUBDIVISIONS0; i0+=1) {
		Vec3 half_circle_p1 = V3(0, 0, 0);
		// Rotate around the z axis
		half_circle_p1.x = half_circle_p0.x * cos_theta0 - half_circle_p0.y * sin_theta0;
		half_circle_p1.y = half_circle_p0.x * sin_theta0 + half_circle_p0.y * cos_theta0;

		Vec3 p_up_0   = half_circle_p0;
		Vec3 p_down_0 = half_circle_p1;
		Color n_up_0   = V4_To_Color((Vec4){.xyz=p_up_0});
		Color n_down_0 = V4_To_Color((Vec4){.xyz=p_down_0});

		for (int i1 = 1; i1 <= SUBDIVISIONS1; i1+=1) {
			Vec3 p_down_1 = V3(0, p_down_0.y, 0);
			p_down_1.x = p_down_0.x * cos_theta1 - p_down_0.z * sin_theta1;
			p_down_1.z = p_down_0.x * sin_theta1 + p_down_0.z * cos_theta1;
			Color n_down_1 = V4_To_Color((Vec4){.xyz=p_down_1});

			Vec3 p_up_1   = V3(0, p_up_0.y, 0);
			p_up_1.x = p_up_0.x * cos_theta1 - p_up_0.z * sin_theta1;
			p_up_1.z = p_up_0.x * sin_theta1 + p_up_0.z * cos_theta1;
			Color n_up_1 = V4_To_Color((Vec4){.xyz=p_up_1});

			Vec2 uv0 = V2((float)(i1-1)/SUBDIVISIONS1, (float)(i0-1)/(float)SUBDIVISIONS0);
			Vec2 uv1 = V2((float)(i1)/SUBDIVISIONS1, (float)(i0-1)/(float)SUBDIVISIONS0);
			Vec2 uv2 = V2((float)(i1)/SUBDIVISIONS1, (float)(i0)/(float)SUBDIVISIONS0);
			Vec2 uv3 = V2((float)(i1-1)/SUBDIVISIONS1, (float)(i0)/(float)SUBDIVISIONS0);

			GFX_Draw_quad_ex(
				V3_Add(pos, p_up_0),
				V3_Add(pos, p_up_1),
				V3_Add(pos, p_down_1),
				V3_Add(pos, p_down_0),
				n_up_0, n_up_1, n_down_1, n_down_0,
				uv0, uv1, uv2, uv3, color, color, color, color);
			//GFX_Draw_quad_3D(
			//	V3_Add(p_down_0, pos),
			//	V3_Add(p_down_1, pos),
			//	V3_Add(p_up_1, pos),
			//	V3_Add(p_up_0, pos),
			//	color
			//);
			p_down_0 = p_down_1;
			p_up_0 = p_up_1;
			n_up_0 = n_up_1;
			n_down_0 = n_down_1;
		}

		half_circle_p0 = half_circle_p1;
	}
}

void
GFX_Draw_torus(Vec3 pos, float radius0, float radius1, Color color) {

	int SUBDIVISIONS0 = 20;
	float theta0 = -2*PI32/(float)SUBDIVISIONS0;
	float cos_theta0 = Cos(theta0);
	float sin_theta0 = Sin(theta0);

	int SUBDIVISIONS1 = 40;
	float theta1 = -2*PI32/(float)SUBDIVISIONS1;
	float cos_theta1 = Cos(theta1);
	float sin_theta1 = Sin(theta1);
	
	Vec3 circle_p0 = V3(0, 0, radius0);
	for (int i0 = 1; i0 <= SUBDIVISIONS0; i0+=1) {
		Vec3 circle_p1 = V3(0, 0, 0);
		// Rotate across the z axis
		circle_p1.x = circle_p0.x * cos_theta0 - circle_p0.z * sin_theta0;
		circle_p1.z = circle_p0.x * sin_theta0 + circle_p0.z * cos_theta0;

		Vec3 p_down_0 = V3_Add(V3(radius1, 0, 0), circle_p0);
		Vec3 p_down_1 = V3_Add(V3(radius1, 0, 0), circle_p1);
		Vec3 n_down_0 = circle_p0;
		Vec3 n_down_1 = circle_p1;
		Color nc_down_0 = V4_To_Color((Vec4){.xyz=n_down_0});
		Color nc_down_1 = V4_To_Color((Vec4){.xyz=n_down_1});

		circle_p0 = circle_p1;
		
		for (int i1 = 1; i1 <= SUBDIVISIONS1; i1+=1) {
			Vec3 p_up_0;
			p_up_0.x = p_down_0.x * cos_theta1 - p_down_0.y * sin_theta1;
			p_up_0.y = p_down_0.x * sin_theta1 + p_down_0.y * cos_theta1;
			p_up_0.z = p_down_0.z;

			Vec3 p_up_1;
			p_up_1.x = p_down_1.x * cos_theta1 - p_down_1.y * sin_theta1;
			p_up_1.y = p_down_1.x * sin_theta1 + p_down_1.y * cos_theta1;
			p_up_1.z = p_down_1.z;

			Vec3 n_up_0;
			n_up_0.x = n_down_0.x * cos_theta1 - n_down_0.y * sin_theta1;
			n_up_0.y = n_down_0.x * sin_theta1 + n_down_0.y * cos_theta1;
			n_up_0.z = n_down_0.z;
			Color nc_up_0 = V4_To_Color((Vec4){.xyz=n_up_0});

			Vec3 n_up_1;
			n_up_1.x = n_down_1.x * cos_theta1 - n_down_1.y * sin_theta1;
			n_up_1.y = n_down_1.x * sin_theta1 + n_down_1.y * cos_theta1;
			n_up_1.z = n_down_1.z;
			Color nc_up_1 = V4_To_Color((Vec4){.xyz=n_up_1});

			Vec2 uv0 = V2((float)(i0-1)/SUBDIVISIONS0, (float)(i1-1)/(float)SUBDIVISIONS1);
			Vec2 uv1 = V2((float)(i0-1)/SUBDIVISIONS0, (float)(i1)/(float)SUBDIVISIONS1);
			Vec2 uv2 = V2((float)(i0)/SUBDIVISIONS0, (float)(i1)/(float)SUBDIVISIONS1);
			Vec2 uv3 = V2((float)(i0)/SUBDIVISIONS0, (float)(i1-1)/(float)SUBDIVISIONS1);

			GFX_Draw_quad_ex(
				V3_Add(p_down_0, pos),
				V3_Add(p_up_0, pos),
				V3_Add(p_up_1, pos),
				V3_Add(p_down_1, pos),
				nc_down_0, nc_up_0, nc_up_1, nc_down_1,
				uv0, uv1, uv2, uv3,
				color, color, color, color);
			//GFX_Draw_quad_3D(
			//	V3_Add(p_down_0, pos),
			//	V3_Add(p_up_0, pos),
			//	V3_Add(p_up_1, pos),
			//	V3_Add(p_down_1, pos),
			//	color
			//);
			p_down_0 = p_up_0;
			p_down_1 = p_up_1;
			n_down_0 = n_up_0;
			n_down_1 = n_up_1;
			nc_down_0 = nc_up_0;
			nc_down_1 = nc_up_1;
		}

	}
}


#endif // _GRAPHICS_


