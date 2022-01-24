
#ifndef _FONT_H_
#define _FONT_H_

// 
// ---------- font.h ----------
// Api for font rendering stuff
//


#include "base.h"
#include "graphics.h"
#include "third_party/stb_truetype.h"



// The struct of TextFont
typedef struct {
	stbtt_bakedchar glyphs_info[96]; // This stores the information of all ASCII glyphs
	GLuint texture;
	f32 base_height;
} TextFont;


typedef enum {
	FONT_USE_LIENAR_INTERPOLATION_NO,
	FONT_USE_LIENAR_INTERPOLATION_YES,
} FontUseLinearInterpolation;


/*
* Make_font
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Makes a font with the passed font file and height
* It rasterizes a atlas with ONLY ASCII characters and setups the openGL
* texture.
*
* To clean the resource you need to call Free_font.
*
* VARIABLES
* -------------------------------------------------------------------
* font:     Uninitialized font to setup
* filename: The file of the font
* height:   Height in pixels of the rasterized glyphs
*
* RETURNS
* -------------------------------------------------------------------
* int: 0 on success, < 0 on failure
*
*/
int
Make_font(TextFont *font, const char *filename, f32 height, FontUseLinearInterpolation linear_interpolation);




/*
* Free_font
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Free a previously initcialized font with Make_font.
*
* This deletes the opengl texture and puts 0 on all the data.
*
* VARIABLES
* -------------------------------------------------------------------
* font:     Font to cleanup
*
*/
void
Free_font(TextFont *font);



/*
* Draw_text
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Draws text on the screen (Only ASCII), the font passed has to be previously
* initialized with Make_font and the font renderer has to be initializer with
* Font_renderer_setup.
*
* This renders assuming that Y increases going down on the screen.
*
* VARIABLES
* -------------------------------------------------------------------
* font: Font to use.
* text: ASCII string to draw.
* scale: Apply some scale to the rendered text
* pos: The coordinates on screen
* color: Color channels
*
*/
void 
Draw_text(TextFont *font, const char *text, f32 scale, Vec2 pos, Color color);





/*
* Get_text_width
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Calculates the width in pixels that will have the drawed text.
*
* VARIABLES
* -------------------------------------------------------------------
* font: Font to use.
* text: ASCII string to measure.
* scale: Apply some scale to the rendered text
*
* RETURNS
* -------------------------------------------------------------------
* f32: Width in pixels
*
*/
f32
Get_text_width(TextFont *font, const char *text, f32 scale);






/*
* Draw_text_with_height
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
*
* This is a variant of Draw_text, this recieves the height on pixels to rescale
* the font.
*
*
* VARIABLES
* -------------------------------------------------------------------
* font:   Font to use.
* text:   ASCII string to draw.
* height: Pixels of the desired height
* pos: The coordinates on screen
* color: Color channels
*
*/
void 
Draw_text_with_height(TextFont *font, const char *text, f32 height, Vec2 pos, Color color);





/*
* Get_text_width_with_height
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
*
* This is a variant of Get_text_width, this recieves the height on pixels to rescale
* the font.
*
* VARIABLES
* -------------------------------------------------------------------
* font: Font to use.
* text: ASCII string to measure.
* height: Height on pixels
*
* RETURNS
* -------------------------------------------------------------------
* f32: Width in pixels
*
*/
f32
Get_text_width(TextFont *font, const char *text, f32 scale);









// -------------------------------------------------
//
//
// IMPLEMENTATION STARTS
//
//
// -------------------------------------------------




#define TEX_SIZE 1024


// Documented above
int
Make_font(TextFont *font, const char *filename, f32 height, FontUseLinearInterpolation linear_interpolation) {
	memset(font, 0, sizeof(TextFont));
	u32 font_buffer_size;
	u8 *ttf_buffer = APP_Get_file_contentsz(filename, &font_buffer_size);
	if (ttf_buffer == NULL) {
		Free_font(font);
		return -1;
	}
	u8 *tmp_bitmap = Alloc(u8, TEX_SIZE * TEX_SIZE + TEX_SIZE * TEX_SIZE * 4);
	int result = stbtt_BakeFontBitmap(ttf_buffer, 0, height, tmp_bitmap, TEX_SIZE, TEX_SIZE, 32, 96, font->glyphs_info);

	u8 *tmp_rgba_bitmap = &tmp_bitmap[TEX_SIZE * TEX_SIZE];
	for (int i = 0; i < TEX_SIZE; i+=1) {
		for (int j = 0; j < TEX_SIZE; j+=1) {
			tmp_rgba_bitmap[i*TEX_SIZE*4 + j*4 + 0] = 0xFF; // R
			tmp_rgba_bitmap[i*TEX_SIZE*4 + j*4 + 1] = 0xFF; // G
			tmp_rgba_bitmap[i*TEX_SIZE*4 + j*4 + 2] = 0xFF; // B
			u8 A = tmp_bitmap[i*TEX_SIZE + j];
			tmp_rgba_bitmap[i*TEX_SIZE*4 + j*4 + 3] = A; // A
		}
	}

	APP_Free_file_contents(ttf_buffer);

	if (result <= 0) {
		free(tmp_bitmap);
		Free_font(font);
		return -1;
	}

	// Make the texture
	glGenTextures(1, &font->texture);
    glBindTexture(GL_TEXTURE_2D, font->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_SIZE, TEX_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmp_rgba_bitmap);
	if (linear_interpolation == FONT_USE_LIENAR_INTERPOLATION_YES) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	free(tmp_bitmap);

	font->base_height = height;

	return 0;
}


// Documented above
void
Free_font(TextFont *font) {
	// Clean the texture
	glDeleteTextures(1, &font->texture);
	memset(font, 0, sizeof(TextFont));
}



/*
* Draw_glyph
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Renders 1 glyph
* Assumes that the right texture, color, VBO etc was setted before the call.
*
*
* VARIABLES
* -------------------------------------------------------------------
* glyph_info: The data of the glyph
* scale: Scale to apply
* x,y : Coordinates
*
*/
static void
Draw_glyph(stbtt_bakedchar *glyph_info, f32 scale, Vec2 pos, Color color) {

	f32 inv_tex_size = (1.0f / (f32)TEX_SIZE);
	
	f32 width  = (glyph_info->x1 - glyph_info->x0) * scale;
	f32 height = (glyph_info->y1 - glyph_info->y0) * scale;

	f32 xoff = glyph_info->xoff * scale;
	f32 yoff = glyph_info->yoff * scale;

	f32 norm_x0 = glyph_info->x0 * inv_tex_size;
	f32 norm_y0 = glyph_info->y0 * inv_tex_size;
	f32 norm_x1 = glyph_info->x1 * inv_tex_size;
	f32 norm_y1 = glyph_info->y1 * inv_tex_size;

	Vec2 pos_offseted = V2(pos.x+xoff, pos.y-(height+yoff));
	Vec2 v1 = V2_add(pos_offseted, V2(width, 0.0f));
	Vec2 v2 = V2_add(pos_offseted, V2(width, height));
	Vec2 v3 = V2_add(pos_offseted, V2(0.0f, height));

	GFX_Draw_textured_quad(
		pos_offseted, v1, v2, v3,
		V2(norm_x0, norm_y1), V2(norm_x1, norm_y1), V2(norm_x1, norm_y0),V2(norm_x0, norm_y0),
		color);
}




// Documented above
void 
Draw_text(TextFont *font, const char *text, f32 scale, Vec2 pos, Color color) {
	GFX_Set_texture(font->texture);

	u32 character_i = 0;
	char character = text[character_i];
	f32 cursor_x = pos.x;
	while (character != 0) {
		if (character < 32 || character > 126) character = ' ';
		stbtt_bakedchar glyph_info = font->glyphs_info[character-32];
		Draw_glyph(&glyph_info, scale, V2(cursor_x, pos.y), color);
		cursor_x += glyph_info.xadvance * scale;
		++character_i;
		character = text[character_i];
	}
}



// Documented above
f32
Get_text_width(TextFont *font, const char *text, f32 scale) {
	
	f32 result_width = 0.0f;

	u32 character_i = 0;
	char character = text[character_i];
	while (character != 0) {
		if (character < 32 || character > 126) character = ' ';
		result_width += font->glyphs_info[character-32].xadvance * scale;
		++character_i;
		character = text[character_i];
	}

	return result_width;

}

// Documented above
void 
Draw_text_with_height(TextFont *font, const char *text, f32 height, Vec2 pos, Color color) {
	Draw_text(font, text, height/font->base_height, pos, color);
}

// Documented above
f32
Get_text_width_with_height(TextFont *font, const char *text, f32 height) {
	return Get_text_width(font, text, height/font->base_height);
}


#endif // _FONT_H_

