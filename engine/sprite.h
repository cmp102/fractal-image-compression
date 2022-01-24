#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "base.h"
#include "app.h"
#include "graphics.h"
#include "third_party/stb_image.h"




// This defines a group of sprites with the same width/height in the same texture
// this is also used as tileset
typedef struct {
	u32 sprite_width;
	u32 sprite_height;
	GLuint texture_id;
	i32 texture_width;
	i32 texture_height;
} Spriteset;

typedef struct {
    u32 n_layers;
    u32 tiles_x;
    u32 tiles_y;
    f32 scroll_x;
    f32 scroll_y;
	Spriteset *spriteset;
    u32 *tilemap_data;
} Tilemap;



typedef struct {
    const char *name;
    const char *value;
} Attribute;

typedef struct {
    f32 x, y, width, height, rotation, vx, vy, vr;
    const char *name;
    Attribute *attributes;
    u32 attributes_size;
} Object;




/*
* Free_objects
* ===================================================================================
*
* DESCRIPTIION
* -------------------------------------------------------------------------------------
* Frees the memory of the object array
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   obj: Object array
*/
void
Free_objects(Object *obj,  u32 objects_size);


/*
* Load_objects_from_tiled_json
* ===================================================================================
*
* DESCRIPTIION
* -------------------------------------------------------------------------------------
* Loads a object map from tiled
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   filename: file name of the map.
*   set: Texture set
*   set_size: size of the texture set
*   gameplay_height: width of the gamplay y axis
*   objects_size: Pointer to get the size of the result array
*
* RETURNS
* -------------------------------------------------------------------------------------
*   Object*: Array of objects loaded
*/
Object*
Load_objects_from_tiled_json(const char *filename, u32 gameplay_height, u32 *objects_size);




/*
* Make_spriteset
* ===================================================================================
*
* DESCRIPTIION
* -------------------------------------------------------------------------------------
* Creates a spriteset using the image filename passed as parameter.
*
* To release all the spriteset resources we must call Free_spriteset.
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   image_filename: The filename of the image that will be set as texture.
*   tile_width:  Width of each tile in pixels
*   tile_height: Height of each tile in pixels
*   spriteset_result: Pointer to the spriteset to make
*
* RETURNS
* -------------------------------------------------------------------------------------
*   int: If is != 0 The image couldn't be loaded or the tile widths donn't match.
*/
int
Make_spriteset(const char *image_filename, u32 tile_width, u32 tile_height, bool linear_interpolation, Spriteset *spriteset_result);





/*
* Free_spriteset
* ===================================================================================
*
* DESCRIPTIION
* -------------------------------------------------------------------------------------
* Releases all the resources grabbed by the spriteset (Just the texture)
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   spriteset: Spriteset to free
*
*/
void
Free_spriteset(Spriteset *spriteset);









/*
* DESCRIPTIION
* --------------------------------------------------------------------------------------
* Draws the sprite indicated by the sprite_number of the texture. Draws it in a box defined by the
* parameters. Takes into account aspect ratio deformations.
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   x: Position in the X axis in world coordinates
*   y: Position in the Y axis in world coordinates
*   width: Width in world coordinates.
*   heigth: Heigth in world coordinates
*   rotation: Degrees the sprite is rotated. The rotation point its the center of the sprite.
*   texture_id: Id of the texture of the sprite.
*   sprite_width: Width of a single sprite in the original image.
*   sprite_height: Height of a single sprite in the original image.
*   sprite_number: Index of the sprite to draw. Starting by 0. If multiple dimensions, counts left to right, and top to bottom.
*/
void
Draw_sprite(const Spriteset *spriteset, Vec2 pos, f32 width, f32 height, f32 rotation, f32 center_x, f32 center_y, u32 sprite_number, Color color);



/*
* DESCRIPTIION
* -------------------------------------------------------------------------------------
* Makes a tilemap
*
* Note that the tilemap isn't ready to draw, you must call Tilemap_gen_render_data
* to generate the resources needed to be rendered.
*
* The tilemap holds resources that should be released calling Free_tilemap
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   init_x: Most left position of the screen to start drawing.
*   init_y: Most right position of the screen to start drawing.
*   width: Width of a tile in world coordinates.
*   height: Height of a tile in world coordinates.
*   n_layers: The number of layers that will have the tilemap
*   tiles_x: Number of tiles on the x axis. (Width of the tilemap in tiles)
*   tiles_y: Number of tiles on the y axis. (Heigth of the tilemap in tiles)
*
*
* RETURNS
* -------------------------------------------------------------------------------------
*   Tilemap: the tilemap :)
*/
Tilemap
Make_tilemap(u32 n_layers, u32 tiles_x, u32 tiles_y, Spriteset *spriteset);



/*
* DESCRIPTIION
* --------------------------------------------------------------------------------------
* Frees the memory used by a Tilemap. Not calling it causes a leak.
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   tilemap: Tilemap struct data.
*/
void
Free_tilemap(Tilemap *tilemap);



/*
* Tilemap_set_tile
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Sets the value of 1 tile on the tilemap
*
* VARIABLES
* -------------------------------------------------------------------
* tilemap: Tilemap to use
* layer: Layer where is the tile
* x: Coordinate
* y: Coordinate
* tile: Tile value
*
*/
void
Tilemap_set_tile(Tilemap *tilemap, u32 layer, u32 x, u32 y, u32 tile);




/*
* Tilemap_get_tile
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Gets the value of 1 tile on the tilemap
*
* VARIABLES
* -------------------------------------------------------------------
* tilemap: Tilemap to use
* layer: Layer where is the tile
* x: Coordinate
* y: Coordinate
*
* RETURNS
* -------------------------------------------------------------------------------------
*   u32: The value of the tile
*/
u32
Tilemap_get_tile(Tilemap *tilemap, u32 layer, u32 x, u32 y);




/*
* DESCRIPTIION
* --------------------------------------------------------------------------------------
* Draws a tilemap
*
* PARAMETERS
* -------------------------------------------------------------------------------------
*   tilemap: Tilemap struct data to draw.
*/
void 
Draw_tilemap(Tilemap *tilemap, Vec2 pos, f32 width, f32 height, Color color);





/*
* Load_tilemap_from_tiled_json
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Loads a tilemap from a json generated with tiled
*
* The tilemap holds resources that should be released calling Free_tilemap
*
* VARIABLES
* -------------------------------------------------------------------
* filename: The json file to load
* init_x: initial position of the tilemap
* init_y: initial position of the tilemap
* screen_tile_width: tile width when displayed. 0 for default (use tilemap size)
* screen_tile_height: tile height when displayed. 0 for default (use tilemap size)
* spriteset: spriteset to use
* tilemap_result: Pointer to the resulting tilemap
*
* RETURNS
* -------------------------------------------------------------------
* int: != 0 on failure
*
*/
int
Load_tilemap_from_tiled_json(const char *filename, Spriteset *spriteset, Tilemap *tilemap_result);















void
Calculate_texture_coordinates(const Spriteset *spriteset, u32 sprite_number, Vec2 UVs[4]) {

	u32 sprite_width = spriteset->sprite_width;
	u32 sprite_height = spriteset->sprite_height;
	u32 texture_width = spriteset->texture_width;
	u32 texture_height = spriteset->texture_height;

    Assert(texture_width % sprite_width == 0, "ERROR: Texture width does not match sprite width.");
    Assert(texture_height % sprite_height == 0, "ERROR: Texture heigth does not match sprite height.");

    u32 tex_count_x = texture_width / sprite_width;
    // u32 tex_count_y = texture->height / sprite_height;

    u32 tx = sprite_number % tex_count_x;
    u32 ty = sprite_number / tex_count_x;
    f32 start_x = tx * sprite_width; //start of the sprite in the texture in pixels
    f32 start_y = ty * sprite_height;
    f32 x0 = (start_x + 0.5f) / (f32)(texture_width);
    f32 x1 = (start_x + (f32)(sprite_width) - 0.5f) / (f32)(texture_width);
    f32 y0 = (start_y + 0.5f) / (f32)(texture_height);
    f32 y1 = (start_y + (f32)(sprite_height) - 0.5f) / (f32)(texture_height);

	// We have to store this inverted in y
	UVs[0] = V2(x0, y1);
	UVs[1] = V2(x1, y1);
	UVs[2] = V2(x1, y0);
	UVs[3] = V2(x0, y0);
}


//Documented above
void
Draw_sprite(const Spriteset *spriteset, Vec2 pos, f32 width, f32 height, f32 rotation, f32 center_x, f32 center_y, u32 sprite_idx, Color color) {
    //--------  Calculate texture coordinates
	Vec2 UVs[4];
    Calculate_texture_coordinates(spriteset, sprite_idx, UVs);

	Vec2 v0 = V2(-width * center_x, -height * center_y);
	Vec2 v1 = V2(v0.x + width, v0.y);
	Vec2 v2 = V2(v1.x, v1.y + height);
	Vec2 v3 = V2(v0.x, v0.y + height);

	Mat2 rot_mat = M2_rotation(rotation);
	v0 = V2_add(pos, Mul_v2_m2(v0, rot_mat));
	v1 = V2_add(pos, Mul_v2_m2(v1, rot_mat));
	v2 = V2_add(pos, Mul_v2_m2(v2, rot_mat));
	v3 = V2_add(pos, Mul_v2_m2(v3, rot_mat));

	GFX_Set_texture(spriteset->texture_id);
	GFX_Draw_textured_quad(v0, v1, v2, v3, UVs[0], UVs[1], UVs[2], UVs[3], color);
}




// Documented above
int
Make_spriteset(const char *image_filename, u32 sprite_width, u32 sprite_height, bool linear_interpolation, Spriteset *spriteset_result) {
	memset(spriteset_result, 0, sizeof(Spriteset));

	{ // Loads the texture from a file
		u32 image_data_size;
		u8 *image_data = APP_Get_file_contentsz(image_filename, &image_data_size);
		if (image_data == NULL) {
			fprintf(stderr, "Cannot load file %s\n", image_filename);
			return -1;
		}

		int texture_width, texture_height, channels;
    	unsigned char *sprite = stbi_load_from_memory(
			image_data,
			image_data_size,
			&texture_width,
			&texture_height,
			&channels,
			STBI_rgb_alpha
		);

		APP_Free_file_contents(image_data);
    	if (sprite == NULL) {
    	    fprintf(stderr, "Couldnt load texture\n");
			return -1;
    	}

		GLuint texture_id;
    	glGenTextures(1, &texture_id);
    	glBindTexture(GL_TEXTURE_2D, texture_id);
		if (linear_interpolation) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // On webgl we need a pow
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // of 2 texture or set this
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite);
    	//glGenerateMipmap(GL_TEXTURE_2D);

    	stbi_image_free(sprite);

		// Set the values on the structure!!!
		spriteset_result->texture_id     = texture_id;
		spriteset_result->texture_width  = texture_width;
		spriteset_result->texture_height = texture_height;
	}

	spriteset_result->sprite_width  = sprite_width;
	spriteset_result->sprite_height = sprite_height;
	return 0;
}

// Documented above
void
Free_spriteset(Spriteset *spriteset) {
	glDeleteTextures(1, &(spriteset->texture_id));
	memset(spriteset, 0, sizeof(Spriteset));
}





//Documented above
Tilemap
Make_tilemap(u32 n_layers, u32 tiles_x, u32 tiles_y, Spriteset *spriteset) {
	Tilemap result  = {0};
	result.n_layers = n_layers;
    result.tiles_x  = tiles_x;
    result.tiles_y  = tiles_y;
	result.spriteset = spriteset;
	result.tilemap_data = Alloc(u32, n_layers * tiles_x * tiles_y);
	return result;
}

//Documented above
void
Free_tilemap(Tilemap *tilemap) {
    free(tilemap->tilemap_data);
	*tilemap = (Tilemap){0};
}


//Documented above
void
Tilemap_set_tile(Tilemap *tilemap, u32 layer, u32 x, u32 y, u32 tile) {
	Assert(layer < tilemap->n_layers, "%d < %d", layer, tilemap->n_layers);
	Assert(x     < tilemap->tiles_x,  "%d < %d", x, tilemap->tiles_x);
	Assert(y     < tilemap->tiles_y,  "%d < %d", y, tilemap->tiles_y);
	u32 w = tilemap->tiles_x;
	u32 h = tilemap->tiles_y;
	tilemap->tilemap_data[(layer * w * h) + (y * w) + x] = tile;
}

//Documented above
u32
Tilemap_get_tile(Tilemap *tilemap, u32 layer, u32 x, u32 y) {
	Assert(layer < tilemap->n_layers, "%d < %d", layer, tilemap->n_layers);
	Assert(x     < tilemap->tiles_x,  "%d < %d", x, tilemap->tiles_x);
	Assert(y     < tilemap->tiles_y,  "%d < %d", y, tilemap->tiles_y);
	u32 w = tilemap->tiles_x;
	u32 h = tilemap->tiles_y;
	return tilemap->tilemap_data[(layer * w * h) + (y * w) + x];
}

//Documented above
void 
Draw_tilemap(Tilemap *tilemap, Vec2 pos, f32 width, f32 height, Color color) {

	u32 tiles_x  = tilemap->tiles_x;
	u32 tiles_y  = tilemap->tiles_y;
	u32 n_layers = tilemap->n_layers;
	f32 tile_w   = width/(f32)tiles_x;
	f32 tile_h   = height/(f32)tiles_y;

	GFX_Set_texture(tilemap->spriteset->texture_id);
	for (u32 layer_i = 0; layer_i < n_layers; layer_i += 1) {
		for (u32 y = 0; y < tiles_y; y += 1) {
			for (u32 x = 0; x < tiles_x; x += 1) {
				u32 tile_idx = Tilemap_get_tile(tilemap, layer_i, x, y);
				if (tile_idx == -1) continue;
				Vec2 UVs[4];
    			Calculate_texture_coordinates(tilemap->spriteset, tile_idx, UVs);
				Vec2 v0 = V2(pos.x + (f32)x * tile_w, pos.y + (f32)y * tile_h);
				Vec2 v1 = V2(v0.x + tile_w, v0.y);
				Vec2 v2 = V2(v0.x + tile_w, v0.y + tile_h);
				Vec2 v3 = V2(v0.x, v0.y + tile_h);
				GFX_Draw_textured_quad(v0, v1, v2, v3, UVs[0], UVs[1], UVs[2], UVs[3], color);
			}
		}
	}
}



// Documented above
#include "third_party/parson.h"
int
Load_tilemap_from_tiled_json(const char *filename, Spriteset *spriteset, Tilemap *tilemap_result) {
	const char *file_data = (const char *)APP_Get_file_contentsz(filename, NULL);

	JSON_Value *root_value = json_parse_string(file_data);

	if(json_value_get_type(root_value) != JSONObject){
		fprintf(stderr, "Error, no valid file\n");
		return -1;
	}

	JSON_Array *layers = json_object_get_array(json_object(root_value), "layers");

    u32 n_layers = (u32)json_array_get_count(layers);

    u32 tiles_x = (u32)json_object_get_number(json_object(root_value),  "width");
    u32 tiles_y  = (u32)json_object_get_number(json_object(root_value), "height");
	Tilemap tm = Make_tilemap(n_layers, tiles_x, tiles_y, spriteset);

    for (u32 layer_i = 0; layer_i < n_layers; ++layer_i) {
        JSON_Object *json_tilemap      = json_array_get_object(layers, layer_i);
        JSON_Array  *json_tilemap_data = json_object_get_array(json_tilemap, "data");

        if(tiles_x * tiles_y != json_array_get_count(json_tilemap_data)) {
            json_value_free(root_value);
            fprintf(stderr, "Size of the tilemap does not match\n");
            return -1;
        }

        // The tilemap has the origin starting on the bottom left, we have to store it inverted
        for(size_t i =0; i < tiles_y; ++i){
            for(size_t j = 0; j < tiles_x; ++j) {
				u32 y = (tiles_y-i-1);
				u32 x = j;
				u32 tile_number = (u32)json_array_get_number(json_tilemap_data, i*tiles_x+j)-1;
				Tilemap_set_tile(&tm, layer_i, x, y, tile_number);
            }
        }
    }

    json_value_free(root_value);

	*tilemap_result = tm;

	return 0;
}



//Documented above
Object*
Load_objects_from_tiled_json(const char *filename, u32 gameplay_height, u32 *objects_size) {
    Object *obj;

    const char *file_data = (const char *)APP_Get_file_contentsz(filename, NULL);
	JSON_Value *root_value = json_parse_string(file_data);
	if(json_value_get_type(root_value) != JSONObject){
		fprintf(stderr, "Error, no valid file\n");
		return NULL;
	}

	JSON_Array *layers = json_object_get_array(json_object(root_value), "layers");
    JSON_Object *layer      = json_array_get_object(layers, 0);
    JSON_Array  *objects = json_object_get_array(layer, "objects");
    u32 n_objects = (u32)json_array_get_count(objects);
    *objects_size = n_objects;
    obj = Alloc(Object, n_objects);

    for (u32 i = 0; i < n_objects; i++) {
        JSON_Object *obj_json = json_array_get_object(objects, i);
        obj[i].x = json_object_get_number(obj_json, "x");
        obj[i].height = json_object_get_number(obj_json, "height");
        obj[i].y = gameplay_height - (json_object_get_number(obj_json, "y") + obj[i].height);
        obj[i].width = json_object_get_number(obj_json, "width");
        obj[i].rotation = json_object_get_number(obj_json, "rotation");

        const char *name = json_object_get_string(obj_json, "name");
        obj[i].name = name;
        // if (name != NULL && strcmp(name, "") != 0) {
        //     obj[i].texture = Get_texture_by_name(name, set, set_size);
        // }
        
        JSON_Array *props = json_object_get_array(obj_json, "properties");
        u32 p_count = json_array_get_count(props);
        obj[i].attributes = Alloc(Attribute, p_count);
        obj[i].attributes_size = p_count;
        for (u32 j = 0; j < p_count; j++) {
            JSON_Object *pr_obj = json_array_get_object(props, j);
            obj[i].attributes[j].name = json_object_get_string(pr_obj, "name");
            obj[i].attributes[j].value = json_object_get_string(pr_obj, "value");
        }
    }

    return obj;
}


//Documented above
void
Free_objects(Object *obj, u32 objects_size) {
    if (obj != NULL) {
        #if !defined(BUNDLED_TREE)
            for (u32 i = 0; i < objects_size; i++) {
                free(obj[i].attributes);
            }
            free(obj);
        #endif
        obj = NULL;
    }
}





#endif //_SPRITE_H_
