
#include "engine/app.h"
#include "engine/madmath.h"
#include "engine/graphics.h"
#define STB_IMAGE_IMPLEMENTATION
#include "engine/third_party/stb_image.h"
#include "baboon.c"

#define IMAGE_DATA baboon_jpg
#define IMAGE_DATA_LEN baboon_jpg_len



#define IMAGE_MAX 1024
#define IMAGE_COMPRESSED_MAX 1024
#define COMPRESSED_BLOCK_SIZE 8



typedef struct {
	unsigned char *data;
	int width;
	int height;
} Image;


static Color
Image_Get(Image img, int x, int y) {
	Color result = {0};
	if (x < 0 || x > img.width-1) return result;
	if (y < 0 || y > img.width-1) return result;
	int index = (y * img.width + x)*4;
	result.r = img.data[index+0];
	result.g = img.data[index+1];
	result.b = img.data[index+2];
	result.a = img.data[index+3];
	return result;
}


static void
Image_Set(Image img, int x, int y, Color color) {
	if (x < 0 || x > img.width-1) return;
	if (y < 0 || y > img.width-1) return;
	int index = (y * img.width + x)*4;
	img.data[index+0] = color.r;
	img.data[index+1] = color.g;
	img.data[index+2] = color.b;
	img.data[index+3] = color.a;
}


#define MAX_COMPRESS_TRANSFORMS 1024*1024
#define MAX_COMPRESS_BASE_DATA 1024



#define SCALE_RATE 2

static bool
Find_transform(int tile_x, int tile_y, int tile_size, Image img, bool *empty_map, int *transf_x, int *transf_y, int tol) {
	assert(tile_size<=256);
	assert(tile_x >= 0 && tile_x < img.width);
	assert(tile_x + tile_size <=  img.width);
	assert(tile_y >= 0 && tile_y < img.width);
	assert(tile_y + tile_size <=  img.height);

	static int dst_precomp_window[4*256*256] = {0};

	for (int w_row = 0; w_row < tile_size; w_row+=1) {
		for (int w_col = 0; w_col < tile_size; w_col+=1) {
			int pos_y = w_row + tile_y;
			int pos_x = w_col + tile_x;
			if (empty_map[pos_y*img.width+pos_x]) return false;

			// Also we precompute the window of the current dst
			Color color =  Image_Get(img, tile_x+w_col, tile_y+w_row);
			dst_precomp_window[(w_row*tile_size+w_col)*4+0] = -((int)color.r);
			dst_precomp_window[(w_row*tile_size+w_col)*4+1] = -((int)color.g);
			dst_precomp_window[(w_row*tile_size+w_col)*4+2] = -((int)color.b);
			dst_precomp_window[(w_row*tile_size+w_col)*4+3] = -((int)color.a);
		}
	}

	int best_norm = 1<<30;
	int best_col = 0;
	int best_row = 0;

	// Search for a similar tile but scaled by 2
	int window_size = tile_size * SCALE_RATE;
	for (int src_row = 0; src_row < img.height-window_size; src_row +=1) {
		for (int src_col = 0; src_col < img.width-window_size; src_col +=1) {
			
			// We ignore if the source and the dst are overlaped
			if (tile_y <= src_row + window_size && src_row <= tile_y + tile_size &&
				tile_x <= src_col + window_size && src_col <= tile_x + tile_size) continue;

			// Compare the blocks from dst and src using Norm2 and find a good match
			int norm2 = 0;

			for (int win_row = 0; win_row < window_size; win_row +=1) {
				for (int win_col = 0; win_col < window_size; win_col +=1) {
					int pixel_x = src_col+win_col;
					int pixel_y = src_row+win_row;
					if (empty_map[pixel_y*img.width+pixel_x]) {
						//__builtin_printf("Skip\n");
						goto next;
					}

					Color pixel_color = Image_Get(img, pixel_x, pixel_y);
					int dst_precomp_col = win_col/SCALE_RATE;
					int dst_precomp_row = win_row/SCALE_RATE;
					int precomp_pos = (dst_precomp_row*tile_size+dst_precomp_col)*4;
					int tmp;

					// R
					tmp = dst_precomp_window[precomp_pos+0];
					tmp += (int)pixel_color.r;
					norm2 += tmp*tmp;

					// G
					tmp = dst_precomp_window[precomp_pos+1];
					tmp += (int)pixel_color.g;
					norm2 += tmp*tmp;

					// B
					tmp = dst_precomp_window[precomp_pos+2];
					tmp += (int)pixel_color.b;
					norm2 += tmp*tmp;

					// A
					tmp = dst_precomp_window[precomp_pos+3];
					tmp += (int)pixel_color.a;
					norm2 += tmp*tmp;

					if (norm2 > tol*tol || norm2 > best_norm) goto next;
				}
			}


			best_norm = norm2;
			best_col = src_col;
			best_row = src_row;

			next: {}
		}
	}

	// If they are equal enought we finish
	if (best_norm <= tol*tol) {
		*transf_x = best_col;
		*transf_y = best_row;
		for (int w_row = 0; w_row < tile_size; w_row+=1) {
			for (int w_col = 0; w_col < tile_size; w_col+=1) {
				int pos_y = tile_y + w_row;
				int pos_x = tile_x + w_col;
				empty_map[pos_y*img.width+pos_x] = true;
			}
		}
		return true;
	}

	return false;
}


typedef struct {
	int source_x;
	int source_y;
	int dst_x;
	int dst_y;
} Transform;

#define DISPLACE_TILE_TIME 0.1f

#define STATE_ANIM_COMPRESSION   0
#define STATE_ANIM_DECOMPRESSION 1
#define STATE_ANIM_COMPRESSION_PAUSED   2
#define STATE_ANIM_DECOMPRESSION_PAUSED 3

struct {
	Image  image_raw;
	GLuint texture_raw;
	GLuint texture_compressed;
	Image  image_compressed;
	bool   empty_map[IMAGE_MAX*IMAGE_MAX];
	int current_tile_x;
	int current_tile_y;
	bool compression_finished;
	int total_transforms;
	Transform transforms[MAX_COMPRESS_TRANSFORMS];
	f32 displace_tile_time;
	f32 playback_speed;
	int target_transform;
	int state;
	bool paused;
} GLOBALS = {0};


void
Update_texture(GLuint texture, Image img) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

GLuint
Make_texture(Image img) {
	GLuint result;
    glGenTextures(1, &result);
	Update_texture(result, img);
	return result;
}

int
Frame(void) {
	if (APP_Quit_requested()) return 1;
	if (APP_Is_key_pressed(APP_KEY_SPACE)) {
		GLOBALS.paused = !GLOBALS.paused;
	}
	if (APP_Is_key_pressed(APP_KEY_LEFT)) {
		GLOBALS.playback_speed = Max(GLOBALS.playback_speed-0.1f, 0.1f);
	}
	if (APP_Is_key_pressed(APP_KEY_RIGHT)) {
		GLOBALS.playback_speed = Min(GLOBALS.playback_speed+0.1f, 4.0f);
	}
	if (APP_Is_key_pressed(APP_KEY_DOWN)) {
		GLOBALS.playback_speed = 1.0f;
	}
	
	#define TILE_SIZE 8

	if (!GLOBALS.compression_finished && GLOBALS.target_transform == GLOBALS.total_transforms) {
		int transf_x, transf_y;
		bool found = Find_transform(
			GLOBALS.current_tile_x, GLOBALS.current_tile_y, TILE_SIZE,
			GLOBALS.image_raw, GLOBALS.empty_map, &transf_x, &transf_y, 800);
		if (found) {
			__builtin_printf("Transform found!\n");
			__builtin_printf("Tile: %d     %d\n", GLOBALS.current_tile_x, GLOBALS.current_tile_y);
			__builtin_printf("Transform: %d     %d\n", transf_x, transf_y);
			Transform *transf = &GLOBALS.transforms[GLOBALS.total_transforms];
			transf->source_x  = transf_x;
			transf->source_y  = transf_y;
			transf->dst_x     = GLOBALS.current_tile_x;
			transf->dst_y     = GLOBALS.current_tile_y;
			GLOBALS.total_transforms += 1;
		}
		GLOBALS.current_tile_x += TILE_SIZE;
		if (GLOBALS.current_tile_x + TILE_SIZE > GLOBALS.image_raw.width) {
			GLOBALS.current_tile_x  = 0;
			GLOBALS.current_tile_y += TILE_SIZE;
		}
		if (GLOBALS.current_tile_y + TILE_SIZE > GLOBALS.image_raw.width) {
			__builtin_printf("Compression finished!\n");
			GLOBALS.compression_finished = true;
			GLOBALS.image_compressed.width  = GLOBALS.image_raw.width;
			GLOBALS.image_compressed.height = GLOBALS.image_raw.height;
			for (int row = 0; row < GLOBALS.image_compressed.height; row+=1) {
				for (int col = 0; col < GLOBALS.image_compressed.width; col+=1) {
					if (!GLOBALS.empty_map[row*GLOBALS.image_compressed.width+col]) {
						Color pixel_color = Image_Get(GLOBALS.image_raw, col, row);
						Image_Set(GLOBALS.image_compressed, col, row, pixel_color);
					}
				}
			}

			for (int transf_i = GLOBALS.total_transforms-1; transf_i >= 0; transf_i-=1) {
				Transform *transf = &GLOBALS.transforms[transf_i];
				for (int w_row = 0; w_row < TILE_SIZE; w_row+=1) {
					for (int w_col = 0; w_col < TILE_SIZE; w_col+=1) {
						int r=0, g=0, b=0, a=0;
						int src_pos_x = w_col*SCALE_RATE+transf->source_x;
						int src_pos_y = w_row*SCALE_RATE+transf->source_y;
						for (int i = 0; i < SCALE_RATE; i+=1) {
							for (int j = 0; j < SCALE_RATE; j+=1) {
								Color c = Image_Get(GLOBALS.image_compressed, src_pos_x+i, src_pos_y+j);
								assert(c.a != 0);
								r += (int)c.r; g += (int)c.g; b += (int)c.b; a += (int)c.a;
							}
						}
						Color c;
						c.r = (u8)(r/(SCALE_RATE*SCALE_RATE));
						c.g = (u8)(g/(SCALE_RATE*SCALE_RATE));
						c.b = (u8)(b/(SCALE_RATE*SCALE_RATE));
						c.a = (u8)(a/(SCALE_RATE*SCALE_RATE));

						int dst_pos_x = w_col+transf->dst_x;
						int dst_pos_y = w_row+transf->dst_y;
						Image_Set(GLOBALS.image_compressed, dst_pos_x, dst_pos_y, c);
					}
				}
			}

			GLOBALS.texture_compressed = Make_texture(GLOBALS.image_compressed);

		}
	}

	f32 ww = (f32)APP_Get_window_width();
	f32 wh = (f32)APP_Get_window_height();

	glViewport(0, 0, ww, wh);
	glClear(GL_COLOR_BUFFER_BIT);

	GFX_Begin();

	GFX_Set_matrix(M4_Orthographic(0, ww, 0, wh, 0, 1));

	f32 i_height    = wh*0.8f;
	f32 image_scale = i_height/(f32)GLOBALS.image_raw.height;
	f32 i_width     = (f32)GLOBALS.image_raw.width * image_scale;
	Vec2 image_pos   = V2((ww-i_width)*0.5f, (wh-i_height)*0.5f);

	if (!GLOBALS.compression_finished) GFX_Set_texture(GLOBALS.texture_raw);
	else GFX_Set_texture(GLOBALS.texture_compressed);

	GFX_Draw_rect(image_pos, i_width, i_height, WHITE);


	if (GLOBALS.state == STATE_ANIM_COMPRESSION) {

		GFX_Set_texture(GFX_Default_texture());
		for (int transf_i = 0; transf_i < GLOBALS.target_transform; transf_i+=1) {
			Transform *transf = &GLOBALS.transforms[transf_i];
			Vec2 dst_pos = V2(transf->dst_x, transf->dst_y);
			dst_pos      = V2_Add(image_pos, V2_Mulf(dst_pos, image_scale));
			f32 dst_size = (f32)(TILE_SIZE) * image_scale;
			GFX_Draw_rect(dst_pos, dst_size, dst_size, RAYWHITE);
		}

		if (!GLOBALS.paused) {
			if (GLOBALS.target_transform < GLOBALS.total_transforms) {


				GFX_Set_texture(GLOBALS.texture_raw);
				if (GLOBALS.displace_tile_time <= 0.0f) {
					GLOBALS.displace_tile_time = DISPLACE_TILE_TIME;
					GLOBALS.target_transform += 1;
				}
				else {
					f32 lerp_factor = (DISPLACE_TILE_TIME - GLOBALS.displace_tile_time)/DISPLACE_TILE_TIME;
					Transform *transf = &GLOBALS.transforms[GLOBALS.target_transform];
					f32 src_size = (f32)TILE_SIZE*image_scale;

					Vec2 uv0     = V2(transf->source_x, transf->source_y);
					Vec2 uv1     = V2(uv0.x+TILE_SIZE*2, uv0.y);
					Vec2 uv2     = V2(uv0.x+TILE_SIZE*2, uv0.y+TILE_SIZE*2);
					Vec2 uv3     = V2(uv0.x+TILE_SIZE*2, uv0.y+TILE_SIZE*2);
					uv0 = V2_Mulf(uv0, 1.0f/(f32)GLOBALS.image_raw.width);
					uv1 = V2_Mulf(uv1, 1.0f/(f32)GLOBALS.image_raw.width);
					uv2 = V2_Mulf(uv2, 1.0f/(f32)GLOBALS.image_raw.width);
					uv3 = V2_Mulf(uv3, 1.0f/(f32)GLOBALS.image_raw.width);

					Vec2 src_v0  = V2(transf->dst_x, transf->dst_y);
					src_v0       = V2_Add(image_pos, V2_Mulf(src_v0, image_scale));
					Vec2 src_v1  = V2(src_v0.x+src_size, src_v0.y);
					Vec2 src_v2  = V2(src_v0.x+src_size, src_v0.y+src_size);
					Vec2 src_v3  = V2(src_v0.x, src_v0.y+src_size);

					f32 dst_size = (f32)(TILE_SIZE*SCALE_RATE)*image_scale;
					Vec2 dst_v0  = V2(transf->source_x, transf->source_y);
					dst_v0       = V2_Add(image_pos, V2_Mulf(dst_v0, image_scale));
					Vec2 dst_v1  = V2(dst_v0.x+dst_size, dst_v0.y);
					Vec2 dst_v2  = V2(dst_v0.x+dst_size, dst_v0.y+dst_size);
					Vec2 dst_v3  = V2(dst_v0.x, dst_v0.y+dst_size);

					Vec2 v0 = V2_Lerp(src_v0, dst_v0, lerp_factor);
					Vec2 v1 = V2_Lerp(src_v1, dst_v1, lerp_factor);
					Vec2 v2 = V2_Lerp(src_v2, dst_v2, lerp_factor);
					Vec2 v3 = V2_Lerp(src_v3, dst_v3, lerp_factor);
					GFX_Draw_textured_quad(v0, v1, v2, v3, uv0, uv1, uv2, uv3, WHITE);

					GLOBALS.displace_tile_time -= ((f32)APP_Frame_duration(1)*1e-9f*GLOBALS.playback_speed);
				}
			}
			else if (GLOBALS.compression_finished) {
				GLOBALS.displace_tile_time = DISPLACE_TILE_TIME;
				GLOBALS.target_transform -= 1;
				GLOBALS.state = STATE_ANIM_DECOMPRESSION;
				GLOBALS.paused = true;
			}
		}
	}
	else if (GLOBALS.state == STATE_ANIM_DECOMPRESSION) {

		GFX_Set_texture(GFX_Default_texture());
		
		for (int transf_i = 0; transf_i < GLOBALS.target_transform; transf_i+=1) {
			Transform *transf = &GLOBALS.transforms[transf_i];
			Vec2 dst_pos = V2(transf->dst_x, transf->dst_y);
			dst_pos      = V2_Add(image_pos, V2_Mulf(dst_pos, image_scale));
			f32 dst_size = (f32)(TILE_SIZE) * image_scale;
			GFX_Draw_rect(dst_pos, dst_size, dst_size, RAYWHITE);
		}

		GFX_Set_texture(GLOBALS.texture_compressed);

		if (!GLOBALS.paused) {
			if (GLOBALS.target_transform >= 0) {
				if (GLOBALS.displace_tile_time <= 0.0f) {
					GLOBALS.displace_tile_time = DISPLACE_TILE_TIME;
					GLOBALS.target_transform -= 1;
				}
				else {
					f32 lerp_factor = (DISPLACE_TILE_TIME - GLOBALS.displace_tile_time)/DISPLACE_TILE_TIME;
					Transform *transf = &GLOBALS.transforms[GLOBALS.target_transform];

					Vec2 uv0     = V2(transf->source_x, transf->source_y);
					Vec2 uv1     = V2(uv0.x+TILE_SIZE*2, uv0.y);
					Vec2 uv2     = V2(uv0.x+TILE_SIZE*2, uv0.y+TILE_SIZE*2);
					Vec2 uv3     = V2(uv0.x+TILE_SIZE*2, uv0.y+TILE_SIZE*2);
					uv0 = V2_Mulf(uv0, 1.0f/(f32)GLOBALS.image_raw.width);
					uv1 = V2_Mulf(uv1, 1.0f/(f32)GLOBALS.image_raw.width);
					uv2 = V2_Mulf(uv2, 1.0f/(f32)GLOBALS.image_raw.width);
					uv3 = V2_Mulf(uv3, 1.0f/(f32)GLOBALS.image_raw.width);

					f32 src_size = (f32)TILE_SIZE*image_scale;
					Vec2 src_v0  = V2(transf->dst_x, transf->dst_y);
					src_v0       = V2_Add(image_pos, V2_Mulf(src_v0, image_scale));
					Vec2 src_v1  = V2(src_v0.x+src_size, src_v0.y);
					Vec2 src_v2  = V2(src_v0.x+src_size, src_v0.y+src_size);
					Vec2 src_v3  = V2(src_v0.x, src_v0.y+src_size);

					f32 dst_size = (f32)(TILE_SIZE*SCALE_RATE)*image_scale;
					Vec2 dst_v0  = V2(transf->source_x, transf->source_y);
					dst_v0       = V2_Add(image_pos, V2_Mulf(dst_v0, image_scale));
					Vec2 dst_v1  = V2(dst_v0.x+dst_size, dst_v0.y);
					Vec2 dst_v2  = V2(dst_v0.x+dst_size, dst_v0.y+dst_size);
					Vec2 dst_v3  = V2(dst_v0.x, dst_v0.y+dst_size);

					Vec2 v0 = V2_Lerp(dst_v0, src_v0, lerp_factor);
					Vec2 v1 = V2_Lerp(dst_v1, src_v1, lerp_factor);
					Vec2 v2 = V2_Lerp(dst_v2, src_v2, lerp_factor);
					Vec2 v3 = V2_Lerp(dst_v3, src_v3, lerp_factor);
					GFX_Draw_textured_quad(v0, v1, v2, v3, uv0, uv1, uv2, uv3, WHITE);

					GLOBALS.displace_tile_time -= ((f32)APP_Frame_duration(1)*1e-9f*GLOBALS.playback_speed);
				}
			}
			else {
				GLOBALS.displace_tile_time = DISPLACE_TILE_TIME;
				GLOBALS.target_transform = 0;
				GLOBALS.state = STATE_ANIM_COMPRESSION;
				GLOBALS.paused = true;
			}
		}

	}

	GFX_End();

	return 0;
}

int
main() {
	static unsigned char asdfg[IMAGE_COMPRESSED_MAX*IMAGE_COMPRESSED_MAX*4];
	GLOBALS.image_compressed.data   = asdfg;
	GLOBALS.image_compressed.width  = IMAGE_COMPRESSED_MAX;
	GLOBALS.image_compressed.height = IMAGE_COMPRESSED_MAX;
	GLOBALS.playback_speed = 1.0f;

	if (0 > APP_Init("Fractal image compression", 600, 400)) Panic("Oops");
	if (0 > GFX_Init()) Panic("Oops");

	GLOBALS.image_raw.data = stbi_load_from_memory(
		IMAGE_DATA, IMAGE_DATA_LEN,
		&GLOBALS.image_raw.width, &GLOBALS.image_raw.height, NULL, 4);
	if (!GLOBALS.image_raw.data) Panic("Oops");

	// Flip the image vertically
	{
		int width  = GLOBALS.image_raw.width;
		int height = GLOBALS.image_raw.height;
		for (int row = 0; row < height/2; row+=1) {
			for (int col = 0; col < width; col+=1) {
				Color colorA = Image_Get(GLOBALS.image_raw, col, row);
				int tmp = colorA.r;
				tmp += colorA.g;
				tmp += colorA.b;
				colorA.r = tmp/3; colorA.g = tmp/3; colorA.b = tmp/3;
				Color colorB = Image_Get(GLOBALS.image_raw, col, height-1-row);
				tmp = colorB.r;
				tmp += colorB.g;
				tmp += colorB.b;
				colorB.r = tmp/3; colorB.g = tmp/3; colorB.b = tmp/3;
				Image_Set(GLOBALS.image_raw, col, row, colorB);
				Image_Set(GLOBALS.image_raw, col, height-1-row, colorA);
			}
		}
	}

	{
		int src_width     = GLOBALS.image_raw.width;
		int compressed_w  = src_width / COMPRESSED_BLOCK_SIZE;
		int window_left_w = src_width - (compressed_w * COMPRESSED_BLOCK_SIZE);
		if (window_left_w) compressed_w += 1;
		GLOBALS.image_compressed.width = compressed_w;

		int src_height    = GLOBALS.image_raw.height;
		int compressed_h  = src_height / COMPRESSED_BLOCK_SIZE;
		int window_left_h = src_height - (compressed_h * COMPRESSED_BLOCK_SIZE);
		if (window_left_w) compressed_h += 1;
		GLOBALS.image_compressed.height= compressed_h;

		for (int row = 0; row < compressed_h; row+=1) {
			int wh = COMPRESSED_BLOCK_SIZE;
			if (row == COMPRESSED_BLOCK_SIZE-1 && window_left_h) wh = window_left_h;
			for (int col = 0; col < compressed_w; col+=1) {
				int ww = COMPRESSED_BLOCK_SIZE;
				if (col == COMPRESSED_BLOCK_SIZE-1 && window_left_w) ww = window_left_w;

				// Detect where the window starts
				int src_row = row * COMPRESSED_BLOCK_SIZE;
				int src_col = col * COMPRESSED_BLOCK_SIZE;

				int r = 0, g = 0, b = 0, a = 0;
				int total = 0;
				for (int w_row = 0; w_row < wh; w_row+=1) {
					for (int w_col = 0; w_col < ww; w_col+=1) {
						Color c = Image_Get(GLOBALS.image_raw, src_col+w_col, src_row+w_row);
						r += (int)c.r;
						g += (int)c.g;
						b += (int)c.b;
						a += (int)c.a;
						total += 1;
					}
				}
				r /= total;
				g /= total;
				b /= total;
				a /= total;
				Color c = COLOR(r,g,b,a);
				Image_Set(GLOBALS.image_compressed, col, row, c);
			}
		}
	}

	GLOBALS.texture_raw = Make_texture(GLOBALS.image_raw);

	Vec4 c = Color_to_Vec4(RAYWHITE);
	glClearColor(c.r, c.g, c.b, c.a);

	APP_Run_application_loop(Frame);
}


