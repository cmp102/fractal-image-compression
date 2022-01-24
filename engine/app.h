//
//
//
//


// MAP OF THE FILE
//
// - HEADER (All API's function calls)
// - IMPLEMENTATION
// 	- GENERAL IMPLEMENTATIONS (Calling to the per platform implementations when needed)
//	- PER PLATFORM NEEDED IMPLEMENTATIONS
// 	  - Windows
// 	  - Linux
// 	  - Wasm
//



#ifndef _APP_H_
#define _APP_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#ifndef APP_PUBLIC
	#define APP_PUBLIC 
#endif

#ifndef APP_INTERNAL
	#define APP_INTERNAL static
#endif




///////////////////////////////////////////////////////////////////////////
//
//
//
// Basic GL application API
//
//
//
///////////////////////////////////////////////////////////////////////////




/* Based on GLFW */
typedef enum {
    APP_KEY_INVALID          = 0,
    APP_KEY_SPACE            = 32,
    APP_KEY_APOSTROPHE       = 39,  /* ' */
    APP_KEY_COMMA            = 44,  /* , */
    APP_KEY_MINUS            = 45,  /* - */
    APP_KEY_PERIOD           = 46,  /* . */
    APP_KEY_SLASH            = 47,  /* / */
    APP_KEY_0                = 48,
    APP_KEY_1                = 49,
    APP_KEY_2                = 50,
    APP_KEY_3                = 51,
    APP_KEY_4                = 52,
    APP_KEY_5                = 53,
    APP_KEY_6                = 54,
    APP_KEY_7                = 55,
    APP_KEY_8                = 56,
    APP_KEY_9                = 57,
    APP_KEY_SEMICOLON        = 59,  /* ; */
    APP_KEY_EQUAL            = 61,  /* = */
    APP_KEY_A                = 65,
    APP_KEY_B                = 66,
    APP_KEY_C                = 67,
    APP_KEY_D                = 68,
    APP_KEY_E                = 69,
    APP_KEY_F                = 70,
    APP_KEY_G                = 71,
    APP_KEY_H                = 72,
    APP_KEY_I                = 73,
    APP_KEY_J                = 74,
    APP_KEY_K                = 75,
    APP_KEY_L                = 76,
    APP_KEY_M                = 77,
    APP_KEY_N                = 78,
    APP_KEY_O                = 79,
    APP_KEY_P                = 80,
    APP_KEY_Q                = 81,
    APP_KEY_R                = 82,
    APP_KEY_S                = 83,
    APP_KEY_T                = 84,
    APP_KEY_U                = 85,
    APP_KEY_V                = 86,
    APP_KEY_W                = 87,
    APP_KEY_X                = 88,
    APP_KEY_Y                = 89,
    APP_KEY_Z                = 90,
    APP_KEY_LEFT_BRACKET     = 91,  /* [ */
    APP_KEY_BACKSLASH        = 92,  /* \ */
    APP_KEY_RIGHT_BRACKET    = 93,  /* ] */
    APP_KEY_GRAVE_ACCENT     = 96,  /* ` */
    APP_KEY_WORLD_1          = 161, /* non-US #1 */
    APP_KEY_WORLD_2          = 162, /* non-US #2 */
    APP_KEY_ESCAPE           = 256,
    APP_KEY_ENTER            = 257,
    APP_KEY_TAB              = 258,
    APP_KEY_BACKSPACE        = 259,
    APP_KEY_INSERT           = 260,
    APP_KEY_DELETE           = 261,
    APP_KEY_RIGHT            = 262,
    APP_KEY_LEFT             = 263,
    APP_KEY_DOWN             = 264,
    APP_KEY_UP               = 265,
    APP_KEY_PAGE_UP          = 266,
    APP_KEY_PAGE_DOWN        = 267,
    APP_KEY_HOME             = 268,
    APP_KEY_END              = 269,
    APP_KEY_CAPS_LOCK        = 280,
    APP_KEY_SCROLL_LOCK      = 281,
    APP_KEY_NUM_LOCK         = 282,
    APP_KEY_PRINT_SCREEN     = 283,
    APP_KEY_PAUSE            = 284,
    APP_KEY_F1               = 290,
    APP_KEY_F2               = 291,
    APP_KEY_F3               = 292,
    APP_KEY_F4               = 293,
    APP_KEY_F5               = 294,
    APP_KEY_F6               = 295,
    APP_KEY_F7               = 296,
    APP_KEY_F8               = 297,
    APP_KEY_F9               = 298,
    APP_KEY_F10              = 299,
    APP_KEY_F11              = 300,
    APP_KEY_F12              = 301,
    APP_KEY_F13              = 302,
    APP_KEY_F14              = 303,
    APP_KEY_F15              = 304,
    APP_KEY_F16              = 305,
    APP_KEY_F17              = 306,
    APP_KEY_F18              = 307,
    APP_KEY_F19              = 308,
    APP_KEY_F20              = 309,
    APP_KEY_F21              = 310,
    APP_KEY_F22              = 311,
    APP_KEY_F23              = 312,
    APP_KEY_F24              = 313,
    APP_KEY_F25              = 314,
    APP_KEY_KP_0             = 320,
    APP_KEY_KP_1             = 321,
    APP_KEY_KP_2             = 322,
    APP_KEY_KP_3             = 323,
    APP_KEY_KP_4             = 324,
    APP_KEY_KP_5             = 325,
    APP_KEY_KP_6             = 326,
    APP_KEY_KP_7             = 327,
    APP_KEY_KP_8             = 328,
    APP_KEY_KP_9             = 329,
    APP_KEY_KP_DECIMAL       = 330,
    APP_KEY_KP_DIVIDE        = 331,
    APP_KEY_KP_MULTIPLY      = 332,
    APP_KEY_KP_SUBTRACT      = 333,
    APP_KEY_KP_ADD           = 334,
    APP_KEY_KP_ENTER         = 335,
    APP_KEY_KP_EQUAL         = 336,
    APP_KEY_LEFT_SHIFT       = 340,
    APP_KEY_LEFT_CONTROL     = 341,
    APP_KEY_LEFT_ALT         = 342,
    APP_KEY_LEFT_SUPER       = 343,
    APP_KEY_RIGHT_SHIFT      = 344,
    APP_KEY_RIGHT_CONTROL    = 345,
    APP_KEY_RIGHT_ALT        = 346,
    APP_KEY_RIGHT_SUPER      = 347,
    APP_KEY_MENU             = 348,
	APP_MAX_KEYCODES,
} APP_KeyCode;



typedef enum {
	APP_MOUSE_BUTTON_LEFT   = 0,
	APP_MOUSE_BUTTON_RIGHT  = 1,
	APP_MOUSE_BUTTON_MIDDLE = 2,
	APP_MOUSE_BUTTON_INVALID = 3,
} APP_MouseButton;


typedef enum {
	APP_TOUCH_STATE_INVALID = 0x0,
	APP_TOUCH_STATE_BEGIN   = 0x1,
	APP_TOUCH_STATE_MOVE    = 0x2,
	APP_TOUCH_STATE_END     = 0x4,
	APP_TOUCH_STATE_CANCEL  = 0x8,
} APP_TouchState;

typedef enum {
	APP_POINTER_STATE_INVALID  = 0x0, // Invalid state
	APP_POINTER_STATE_DOWN     = 0x1, // Pointer is touching the canvas
	APP_POINTER_STATE_PRESSED  = 0x2, // Pointer changed from up to down
	APP_POINTER_STATE_RELEASED = 0x4, // Pointer changed from down to up
	APP_POINTER_STATE_UP       = 0x8, // Pointer isn't touching the canvas
} APP_PointerState;

typedef enum {
	APP_SUCCESS = 0,
} APP_ErrorCode;





// Creates a windows based on the description passed.
// This must be called before Setup_GL and any window operation.
// To close the window properly, Destroy_window must be called
// at the end.
APP_PUBLIC int
APP_Init(const char *title, int width,	int height);

// Destroys the window
APP_PUBLIC void
APP_Destroy_window(void);



// Gets the window width
APP_PUBLIC int
APP_Get_window_width(void);

// Gets the window height
APP_PUBLIC int
APP_Get_window_height(void);

// Gets if the windows was resized in the last frame
APP_PUBLIC bool
APP_Window_resized(void);



// Gets if the key is down
APP_PUBLIC bool
APP_Is_key_down(APP_KeyCode key);

// Gets if the key is being pressed for first time
APP_PUBLIC bool
APP_Is_key_pressed(APP_KeyCode key);

// The key was previously down
APP_PUBLIC bool
APP_Is_key_released(APP_KeyCode key);

// The key is untouched
APP_PUBLIC bool
APP_Is_key_up(APP_KeyCode key);

// If the key is repeated, (Timing determined by the environment) useful for text input
// controls, like backespace to delete characters
APP_PUBLIC bool
APP_Is_key_repeat(APP_KeyCode key);


// Gets a null terminated utf8 string with the last text send by the keyboard
APP_PUBLIC const char *
APP_Get_text_input(void);

// Gets the length (IN BYTES) of the text input
APP_PUBLIC unsigned int
APP_Get_text_input_length(void);



// Gets the mouse x position
APP_PUBLIC float
APP_Get_mouse_x(void);

// Gets the mouse y position (up is 0)
APP_PUBLIC float
APP_Get_mouse_y(void);

// Gets the mouse y position inverted (down is 0)
APP_PUBLIC float
APP_Get_mouse_y_inv(void);



// Gets if the mouse button is down
APP_PUBLIC bool
APP_Is_mouse_button_down(APP_MouseButton button);

// Gets if the button is being pressed for first time
APP_PUBLIC bool
APP_Is_mouse_button_pressed(APP_MouseButton button);

// The button was previously down
APP_PUBLIC bool
APP_Is_mouse_button_released(APP_MouseButton button);

// The button is untouched
APP_PUBLIC bool
APP_Is_mouse_button_up(APP_MouseButton button);




// Gets the mouse wheel delta
APP_PUBLIC float
APP_Get_wheel_x(void);

// Gets the mouse wheel delta
APP_PUBLIC float
APP_Get_wheel_y(void);




// Gets the touch x
APP_PUBLIC float
APP_Get_touch_x(int id);

// Gets the touch y
APP_PUBLIC float
APP_Get_touch_y(int id);

// Gets the touch state
APP_PUBLIC unsigned char
APP_Get_touch_state(int id);


// The pointer is a mix between mouse and touch, tracks the mouse or the touch(0) depending on the
// last interaction

APP_PUBLIC float
APP_Get_pointer_x(void);

APP_PUBLIC float
APP_Get_pointer_y(void);

APP_PUBLIC unsigned char
APP_Get_pointer_state(void);





// Changes to fullscreen or windowed depending if is true (fullscreen) or
// false (windowed).
//
// The resize event will be triggered when this is called.
APP_PUBLIC void
APP_Set_fullscreen(bool enable);


// Shows or hides the mouse depending on the parameter.
// true  = shows
// false = hides
APP_PUBLIC void
APP_Show_mouse(bool show);


// Changes the window title.
APP_PUBLIC void
APP_Set_window_title(const char *title);





// Changes the swap interval between the backbuffer and the front buffer
// This must be called after Setup_GL
//
// 0 disables the swap interval so unlimits the fps rate.
//
// NOTE: This doesn't have any effect on WASM.
APP_PUBLIC void
APP_Set_swap_interval(unsigned int interval);




// Runs the application loop, recives a application frame handler
// which will execute every frame.
// If the handler returns 0 the application should continue normally
// If the handler returns 1 the application should finish.
// If the handler returns <0 the application will have an abnormal finish.
//
// Take into account that this function don't does any resource cleanup
// when the handler decides tu finish, all resource cleanup should be
// done inside the frame handler.
//
// This function varies in implementaton between wasm and other platforms
// because in javascript we need to use the frame handler as a event listener.
// Look at platform_wasm.h, WAFN_application_frame().
// 
// The way to call this function from main should be:
//
// int
// main(...) {
//	....
//   return Run_application_loop(My_frame_handler);
// }
APP_PUBLIC int
APP_Run_application_loop(int(*application_frame)(void));



// Returns the nanoseconds passed from the start of the app
APP_PUBLIC int64_t
APP_Time(void);


APP_PUBLIC int64_t
APP_Frame_duration(int samples);



typedef int (*APP_SoundPlayerCallback) (void *user_data, float* buffer, int n_frames, int n_channels);




//
// Description with the desired when the player is launched
//
typedef struct {
	int sample_rate;        /* requested sample rate */
	int num_channels;       /* number of channels, default: 1 (mono) */
	int buffer_frames;      /* number of frames in streaming buffer */
    void *user_data;        /* optional user data argument for stream_userdata_cb */
	APP_SoundPlayerCallback stream_cb; /* Streaming callback */
} APP_SoundPlayerDesc;


// Launchs a thread (On linux and windows) or a async rutine (wasm)
// Which will play the audio.
//
// When it needs a new chunk of samples will call the callback
APP_PUBLIC int
APP_Launch_sound_player(APP_SoundPlayerDesc *desc);


// Terminates the player routine.
APP_PUBLIC void
APP_Terminate_sound_player(void);


// Returns a NULL terminated array with de contents of the file,
// the parameter size is setted with de file size (without counting
// the appended 0).
// If the file can't be found, will return a NULL
//
// If we are on BUNDLED_TREE mode the data returned will be a pointer
// to the data embeded into de binary.
//
// If not, the data will be heap allocated.
//
// To free this data on a safe way we have to call to Free_file_contents()
// this function will take into account the mode.
APP_PUBLIC unsigned char *
APP_Get_file_contentsz(const char *filename, uint32_t *size);



// Frees the data getted by Get_file_contentsz
// if the value is NULL nothing happens
APP_PUBLIC void
APP_Free_file_contents(unsigned char *data);



// Gets the file modify time. This will always return 0 on bundled tree mode
APP_PUBLIC uint64_t
Get_file_modify_time(const char *filename);



#if defined(WIN32)
    /* Windows */
	#define APP_WINDOWS (1)
	#include <windows.h>

#elif defined(__wasm__)
	/* Wasm */
	#define APP_WASM (1)
	#define BUNDLED_TREE (1)  // Wasm always need the bundled tree
	#define GL_ES2_COMPAT (1)
	#define APP__WA_JS(ret, name, args, ...) extern __attribute__((import_module("JS"), import_name(#name "|" #args "|" #__VA_ARGS__))) ret name args;
#elif defined(__linux__) || defined(__unix__)
    /* Linux */
	#define APP_LINUX (1)
	#define GL_ES2_COMPAT (1)
#endif

#if defined(APP_WASM)
	#define APP__EXPORT(func_name) __attribute__((export_name(#func_name)))
#else
	#define APP__EXPORT(func_name)
#endif

#include <stddef.h>

#define __gl_h_ 1
#define __gl32_h_ 1
#define __gl31_h_ 1
#define __GL_H__ 1
#define __glext_h_ 1
#define __GLEXT_H_ 1
#define __gltypes_h_ 1
#define __glcorearb_h_ 1
#define __gl_glcorearb_h_ 1
#define GL_APIENTRY APIENTRY

typedef unsigned int  GLenum;
typedef unsigned int  GLuint;
typedef int  GLsizei;
typedef char  GLchar;
typedef ptrdiff_t  GLintptr;
typedef ptrdiff_t  GLsizeiptr;
typedef double  GLclampd;
typedef unsigned short  GLushort;
typedef unsigned char  GLubyte;
typedef unsigned char  GLboolean;
typedef uint64_t  GLuint64;
typedef double  GLdouble;
typedef unsigned short  GLhalf;
typedef float  GLclampf;
typedef unsigned int  GLbitfield;
typedef signed char  GLbyte;
typedef short  GLshort;
typedef void  GLvoid;
typedef int64_t  GLint64;
typedef float  GLfloat;
typedef struct __GLsync * GLsync;
typedef int  GLint;
#define GL_INT_2_10_10_10_REV 0x8D9F
#define GL_R32F 0x822E
#define GL_PROGRAM_POINT_SIZE 0x8642
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_R16F 0x822D
#define GL_COLOR_ATTACHMENT22 0x8CF6
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_NUM_EXTENSIONS 0x821D
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_VERTEX_SHADER 0x8B31
#define GL_INCR 0x1E02
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_STATIC_DRAW 0x88E4
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_FUNC_SUBTRACT 0x800A
#define GL_FUNC_REVERSE_SUBTRACT 0x800B
#define GL_CONSTANT_COLOR 0x8001
#define GL_DECR_WRAP 0x8508
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_SHORT 0x1402
#define GL_DEPTH_TEST 0x0B71
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_LINK_STATUS 0x8B82
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_RGBA16F 0x881A
#define GL_CONSTANT_ALPHA 0x8003
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_MIN_LOD 0x813A
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#define GL_TEXTURE_WRAP_R 0x8072
#define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#define GL_NEAREST_MIPMAP_NEAREST 0x2700
#define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#define GL_SRC_ALPHA_SATURATE 0x0308
#define GL_STREAM_DRAW 0x88E0
#define GL_ONE 1
#define GL_NEAREST_MIPMAP_LINEAR 0x2702
#define GL_RGB10_A2 0x8059
#define GL_RGBA8 0x8058
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_RGBA4 0x8056
#define GL_RGB8 0x8051
#define GL_ARRAY_BUFFER 0x8892
#define GL_STENCIL 0x1802
#define GL_TEXTURE_2D 0x0DE1
#define GL_DEPTH 0x1801
#define GL_FRONT 0x0404
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_REPEAT 0x2901
#define GL_RGBA 0x1908
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_DECR 0x1E03
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_FLOAT 0x1406
#define GL_TEXTURE_MAX_LOD 0x813B
#define GL_DEPTH_COMPONENT 0x1902
#define GL_ONE_MINUS_DST_ALPHA 0x0305
#define GL_COLOR 0x1800
#define GL_TEXTURE_2D_ARRAY 0x8C1A
#define GL_TRIANGLES 0x0004
#define GL_UNSIGNED_BYTE 0x1401
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#define GL_NONE 0
#define GL_SRC_COLOR 0x0300
#define GL_BYTE 0x1400
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_LINE_STRIP 0x0003
#define GL_TEXTURE_3D 0x806F
#define GL_CW 0x0900
#define GL_LINEAR 0x2601
#define GL_RENDERBUFFER 0x8D41
#define GL_GEQUAL 0x0206
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_RGBA32F 0x8814
#define GL_BLEND 0x0BE2
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_LINEAR_MIPMAP_NEAREST 0x2701
#define GL_EXTENSIONS 0x1F03
#define GL_NO_ERROR 0
#define GL_REPLACE 0x1E01
#define GL_KEEP 0x1E00
#define GL_CCW 0x0901
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_RGB 0x1907
#define GL_TRIANGLE_STRIP 0x0005
#define GL_TRIANGLE_FAN 0x0006
#define GL_FALSE 0
#define GL_ZERO 0
#define GL_CULL_FACE 0x0B44
#define GL_INVERT 0x150A
#define GL_INT 0x1404
#define GL_UNSIGNED_INT 0x1405
#define GL_UNSIGNED_SHORT 0x1403
#define GL_NEAREST 0x2600
#define GL_SCISSOR_TEST 0x0C11
#define GL_LEQUAL 0x0203
#define GL_STENCIL_TEST 0x0B90
#define GL_DITHER 0x0BD0
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_EQUAL 0x0202
#define GL_FRAMEBUFFER 0x8D40
#define GL_RGB5 0x8050
#define GL_LINES 0x0001
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_SRC_ALPHA 0x0302
#define GL_INCR_WRAP 0x8507
#define GL_LESS 0x0201
#define GL_MULTISAMPLE 0x809D
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_BACK 0x0405
#define GL_ALWAYS 0x0207
#define GL_FUNC_ADD 0x8006
#define GL_ONE_MINUS_DST_COLOR 0x0307
#define GL_NOTEQUAL 0x0205
#define GL_DST_COLOR 0x0306
#define GL_COMPILE_STATUS 0x8B81
#if defined (GL_ES2_COMPAT)
	#define GL_RED 0x1909 // GL_LUMINANCE
#else
	#define GL_RED 0x1903
#endif
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_DST_ALPHA 0x0304
#define GL_RGB5_A1 0x8057
#define GL_GREATER 0x0204
#define GL_POLYGON_OFFSET_FILL 0x8037
#define GL_TRUE 1
#define GL_NEVER 0x0200
#define GL_POINTS 0x0000
#define GL_ONE_MINUS_SRC_COLOR 0x0301
#define GL_MIRRORED_REPEAT 0x8370
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_R11F_G11F_B10F 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#define GL_RGBA32UI 0x8D70
#define GL_RGB32UI 0x8D71
#define GL_RGBA16UI 0x8D76
#define GL_RGB16UI 0x8D77
#define GL_RGBA8UI 0x8D7C
#define GL_RGB8UI 0x8D7D
#define GL_RGBA32I 0x8D82
#define GL_RGB32I 0x8D83
#define GL_RGBA16I 0x8D88
#define GL_RGB16I 0x8D89
#define GL_RGBA8I 0x8D8E
#define GL_RGB8I 0x8D8F
#define GL_RED_INTEGER 0x8D94
#define GL_RG 0x8227
#define GL_RG_INTEGER 0x8228
#if defined (GL_ES2_COMPAT)
	#define GL_R8 0x1909 // GL_LUMINANCE
#else
	#define GL_R8 0x8229 
#endif
#define GL_R16 0x822A
#define GL_RG8 0x822B
#define GL_RG16 0x822C
#define GL_R16F 0x822D
#define GL_R32F 0x822E
#define GL_RG16F 0x822F
#define GL_RG32F 0x8230
#define GL_R8I 0x8231
#define GL_R8UI 0x8232
#define GL_R16I 0x8233
#define GL_R16UI 0x8234
#define GL_R32I 0x8235
#define GL_R32UI 0x8236
#define GL_RG8I 0x8237
#define GL_RG8UI 0x8238
#define GL_RG16I 0x8239
#define GL_RG16UI 0x823A
#define GL_RG32I 0x823B
#define GL_RG32UI 0x823C
#define GL_RGBA_INTEGER 0x8D99
#define GL_R8_SNORM 0x8F94
#define GL_RG8_SNORM 0x8F95
#define GL_RGB8_SNORM 0x8F96
#define GL_RGBA8_SNORM 0x8F97
#define GL_R16_SNORM 0x8F98
#define GL_RG16_SNORM 0x8F99
#define GL_RGB16_SNORM 0x8F9A
#define GL_RGBA16_SNORM 0x8F9B
#define GL_RGBA16 0x805B
#define GL_MAX_TEXTURE_SIZE 0x0D33
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#define GL_MAX_3D_TEXTURE_SIZE 0x8073
#define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_TEXTURE_BORDER_COLOR 0x1004
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_PACK_ALIGNMENT 0x0D05

#define APP__GL_FUNCS \
    APP__GL_XMACRO(glBindVertexArray,                 void, (GLuint array)) \
    APP__GL_XMACRO(glFramebufferTextureLayer,         void, (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)) \
    APP__GL_XMACRO(glGenFramebuffers,                 void, (GLsizei n, GLuint * framebuffers)) \
    APP__GL_XMACRO(glBindFramebuffer,                 void, (GLenum target, GLuint framebuffer)) \
    APP__GL_XMACRO(glBindRenderbuffer,                void, (GLenum target, GLuint renderbuffer)) \
    APP__GL_XMACRO(glGetStringi,                      const GLubyte *, (GLenum name, GLuint index)) \
    APP__GL_XMACRO(glClearBufferfi,                   void, (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil)) \
    APP__GL_XMACRO(glClearBufferfv,                   void, (GLenum buffer, GLint drawbuffer, const GLfloat * value)) \
    APP__GL_XMACRO(glClearBufferuiv,                  void, (GLenum buffer, GLint drawbuffer, const GLuint * value)) \
    APP__GL_XMACRO(glClearBufferiv,                   void, (GLenum buffer, GLint drawbuffer, const GLint * value)) \
    APP__GL_XMACRO(glDeleteRenderbuffers,             void, (GLsizei n, const GLuint * renderbuffers)) \
    APP__GL_XMACRO(glUniform1i,                       void, (GLint location, GLint v0)) \
    APP__GL_XMACRO(glUniform2i,                       void, (GLint location, GLint v0, GLint v1)) \
    APP__GL_XMACRO(glUniform1f,                       void, (GLint location, GLfloat v0)) \
    APP__GL_XMACRO(glUniform2f,                       void, (GLint location, GLfloat v0, GLfloat v1)) \
    APP__GL_XMACRO(glUniform3f,                       void, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2)) \
    APP__GL_XMACRO(glUniform4f,                       void, (GLint location, const GLfloat v0, const GLfloat v1, const GLfloat v2, const GLfloat v3)) \
    APP__GL_XMACRO(glUniform1fv,                      void, (GLint location, GLsizei count, const GLfloat * value)) \
    APP__GL_XMACRO(glUniform2fv,                      void, (GLint location, GLsizei count, const GLfloat * value)) \
    APP__GL_XMACRO(glUniform3fv,                      void, (GLint location, GLsizei count, const GLfloat * value)) \
    APP__GL_XMACRO(glUniform4fv,                      void, (GLint location, GLsizei count, const GLfloat * value)) \
    APP__GL_XMACRO(glUniformMatrix4fv,                void, (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)) \
    APP__GL_XMACRO(glUseProgram,                      void, (GLuint program)) \
    APP__GL_XMACRO(glShaderSource,                    void, (GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length)) \
    APP__GL_XMACRO(glLinkProgram,                     void, (GLuint program)) \
    APP__GL_XMACRO(glGetUniformLocation,              GLint, (GLuint program, const GLchar * name)) \
    APP__GL_XMACRO(glGetShaderiv,                     void, (GLuint shader, GLenum pname, GLint * params)) \
    APP__GL_XMACRO(glGetProgramInfoLog,               void, (GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)) \
    APP__GL_XMACRO(glGetAttribLocation,               GLint, (GLuint program, const GLchar * name)) \
    APP__GL_XMACRO(glDisableVertexAttribArray,        void, (GLuint index)) \
    APP__GL_XMACRO(glDeleteShader,                    void, (GLuint shader)) \
    APP__GL_XMACRO(glDeleteProgram,                   void, (GLuint program)) \
    APP__GL_XMACRO(glCompileShader,                   void, (GLuint shader)) \
    APP__GL_XMACRO(glStencilFuncSeparate,             void, (GLenum face, GLenum func, GLint ref, GLuint mask)) \
    APP__GL_XMACRO(glStencilOpSeparate,               void, (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)) \
    APP__GL_XMACRO(glRenderbufferStorageMultisample,  void, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)) \
    APP__GL_XMACRO(glDrawBuffers,                     void, (GLsizei n, const GLenum * bufs)) \
    APP__GL_XMACRO(glVertexAttribDivisor,             void, (GLuint index, GLuint divisor)) \
    APP__GL_XMACRO(glBufferSubData,                   void, (GLenum target, GLintptr offset, GLsizeiptr size, const void * data)) \
    APP__GL_XMACRO(glGenBuffers,                      void, (GLsizei n, GLuint * buffers)) \
    APP__GL_XMACRO(glCheckFramebufferStatus,          GLenum, (GLenum target)) \
    APP__GL_XMACRO(glFramebufferRenderbuffer,         void, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)) \
    APP__GL_XMACRO(glCompressedTexImage2D,            void, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)) \
    APP__GL_XMACRO(glCompressedTexImage3D,            void, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)) \
    APP__GL_XMACRO(glActiveTexture,                   void, (GLenum texture)) \
    APP__GL_XMACRO(glTexSubImage2D,                   void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)) \
    APP__GL_XMACRO(glTexSubImage3D,                   void, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)) \
    APP__GL_XMACRO(glRenderbufferStorage,             void, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height)) \
    APP__GL_XMACRO(glGenTextures,                     void, (GLsizei n, GLuint * textures)) \
    APP__GL_XMACRO(glPolygonOffset,                   void, (GLfloat factor, GLfloat units)) \
    APP__GL_XMACRO(glDrawElements,                    void, (GLenum mode, GLsizei count, GLenum type, const void * indices)) \
    APP__GL_XMACRO(glDeleteFramebuffers,              void, (GLsizei n, const GLuint * framebuffers)) \
    APP__GL_XMACRO(glBlendEquationSeparate,           void, (GLenum modeRGB, GLenum modeAlpha)) \
    APP__GL_XMACRO(glDeleteTextures,                  void, (GLsizei n, const GLuint * textures)) \
    APP__GL_XMACRO(glGetProgramiv,                    void, (GLuint program, GLenum pname, GLint * params)) \
    APP__GL_XMACRO(glBindTexture,                     void, (GLenum target, GLuint texture)) \
    APP__GL_XMACRO(glTexImage3D,                      void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)) \
    APP__GL_XMACRO(glCreateShader,                    GLuint, (GLenum type)) \
    APP__GL_XMACRO(glClearDepth,                      void, (GLdouble depth)) \
    APP__GL_XMACRO(glFramebufferTexture2D,            void, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)) \
    APP__GL_XMACRO(glCreateProgram,                   GLuint, (void)) \
    APP__GL_XMACRO(glViewport,                        void, (GLint x, GLint y, GLsizei width, GLsizei height)) \
    APP__GL_XMACRO(glDeleteBuffers,                   void, (GLsizei n, const GLuint * buffers)) \
    APP__GL_XMACRO(glDrawArrays,                      void, (GLenum mode, GLint first, GLsizei count)) \
    APP__GL_XMACRO(glDrawElementsInstanced,           void, (GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount)) \
    APP__GL_XMACRO(glVertexAttribPointer,             void, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)) \
    APP__GL_XMACRO(glDisable,                         void, (GLenum cap)) \
    APP__GL_XMACRO(glColorMask,                       void, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)) \
    APP__GL_XMACRO(glColorMaski,                      void, (GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)) \
    APP__GL_XMACRO(glBindBuffer,                      void, (GLenum target, GLuint buffer)) \
    APP__GL_XMACRO(glDeleteVertexArrays,              void, (GLsizei n, const GLuint * arrays)) \
    APP__GL_XMACRO(glDepthMask,                       void, (GLboolean flag)) \
    APP__GL_XMACRO(glDrawArraysInstanced,             void, (GLenum mode, GLint first, GLsizei count, GLsizei instancecount)) \
    APP__GL_XMACRO(glClearStencil,                    void, (GLint s)) \
    APP__GL_XMACRO(glScissor,                         void, (GLint x, GLint y, GLsizei width, GLsizei height)) \
    APP__GL_XMACRO(glGenRenderbuffers,                void, (GLsizei n, GLuint * renderbuffers)) \
    APP__GL_XMACRO(glBufferData,                      void, (GLenum target, GLsizeiptr size, const void * data, GLenum usage)) \
    APP__GL_XMACRO(glBlendFuncSeparate,               void, (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)) \
    APP__GL_XMACRO(glTexParameteri,                   void, (GLenum target, GLenum pname, GLint param)) \
    APP__GL_XMACRO(glGetIntegerv,                     void, (GLenum pname, GLint * data)) \
    APP__GL_XMACRO(glEnable,                          void, (GLenum cap)) \
    APP__GL_XMACRO(glBlitFramebuffer,                 void, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)) \
    APP__GL_XMACRO(glStencilMask,                     void, (GLuint mask)) \
    APP__GL_XMACRO(glAttachShader,                    void, (GLuint program, GLuint shader)) \
    APP__GL_XMACRO(glDetachShader,                    void, (GLuint program, GLuint shader)) \
    APP__GL_XMACRO(glGetError,                        GLenum, (void)) \
    APP__GL_XMACRO(glClearColor,                      void, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)) \
    APP__GL_XMACRO(glBlendColor,                      void, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)) \
    APP__GL_XMACRO(glTexParameterf,                   void, (GLenum target, GLenum pname, GLfloat param)) \
    APP__GL_XMACRO(glTexParameterfv,                  void, (GLenum target, GLenum pname, GLfloat* params)) \
    APP__GL_XMACRO(glGetShaderInfoLog,                void, (GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)) \
    APP__GL_XMACRO(glDepthFunc,                       void, (GLenum func)) \
    APP__GL_XMACRO(glStencilOp ,                      void, (GLenum fail, GLenum zfail, GLenum zpass)) \
    APP__GL_XMACRO(glStencilFunc,                     void, (GLenum func, GLint ref, GLuint mask)) \
    APP__GL_XMACRO(glEnableVertexAttribArray,         void, (GLuint index)) \
    APP__GL_XMACRO(glBlendFunc,                       void, (GLenum sfactor, GLenum dfactor)) \
    APP__GL_XMACRO(glReadBuffer,                      void, (GLenum src)) \
    APP__GL_XMACRO(glClear,                           void, (GLbitfield mask)) \
    APP__GL_XMACRO(glTexImage2D,                      void, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)) \
    APP__GL_XMACRO(glGenVertexArrays,                 void, (GLsizei n, GLuint * arrays)) \
    APP__GL_XMACRO(glFrontFace,                       void, (GLenum mode)) \
    APP__GL_XMACRO(glCullFace,                        void, (GLenum mode)) \
    APP__GL_XMACRO(glFinish,                          void, (void)) \
	APP__GL_XMACRO(glPixelStorei,                     void, (GLenum pname, GLint param))


#if defined(WIN32)
	// generate GL function pointer typedefs
	#define APP__GL_XMACRO(name, ret, args) typedef ret (GL_APIENTRY* PFN_ ## name) args;
	APP__GL_FUNCS
	#undef APP__GL_XMACRO
	
	// generate GL extern function pointers
	#define APP__GL_XMACRO(name, ret, args) extern PFN_ ## name name;
	APP__GL_FUNCS
	#undef APP__GL_XMACRO
#elif defined(APP_LINUX)
	// generate extern functions
	#define APP__GL_XMACRO(name, ret, args) extern ret name args;
	APP__GL_FUNCS
	#undef APP__GL_XMACRO
#elif defined(APP_WASM)

	// This doesn't exist on webgl
	void glBindVertexArray(GLuint array) {}

//    APP__WA_JS(void, glFramebufferTextureLayer, (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer), {
//
//	});

    APP__WA_JS(void, glGenFramebuffers, (GLsizei n, GLuint * framebuffers), {
		checkHeap();
		for (var i = 0; i < n; ++i) {
			var framebuffer = Module.GLctx.createFramebuffer();
			if (!framebuffer)
			{
				Module.GLrecordError(0x0502); // GL_INVALID_OPERATION
				while(i < n) HEAP32[(((ids)+(i++*4))>>2)]=0;
				return;
			}
			var id = Module.GLgetNewId(GLframebuffers);
			framebuffer.name = id;
			Module.GLframebuffers[id] = framebuffer;
			HEAP32[(((framebuffers)+(i*4))>>2)] = id;
		}
	})

    APP__WA_JS(void, glBindFramebuffer, (GLenum target, GLuint framebuffer), {
		Module.GLctx.bindFramebuffer(target, framebuffer ? Module.GLframebuffers[framebuffer] : null);
	})

//    APP__WA_JS(void, glBindRenderbuffer, (GLenum target, GLuint renderbuffer), {
//
//	});

//    APP__WA_JS(const GLubyte *, glGetStringi, (GLenum name, GLuint index), {
//
//	});

//    APP__WA_JS(void, glClearBufferfi, (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil), {
//
//	});

//    APP__WA_JS(void, glClearBufferfv, (GLenum buffer, GLint drawbuffer, const GLfloat * value), {
//
//	});
//
//    APP__WA_JS(void, glClearBufferuiv, (GLenum buffer, GLint drawbuffer, const GLuint * value), {
//
//	});
//
//    APP__WA_JS(void, glClearBufferiv, (GLenum buffer, GLint drawbuffer, const GLint * value), {
//
//	});

//    APP__WA_JS(void, glDeleteRenderbuffers,(GLsizei n, const GLuint * renderbuffers), {
//
//	});

    APP__WA_JS(void, glUniform1i, (GLint location, GLint v0), {
		Module.GLctx.uniform1i(Module.GLuniforms[location], v0);
	})

    APP__WA_JS(void, glUniform2i, (GLint location, GLint v0, GLint v1), {
		Module.GLctx.uniform2i(Module.GLuniforms[location], v0, v1);
	})

    APP__WA_JS(void, glUniform1f, (GLint location, GLfloat v0), {
		Module.GLctx.uniform1f(Module.GLuniforms[location], v0);
	})

    APP__WA_JS(void, glUniform2f, (GLint location, GLfloat v0, GLfloat v1), {
		Module.GLctx.uniform2f(Module.GLuniforms[location], v0, v1);
	})

    APP__WA_JS(void, glUniform3f, (GLint location, GLfloat v0, GLfloat v1, GLfloat v2), {
		Module.GLctx.uniform3f(Module.GLuniforms[location], v0, v1, v2);
	})

    APP__WA_JS(void, glUniform4f, (GLint location, const GLfloat v0, const GLfloat v1, const GLfloat v2, const GLfloat v3), {
		Module.GLctx.uniform4f(Module.GLuniforms[loccation], v0, v1, v2, v3);
	})

//    APP__WA_JS(void, glUniform1fv, (GLint location, GLsizei count, const GLfloat * value), {
//
//	});
//
//    APP__WA_JS(void, glUniform2fv, (GLint location, GLsizei count, const GLfloat * value), {
//
//	});

    APP__WA_JS(void, glUniform3fv, (GLint location, GLsizei count, const GLfloat * value), {
		checkHeap();
		var view;
		if (3*count <= Module.GLMINI_TEMP_BUFFER_SIZE) {
			// avoid allocation when uploading few enough uniforms
			view = Module.GLminiTempBufferViews[3*count-1];
			for (var ptr = value>>2, i = 0; i != 3*count; i++) {
				view[i] = HEAPF32[ptr+i];
			}
		}
		else view = HEAPF32.subarray((value)>>2,(value+count*12)>>2);
		Module.GLctx.uniform3fv(Module.GLuniforms[location], view);
	})

//    APP__WA_JS(void, glUniform4fv, (GLint location, GLsizei count, const GLfloat * value), {
//
//	});

    APP__WA_JS(void, glUniformMatrix4fv, (GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), {
		checkHeap();
		count<<=4;
		var view;
		if (count <= Module.GLMINI_TEMP_BUFFER_SIZE)
		{
			// avoid allocation when uploading few enough uniforms
			view = Module.GLminiTempBufferViews[count-1];
			for (var ptr = value>>2, i = 0; i != count; i += 4)
			{
				view[i  ] = HEAPF32[ptr+i  ];
				view[i+1] = HEAPF32[ptr+i+1];
				view[i+2] = HEAPF32[ptr+i+2];
				view[i+3] = HEAPF32[ptr+i+3];
			}
		}
		else view = HEAPF32.subarray((value)>>2,(value+count*4)>>2);
		Module.GLctx.uniformMatrix4fv(Module.GLuniforms[location], !!transpose, view);
	})

    APP__WA_JS(void, glUseProgram, (GLuint program), {
		Module.GLctx.useProgram(program ? Module.GLprograms[program] : null);
	})

    APP__WA_JS(void, glShaderSource, (GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length), {
		checkHeap();
		var source = Module.GLgetSource(shader, count, string, length);
		Module.GLctx.shaderSource(Module.GLshaders[shader], source);
	})
			
    APP__WA_JS(void, glLinkProgram, (GLuint program), {
		Module.GLctx.linkProgram(Module.GLprograms[program]);
		Module.GLprogramInfos[program] = null; // uniforms no longer keep the same names after linking
		Module.GLpopulateUniformTable(program);;
	})

    APP__WA_JS(GLint, glGetUniformLocation, (GLuint program, const GLchar * name), {
		checkHeap();
		name = Pointer_stringify(name);

		var arrayOffset = 0;
		if (name.indexOf(']', name.length-1) !== -1) {
			// If user passed an array accessor "[index]", parse the array index off the accessor.
			var ls = name.lastIndexOf('[');
			var arrayIndex = name.slice(ls+1, -1);
			if (arrayIndex.length > 0)
			{
				arrayOffset = parseInt(arrayIndex);
				if (arrayOffset < 0) return -1;
			}
			name = name.slice(0, ls);
		}

		var ptable = Module.GLprogramInfos[program];
		if (!ptable) return -1;
		var utable = ptable.uniforms;
		var uniformInfo = utable[name]; // returns pair [ dimension_of_uniform_array, uniform_location ]
		if (uniformInfo && arrayOffset < uniformInfo[0]) {
			// Check if user asked for an out-of-bounds element, i.e. for 'vec4 colors[3];' user could ask for 'colors[10]' which should return -1.
			return uniformInfo[1] + arrayOffset;
		}
		return -1;
	})

    APP__WA_JS(void, glGetShaderiv, (GLuint shader, GLenum pname, GLint * params), {
		checkHeap();
		if (!params) {
			// GLES2 specification does not specify how to behave if params is a null pointer. Since calling this function does not make sense
			// if params == null, issue a GL error to notify user about it.
			Module.GLrecordError(0x0501); // GL_INVALID_VALUE
			return;
		}
		if (pname == 0x8B84) { // GL_INFO_LOG_LENGTH
			var log = Module.GLctx.getShaderInfoLog(Module.GLshaders[shader]);
			if (log === null) log = '(unknown error)';
			HEAP32[((params)>>2)] = log.length + 1;
		}
		else if (pname == 0x8B88) { // GL_SHADER_SOURCE_LENGTH
			var source = Module.GLctx.getShaderSource(Module.GLshaders[shader]);
			var sourceLength = (source === null || source.length == 0) ? 0 : source.length + 1;
			HEAP32[((params)>>2)] = sourceLength;
		}
		else HEAP32[((params)>>2)] = Module.GLctx.getShaderParameter(Module.GLshaders[shader], pname);
	})

    APP__WA_JS(void, glGetProgramInfoLog, (GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog), {
		checkHeap();
		var log = Module.GLctx.getProgramInfoLog(Module.GLprograms[program]);
		if (log === null) log = '(unknown error)';
		if (bufSize > 0 && infoLog)
		{
			var numBytesWrittenExclNull = stringToUTF8Array(log, infoLog, bufSize);
			if (length) HEAP32[((length)>>2)]=numBytesWrittenExclNull;
		}
		else if (length) HEAP32[((length)>>2)]=0;
	})

    APP__WA_JS(GLint, glGetAttribLocation, (GLuint program, const GLchar * name), {
		checkHeap();
		program = Module.GLprograms[program];
		name = Pointer_stringify(name);
		return Module.GLctx.getAttribLocation(program, name);
	})

    APP__WA_JS(void, glDisableVertexAttribArray, (GLuint index), {
		Module.GLctx.disableVertexAttribArray(index);
	})

    APP__WA_JS(void, glDeleteShader, (GLuint shader), {
		if (!shader) return;
		var shader_object = Module.GLshaders[shader];
		if (!shader_object)
		{
			// glDeleteShader actually signals an error when deleting a nonexisting object, unlike some other GL delete functions.
			Module.GLrecordError(0x0501); // GL_INVALID_VALUE
			return;
		}
		Module.GLctx.deleteShader(shader_object);
		Module.GLshaders[shader] = null;
	})

    APP__WA_JS(void, glDeleteProgram, (GLuint program), {
		if (!program) return;
		var program_object = Module.GLprograms[program];
		if (!program_object) 
		{
			// glDeleteProgram actually signals an error when deleting a nonexisting object, unlike some other GL delete functions.
			Module.GLrecordError(0x0501); // GL_INVALID_VALUE
			return;
		}
		Module.GLctx.deleteProgram(program_object);
		program_object.name = 0;
		Module.GLprograms[program] = null;
		Module.GLprogramInfos[program] = null;
	})

    APP__WA_JS(void, glCompileShader, (GLuint shader), {
		Module.GLctx.compileShader(Module.GLshaders[shader]);
	})

//    APP__WA_JS(void, glStencilFuncSeparate, (GLenum face, GLenum func, GLint ref, GLuint mask), {
//
//	});
//
//    APP__WA_JS(void, glStencilOpSeparate, (GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass), {
//
//	});

//    APP__WA_JS(void, glRenderbufferStorageMultisample, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height), {
//
//	});

//    APP__WA_JS(void, glDrawBuffers, (GLsizei n, const GLenum * bufs), {
//
//	});

//    APP__WA_JS(void, glVertexAttribDivisor, (GLuint index, GLuint divisor), {
//
//	});

    APP__WA_JS(void, glBufferSubData, (GLenum target, GLintptr offset, GLsizeiptr size, const void * data), {
		checkHeap();
		Module.GLctx.bufferSubData(target, offset, HEAPU8.subarray(data, data+size));
	})

    APP__WA_JS(void, glGenBuffers, (GLsizei n, GLuint *buffers), {
		checkHeap();
		for (var i = 0; i < n; i++) {
			var buffer = Module.GLctx.createBuffer();
			if (!buffer) {
				Module.GLrecordError(0x0502); // GL_INVALID_OPERATION
				while(i < n) HEAP32[(((buffers)+(i++*4))>>2)]=0;
				return;
			}
			var id = Module.GLgetNewId(Module.GLbuffers);
			buffer.name = id;
			Module.GLbuffers[id] = buffer;
			HEAP32[(((buffers)+(i*4))>>2)]=id;
		}
	})

//    APP__WA_JS(GLenum, glCheckFramebufferStatus, (GLenum target), {
//
//	});

//    APP__WA_JS(void, glFramebufferRenderbuffer, (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer), {
//
//	});

//    APP__WA_JS(void, glCompressedTexImage2D, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data), {
//
//	});
//
//    APP__WA_JS(void, glCompressedTexImage3D, (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data), {
//
//	});

    APP__WA_JS(void, glActiveTexture, (GLenum texture), {
		Module.GLctx.activeTexture(texture);
	})

    APP__WA_JS(void, glTexSubImage2D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels), {
		checkHeap();
		var pixelData = null;
		if (pixels) pixelData = Module.webGLGetTexPixelData(type, format, width, height, pixels, 0);
		Module.GLctx.texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixelData);
	})

//    APP__WA_JS(void, glTexSubImage3D, (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels), {
//
//	});

//    APP__WA_JS(void, glRenderbufferStorage, (GLenum target, GLenum internalformat, GLsizei width, GLsizei height), {
//
//	});

    APP__WA_JS(void, glGenTextures, (GLsizei n, GLuint * textures), {
		checkHeap();
		for (var i = 0; i < n; i++) {
			var texture = Module.GLctx.createTexture();
			if (!texture) {
				// GLES + EGL specs don't specify what should happen here, so best to issue an error and create IDs with 0.
				Module.GLrecordError(0x0502); // GL_INVALID_OPERATION
				while(i < n) HEAP32[(((textures)+(i++*4))>>2)]=0;
				return;
			}
			var id = Module.GLgetNewId(Module.GLtextures);
			texture.name = id;
			Module.GLtextures[id] = texture;
			HEAP32[(((textures)+(i*4))>>2)]=id;
		}
	})

//    APP__WA_JS(void, glPolygonOffset, (GLfloat factor, GLfloat units), {
//
//	});

    APP__WA_JS(void, glDrawElements, (GLenum mode, GLsizei count, GLenum type, const void * indices), {
		Module.GLctx.drawElements(mode, count, type, indices);
	})

    APP__WA_JS(void, glDeleteFramebuffers, (GLsizei n, const GLuint *framebuffers), {
		checkHeap();
		for (var i = 0; i < n; ++i)
		{
			var id = HEAP32[(((framebuffers)+(i*4))>>2)];
			var framebuffer = Module.GLframebuffers[id];
			if (!framebuffer) continue; // GL spec: "glDeleteFramebuffers silently ignores 0s and names that do not correspond to existing framebuffer objects".
			Module.GLctx.deleteFramebuffer(framebuffer);
			framebuffer.name = 0;
			Module.GLframebuffers[id] = null;
		}
	})

    APP__WA_JS(void, glBlendEquationSeparate, (GLenum modeRGB, GLenum modeAlpha), {
		Module.GLctx.blendEquationSeparate(modeRGB, modeAlpha);
	})

    APP__WA_JS(void, glDeleteTextures, (GLsizei n, const GLuint *textures), {
		checkHeap();
		for (var i = 0; i < n; i++) {
			var id = HEAP32[(((textures)+(i*4))>>2)];
			var texture = Module.GLtextures[id];
			if (!texture) continue; // GL spec: "glDeleteTextures silently ignores 0s and names that do not correspond to existing textures".
			Module.GLctx.deleteTexture(texture);
			texture.name = 0;
			Module.GLtextures[id] = null;
		}
	})

    APP__WA_JS(void, glGetProgramiv, (GLuint program, GLenum pname, GLint * params), {
		checkHeap();
		if (!params) {
			// GLES2 specification does not specify how to behave if params is a null pointer. Since calling this function does not make sense
			// if params == null, issue a GL error to notify user about it.
			Module.GLrecordError(0x0501); // GL_INVALID_VALUE
			return;
		}

		if (program >= GLcounter) {
			Module.GLrecordError(0x0501); // GL_INVALID_VALUE
			return;
		}

		var ptable = Module.GLprogramInfos[program];
		if (!ptable) {
			Module.GLrecordError(0x0502); //GL_INVALID_OPERATION
			return;
		}

		if (pname == 0x8B84) { // GL_INFO_LOG_LENGTH
			var log = Module.GLctx.getProgramInfoLog(Module.GLprograms[program]);
			if (log === null) log = '(unknown error)';
			HEAP32[((params)>>2)] = log.length + 1;
		}
		else if (pname == 0x8B87) { //GL_ACTIVE_UNIFORM_MAX_LENGTH
			HEAP32[((params)>>2)] = ptable.maxUniformLength;
		}
		else if (pname == 0x8B8A) { //GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
			if (ptable.maxAttributeLength == -1) {
				program = Module.GLprograms[program];
				var numAttribs = Module.GLctx.getProgramParameter(program, Module.GLctx.ACTIVE_ATTRIBUTES);
				ptable.maxAttributeLength = 0; // Spec says if there are no active attribs, 0 must be returned.
				for (var i = 0; i < numAttribs; ++i) {
					var activeAttrib = Module.GLctx.getActiveAttrib(program, i);
					ptable.maxAttributeLength = Math.max(ptable.maxAttributeLength, activeAttrib.name.length+1);
				}
			}
			HEAP32[((params)>>2)] = ptable.maxAttributeLength;
		}
		else if (pname == 0x8A35) { //GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH
			if (ptable.maxUniformBlockNameLength == -1) {
				program = Module.GLprograms[program];
				var numBlocks = Module.GLctx.getProgramParameter(program, GLctx.ACTIVE_UNIFORM_BLOCKS);
				ptable.maxUniformBlockNameLength = 0;
				for (var i = 0; i < numBlocks; ++i) {
					var activeBlockName = Module.GLctx.getActiveUniformBlockName(program, i);
					ptable.maxUniformBlockNameLength = Math.max(ptable.maxUniformBlockNameLength, activeBlockName.length+1);
				}
			}
			HEAP32[((params)>>2)] = ptable.maxUniformBlockNameLength;
		} else {
			HEAP32[((params)>>2)] = Module.GLctx.getProgramParameter(Module.GLprograms[program], pname);
		}
	})

    APP__WA_JS(void, glBindTexture, (GLenum target, GLuint texture), {
		Module.GLctx.bindTexture(target, texture ? Module.GLtextures[texture] : null);
	})

    APP__WA_JS(void, glTexImage2D, (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels), {
		checkHeap();
		var pixelData = null;
		if (pixels) pixelData = Module.webGLGetTexPixelData(type, format, width, height, pixels, internalFormat);
		Module.GLctx.texImage2D(target, level, internalFormat, width, height, border, format, type, pixelData);
	})

//    APP__WA_JS(void, glTexImage3D, (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels), {
//
//	});

    APP__WA_JS(GLuint, glCreateShader, (GLenum type), {
		var id = Module.GLgetNewId(Module.GLshaders);
		Module.GLshaders[id] = Module.GLctx.createShader(type);
		return id;
	})

//    APP__WA_JS(void, glClearDepth, (GLdouble depth), {
//
//	});

    APP__WA_JS(void, glFramebufferTexture2D, (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level), {
		Module.GLctx.framebufferTexture2D(target, attachment, textarget, Module.GLtextures[texture], level);
	})

    APP__WA_JS(GLuint, glCreateProgram, (void), {
		var id = Module.GLgetNewId(Module.GLprograms);
		var program = Module.GLctx.createProgram();
		program.name = id;
		Module.GLprograms[id] = program;
		return id;
	})

    APP__WA_JS(void, glViewport, (GLint x, GLint y, GLsizei width, GLsizei height), {
		Module.GLctx.viewport(x, y, width, height);
	})

    APP__WA_JS(void, glDeleteBuffers, (GLsizei n, const GLuint *buffers), {
		checkHeap();
		for (var i = 0; i < n; i++) {
			var id = HEAP32[(((buffers)+(i*4))>>2)];
			var buffer = Module.GLbuffers[id];

			// From spec: "glDeleteBuffers silently ignores 0's and names that do not correspond to existing buffer objects."
			if (!buffer) continue;

			Module.GLctx.deleteBuffer(buffer);
			buffer.name = 0;
			Module.GLbuffers[id] = null;
		}
	})

    APP__WA_JS(void, glDrawArrays, (GLenum mode, GLint first, GLsizei count), {
		Module.GLctx.drawArrays(mode, first, count);
	})

//    APP__WA_JS(void, glDrawElementsInstanced, (GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount), {
//
//	});

    APP__WA_JS(void, glVertexAttribPointer, (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer), {
		Module.GLctx.vertexAttribPointer(index, size, type, !!normalized, stride, pointer);
	})

    APP__WA_JS(void, glDisable, (GLenum cap), {
		Module.GLctx.disable(cap);
	})

    APP__WA_JS(void, glColorMask, (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha), {
		Module.GLctx.colorMask(!!red, !!green, !!blue, !!alpha);
	})

//    APP__WA_JS(void, glColorMaski, (GLuint buf, GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha), {
//
//	});

    APP__WA_JS(void, glBindBuffer, (GLenum target, GLuint buffer), {
		Module.GLctx.bindBuffer(target, buffer ? Module.GLbuffers[buffer] : null); 
	})

//    APP__WA_JS(void, glDeleteVertexArrays, (GLsizei n, const GLuint *arrays), {
//
//	});

    APP__WA_JS(void, glDepthMask, (GLboolean flag), {
		Module.GLctx.depthMask(!!flag);
	})

//    APP__WA_JS(void, glDrawArraysInstanced, (GLenum mode, GLint first, GLsizei count, GLsizei instancecount), {
//
//	});

//    APP__WA_JS(void, glClearStencil, (GLint s), {
//
//	});

    APP__WA_JS(void, glScissor, (GLint x, GLint y, GLsizei width, GLsizei height), {
		Module.GLctx.scissor(x, y, width, height);
	})

//    APP__WA_JS(void, glGenRenderbuffers, (GLsizei n, GLuint * renderbuffers), {
//
//	});

    APP__WA_JS(void, glBufferData, (GLenum target, GLsizeiptr size, const void *data, GLenum usage), {
		checkHeap();
		if (!data) Module.GLctx.bufferData(target, size, usage);
		else Module.GLctx.bufferData(target, HEAPU8.subarray(data, data+size), usage);
	})

    APP__WA_JS(void, glBlendFuncSeparate, (GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha), {
		Module.GLctx.blendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
	})

    APP__WA_JS(void, glTexParameteri, (GLenum target, GLenum pname, GLint param), {
		Module.GLctx.texParameteri(target, pname, param);
	})

    APP__WA_JS(void, glGetIntegerv, (GLenum pname, GLint *data), {
		Module.webGLGet(pname, data, 'Integer');
	})

    APP__WA_JS(void, glEnable, (GLenum cap), {
		Module.GLctx.enable(cap);
	})

//    APP__WA_JS(void, glBlitFramebuffer, (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter), {
//
//	});

//    APP__WA_JS(void, glStencilMask, (GLuint mask), {
//
//	});

    APP__WA_JS(void, glAttachShader, (GLuint program, GLuint shader), {
		Module.GLctx.attachShader(Module.GLprograms[program], Module.GLshaders[shader]);
	})

    APP__WA_JS(void, glDetachShader, (GLuint program, GLuint shader), {
		Module.GLctx.detachShader(Module.GLprograms[program], Module.GLshaders[shader]);
	})

    APP__WA_JS(GLenum, glGetError, (void), {
		if (Module.GLlastError) {
			var e = Module.GLlastError;
			Module.GLlastError = 0;
			return e;
		}
		return Module.GLctx.getError();
	})

    APP__WA_JS(void, glClearColor, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha), {
		Module.GLctx.clearColor(red, green, blue, alpha);
	})

    APP__WA_JS(void, glBlendColor, (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha), {
		Module.GLctx.blendColor(red, green, blue, alpha);
	})

//    APP__WA_JS(void, glTexParameterf, (GLenum target, GLenum pname, GLfloat param), {
//
//	});
//
//    APP__WA_JS(void, glTexParameterfv, (GLenum target, GLenum pname, GLfloat* params), {
//
//	});

    APP__WA_JS(void, glGetShaderInfoLog, (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog), {
		checkHeap();
		var log = Module.GLctx.getShaderInfoLog(Module.GLshaders[shader]);
		if (log === null) log = '(unknown error)';
		if (bufSize > 0 && infoLog)
		{
			var numBytesWrittenExclNull = stringToUTF8Array(log, infoLog, bufSize);
			if (length) HEAP32[((length)>>2)] = numBytesWrittenExclNull;
		}
		else if (length) HEAP32[((length)>>2)] = 0;
	})

    APP__WA_JS(void, glDepthFunc, (GLenum func), {
		Module.GLctx.depthFunc(func);
	})

//    APP__WA_JS(void, glStencilOp, (GLenum fail, GLenum zfail, GLenum zpass), {
//
//	});
//
//    APP__WA_JS(void, glStencilFunc, (GLenum func, GLint ref, GLuint mask), {
//
//	});

    APP__WA_JS(void, glEnableVertexAttribArray, (GLuint index), {
		Module.GLctx.enableVertexAttribArray(index);
	})

    APP__WA_JS(void, glBlendFunc, (GLenum sfactor, GLenum dfactor), {
		Module.GLctx.blendFunc(sfactor, dfactor);
	})

//    APP__WA_JS(void, glReadBuffer, (GLenum src), {
//
//	});

    APP__WA_JS(void, glClear, (GLbitfield mask), {
		Module.GLctx.clear(mask);
	})

	// This doesn't exist on webgl
    void glGenVertexArrays(GLsizei n, GLuint * arrays) {}

//    APP__WA_JS(void, glFrontFace, (GLenum mode), {
//
//	});
//
//    APP__WA_JS(void, glCullFace, (GLenum mode), {
//
//	});

//    APP__WA_JS(void, glFinish, (void), {
//
//	});

	APP__WA_JS(void, glPixelStorei, (GLenum pname, GLint param), {
		if (pname == 0x0D05) Module.GLpackAlignment = param; //GL_PACK_ALIGNMENT
		else if (pname == 0x0cf5) Module.GLunpackAlignment = param; //GL_UNPACK_ALIGNMENT
		Module.GLctx.pixelStorei(pname, param);
	})

#endif








#ifndef APP__TEXT_INPUT_BUFFER_MAX
	#define APP__TEXT_INPUT_BUFFER_MAX 1024
#endif

APP_INTERNAL const char APP__default_text_input_filter[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 31, 127};


typedef enum {
	APP__KEY_STATUS_UP = 0x1,
	APP__KEY_STATUS_PRESSED = 0x2,
	APP__KEY_STATUS_DOWN = 0x4,
	APP__KEY_STATUS_RELEASED = 0x8,
	APP__KEY_STATUS_REPEAT = 0x10,
} APP__KeyStatus;


#ifndef APP__MAX_TOUCH_POINTS
	#define APP__MAX_TOUCH_POINTS 10
#endif

#define APP__MAX_FRAME_DURATION_SAMPLES 255

//
// Global struct that will contain all the crossplatform application data
//
APP_INTERNAL struct {

	int(*frame_callback)(void);

	int  w_width;
	int  w_height;
	int  default_width;
	int  default_height;
	bool window_resized;
	bool fullscreen_changed;
    unsigned char keyboard[APP_MAX_KEYCODES];
	struct {
		float x;
		float y;
		unsigned char buttons[3];
		float wheel_x;
		float wheel_y;
	} mouse;

	bool focus;

	// NOTE(Tano): We may split this into SOA (structures of arrays) to get more performance but
	// anyway...
	struct {
		int id;
		float x;
		float y;
		float force;
		unsigned char state;
	} touch_points[APP__MAX_TOUCH_POINTS];

	struct {
		float x;
		float y;
		unsigned char state;
	} pointer;

	bool quit_requested;

	char text_input_buffer[APP__TEXT_INPUT_BUFFER_MAX];
	unsigned int text_input_bytes_count;

	const char *text_input_filter;
	unsigned int text_input_filter_len;

	// Manage frame duration and statistics
	int64_t prev_time;
	int64_t frame_duration_samples[APP__MAX_FRAME_DURATION_SAMPLES];
	int frame_duration_samples_count;
	int frame_duration_samples_head;

	// Sound player information
	struct SoundPlayerInfo {
		int sample_rate;
		int num_channels;
		int buffer_frames;
		void *user_data;
		APP_SoundPlayerCallback stream_cb;
	} sound_player_info;

} APP__data = {
	.text_input_filter = APP__default_text_input_filter,
	.text_input_filter_len = sizeof(APP__default_text_input_filter),
};







#if defined(APP_LINUX)

#include <pthread.h>
typedef pthread_mutex_t Mutex;

#elif defined(APP_WINDOWS)

typedef HANDLE Mutex;

#elif defined(APP_WASM)

typedef bool Mutex;

#endif

void
Mutex_init(Mutex *mutex);


void
Mutex_deinit(Mutex *mutex);


void
Mutex_lock(Mutex *mutex);


void
Mutex_unlock(Mutex *mutex);




/////////////////////////////////////////////////////////////////////////////////
//
//
//
//    IMPLEMENTATION STARTS HERE
//
// | | | | | | | | | | | | | | | | | |
// V V V V V V V V V V V V V V V V V V
/////////////////////////////////////////////////////////////////////////////////


APP__EXPORT(APP__Report_mouse_button_down) void
APP__Report_mouse_button_down(APP_MouseButton button_id);

APP__EXPORT(APP__Report_mouse_button_up) void
APP__Report_mouse_button_up(APP_MouseButton button_id);

APP__EXPORT(APP__Report_mouse_move) void
APP__Report_mouse_move(float x, float y);

APP__EXPORT(APP__Report_touch_event) void
APP__Report_touch_event(int id, int state, float x, float y);

APP__EXPORT(APP__Handle_frame) int
APP__Handle_frame(void);

#if defined (APP_LINUX)

	APP_INTERNAL int     APP__linux_Init(const char *title, int width, int height);
	APP_INTERNAL void    APP__linux_Shutdown(void);
	APP_INTERNAL void    APP__linux_Process_events(void);
	APP_INTERNAL void    APP__linux_Swap_buffers(void);
	APP_INTERNAL void    APP__linux_Set_fullscreen(bool enable);
	APP_INTERNAL void    APP__linux_Set_swap_interval(unsigned int interval);
	APP_INTERNAL void    APP__linux_Show_mouse(bool show);
	APP_INTERNAL void    APP__linux_Set_window_title(const char *title);
	APP_INTERNAL int64_t APP__linux_Time(void);

#elif defined (APP_WINDOWS)

	APP_INTERNAL int     APP__win32_Init(const char *title, int width, int height);
	APP_INTERNAL void    APP__win32_Shutdown(void);
	APP_INTERNAL void    APP__win32_Process_events(void);
	APP_INTERNAL void    APP__win32_Swap_buffers(void);
	APP_INTERNAL void    APP__win32_Set_fullscreen(bool enable);
	APP_INTERNAL void    APP__win32_Set_swap_interval(unsigned int interval);
	APP_INTERNAL void    APP__win32_Show_mouse(bool show);
	APP_INTERNAL void    APP__win32_Set_window_title(const char *title);
	APP_INTERNAL int64_t APP__win32_Time(void);

#elif defined (APP_WASM)

	static struct {
		int64_t initial_time;
	} APP__wasm_data = {0};

	APP_INTERNAL int     APP__wasm_Init(const char *title, int width, int height);
	APP_INTERNAL void    APP__wasm_Shutdown(void);
	APP_INTERNAL void    APP__wasm_Process_events(void);
	APP_INTERNAL void    APP__wasm_Set_fullscreen(bool enable);
	APP_INTERNAL void    APP__wasm_Show_mouse(bool show);
	APP_INTERNAL void    APP__wasm_Set_window_title(const char *title);
	APP_INTERNAL int64_t APP__wasm_Time(void);
#endif

APP_PUBLIC int
APP_Init(const char *title, int width, int height) {

	APP__data.focus = true;

	// Init the touch points id
	for (int i = 0; i < APP__MAX_TOUCH_POINTS; i+=1) {
		APP__data.touch_points[i].id = -1;
	}

	#if defined (APP_LINUX)
		return APP__linux_Init(title, width, height);
	#elif defined (APP_WINDOWS)
		return APP__win32_Init(title, width, height);
	#elif defined (APP_WASM)
		return APP__wasm_Init(title, width, height);
	#endif

	APP__data.prev_time = APP_Time();
}

// Destroys the window
APP_PUBLIC void
APP_Destroy_window(void) {
	#if defined (APP_LINUX)
		APP__linux_Shutdown();
	#elif defined (APP_WINDOWS)
		APP__win32_Shutdown();
	#elif defined (APP_WASM)
		APP__wasm_Shutdown();
	#endif
}


APP_PUBLIC int
APP_Get_window_width(void) {
	return APP__data.w_width;
}


APP_PUBLIC int
APP_Get_window_height(void) {
	return APP__data.w_height;
}

APP_PUBLIC bool
APP_Window_resized(void) {
	return APP__data.window_resized;
}

APP_PUBLIC bool
APP_Quit_requested(void) {
	return APP__data.quit_requested;
}

APP_PUBLIC bool
APP_Is_key_up(APP_KeyCode key) {
	bool result = (APP__data.keyboard[key] & APP__KEY_STATUS_UP) != 0;
	return result;
}

APP_PUBLIC bool
APP_Is_key_pressed(APP_KeyCode key) {
	bool result = (APP__data.keyboard[key] & APP__KEY_STATUS_PRESSED) != 0;
	return result;
}

APP_PUBLIC bool
APP_Is_key_down(APP_KeyCode key) {
	bool result = (APP__data.keyboard[key] & APP__KEY_STATUS_DOWN) != 0;
	return result;
}


APP_PUBLIC bool
APP_Is_key_released(APP_KeyCode key) {
	bool result = (APP__data.keyboard[key] & APP__KEY_STATUS_RELEASED) != 0;
	return result;
}

APP_PUBLIC bool
APP_Is_key_repeat(APP_KeyCode key) {
	bool result = (APP__data.keyboard[key] & APP__KEY_STATUS_REPEAT) != 0;
	return result;
}


APP_PUBLIC const char *
APP_Get_text_input(void) {
	return APP__data.text_input_buffer;
}


APP_PUBLIC unsigned int
APP_Get_text_input_length(void) {
	return APP__data.text_input_bytes_count;
}


APP_PUBLIC float
APP_Get_mouse_x(void) {
	float result = APP__data.mouse.x;
	return result;
}


APP_PUBLIC float
APP_Get_mouse_y(void) {
	float result = APP__data.mouse.y;
	return result;
}


APP_PUBLIC float
APP_Get_mouse_y_inv(void) {
	float y = APP__data.mouse.y;
	float w_height = APP__data.w_height;
	float result = w_height - y;
	return result;
}


APP_PUBLIC bool
APP_Is_mouse_button_down(APP_MouseButton button) {
	bool result = APP__data.mouse.buttons[button] == APP__KEY_STATUS_DOWN;
	return result;
}



APP_PUBLIC bool
APP_Is_mouse_button_pressed(APP_MouseButton button) {
	bool result = APP__data.mouse.buttons[button] == APP__KEY_STATUS_PRESSED;
	return result;
}


APP_PUBLIC bool
APP_Is_mouse_button_released(APP_MouseButton button) {
	bool result = APP__data.mouse.buttons[button] == APP__KEY_STATUS_RELEASED;
	return result;
}


APP_PUBLIC bool
APP_Is_mouse_button_up(APP_MouseButton button) {
	bool result = APP__data.mouse.buttons[button] == APP__KEY_STATUS_UP;
	return result;
}


APP_PUBLIC float
APP_Get_wheel_x(void) {
	return APP__data.mouse.wheel_x;
}

APP_PUBLIC float
APP_Get_wheel_y(void) {
	return APP__data.mouse.wheel_y;
}


APP_PUBLIC float
APP_Get_touch_x(int id) {
	if (id < 0 || id >= APP__MAX_TOUCH_POINTS) return 0.0f;
	return APP__data.touch_points[id].x;
}

APP_PUBLIC float
APP_Get_touch_y(int id) {
	if (id < 0 || id >= APP__MAX_TOUCH_POINTS) return 0.0f;
	return APP__data.touch_points[id].y;
}

APP_PUBLIC unsigned char
APP_Get_touch_state(int id) {
	if (id < 0 || id >= APP__MAX_TOUCH_POINTS) return APP_TOUCH_STATE_INVALID;
	return APP__data.touch_points[id].state;
}

APP_PUBLIC float
APP_Get_pointer_x(void) {
	return APP__data.pointer.x;
}

APP_PUBLIC float
APP_Get_pointer_y(void) {
	return APP__data.pointer.y;
}

APP_PUBLIC unsigned char
APP_Get_pointer_state(void) {
	return APP__data.pointer.state;
}


APP_PUBLIC void
APP_Set_fullscreen(bool enable) {
	#if defined (APP_LINUX)
		APP__linux_Set_fullscreen(enable);
	#elif defined (APP_WINDOWS)
		APP__win32_Set_fullscreen(enable);
	#elif defined (APP_WASM)
		APP__wasm_Set_fullscreen(enable);
	#endif
}


APP_PUBLIC void
APP_Set_swap_interval(unsigned int interval) {
	#if defined (APP_LINUX)
		APP__linux_Set_swap_interval(interval);
	#elif defined (APP_WINDOWS)
		APP__win32_Set_swap_interval(interval);
	#elif defined (APP_WASM)
		// This doesn't work on wasm
	#endif
}

APP_PUBLIC void
APP_Show_mouse(bool show) {
	#if defined (APP_LINUX)
		APP__linux_Show_mouse(show);
	#elif defined (APP_WINDOWS)
		APP__win32_Show_mouse(show);
	#elif defined (APP_WASM)
		APP__wasm_Show_mouse(show);
	#endif
}

APP_PUBLIC void
APP_Set_window_title(const char *title) {
	#if defined (APP_LINUX)
		APP__linux_Set_window_title(title);
	#elif defined (APP_WINDOWS)
		APP__win32_Set_window_title(title);
	#elif defined (APP_WASM)
		APP__wasm_Set_window_title(title);
	#endif
}

APP_PUBLIC int64_t
APP_Time(void) {
	#if defined (APP_LINUX)
		return APP__linux_Time();
	#elif defined (APP_WINDOWS)
		return APP__win32_Time();
	#elif defined (APP_WASM)
		return APP__wasm_Time();
	#endif
}

APP_PUBLIC int64_t
APP_Frame_duration(int samples) {
	
	if (APP__data.frame_duration_samples_count < samples) {
		samples = APP__data.frame_duration_samples_count;
	}
	if (samples == 0) {
		return 0;
	}

	int head = APP__data.frame_duration_samples_head;
	int64_t acum = 0;
	for (int i = 0; i < samples; i+=1) {
		acum += APP__data.frame_duration_samples[(head+i)%APP__MAX_FRAME_DURATION_SAMPLES];
	}
	
	acum /= (int64_t)samples;

	return acum;
}


APP_INTERNAL bool
APP__Is_char_filtered(char c) {
	const int total = APP__data.text_input_filter_len;
	const char *filter = APP__data.text_input_filter;
	for (int i = 0; i < total; ++i) {
		if (c == filter[i]) return true;
	}
	return false;
}


APP_INTERNAL void
APP__Clear_events(void) {

	// Clear the text input stuff
	APP__data.text_input_buffer[0] = '\0';
	APP__data.text_input_bytes_count = 0;

	// We have to reset the window resize event every frame.
	APP__data.window_resized = false;

	// We must trigger the windows resize event if we went to fullscreen, the right dimensions
	// are informed when the fullscreen has changed.
	// On x11 and wasm the resize event is triggered anyway, so this doesn't matter.
	if (APP__data.fullscreen_changed == true) {
		APP__data.fullscreen_changed = false;
		APP__data.window_resized = true;
	}
	
	// The keys that are UP must be NONE the next frame
	for (int i = 0; i < APP_MAX_KEYCODES; ++i) {
		if (APP__data.keyboard[i] & APP__KEY_STATUS_REPEAT) {
			APP__data.keyboard[i] &= (~APP__KEY_STATUS_REPEAT);
		}
		if (APP__data.keyboard[i] & APP__KEY_STATUS_PRESSED) {
			APP__data.keyboard[i] = APP__KEY_STATUS_DOWN;
		}
		if (APP__data.keyboard[i] & APP__KEY_STATUS_RELEASED) {
			APP__data.keyboard[i] = APP__KEY_STATUS_UP;
		}
	}

	// The same with mouse buttons
	for (int i = 0; i < 3; i+=1) {
		if (APP__data.mouse.buttons[i] & APP__KEY_STATUS_PRESSED) {
			APP__data.mouse.buttons[i] = APP__KEY_STATUS_DOWN;
		}
		if (APP__data.mouse.buttons[i] & APP__KEY_STATUS_RELEASED) {
			APP__data.mouse.buttons[i] = APP__KEY_STATUS_UP;
		}
	}

	APP__data.mouse.wheel_x = 0.0f;
	APP__data.mouse.wheel_y = 0.0f;

	// Clear the touch points
	for (int i = 0; i < APP__MAX_TOUCH_POINTS; i+=1) {
		if (APP__data.touch_points[i].state & (APP_TOUCH_STATE_END|APP_TOUCH_STATE_CANCEL)) {
			APP__data.touch_points[i].state = APP_TOUCH_STATE_INVALID;
			APP__data.touch_points[i].id = -1;
		}
	}

	if (APP__data.pointer.state & APP_POINTER_STATE_PRESSED)  APP__data.pointer.state = APP_POINTER_STATE_DOWN;
	if (APP__data.pointer.state & APP_POINTER_STATE_RELEASED) APP__data.pointer.state = APP_POINTER_STATE_UP;
	if (APP__data.pointer.state == APP_POINTER_STATE_INVALID) APP__data.pointer.state = APP_POINTER_STATE_UP;
}


APP_INTERNAL void
APP__Put_keys_up(void) {
	// The keys that are DOWN go UP
	for (int i = 0; i < APP_MAX_KEYCODES; ++i) {
		if (APP__data.keyboard[i] == APP__KEY_STATUS_PRESSED ||
			APP__data.keyboard[i] == APP__KEY_STATUS_DOWN) {

			APP__data.keyboard[i] = APP__KEY_STATUS_RELEASED;
		}
	}
	// The same with mouse buttons
	for (int i = 0; i < 3; ++i) {
		if (APP__data.mouse.buttons[i] == APP__KEY_STATUS_PRESSED ||
			APP__data.keyboard[i] == APP__KEY_STATUS_DOWN) {

			APP__data.mouse.buttons[i] = APP__KEY_STATUS_RELEASED;
		}
	}
}

void
APP__Report_mouse_button_down(APP_MouseButton button_id) {

	if (button_id < APP_MOUSE_BUTTON_LEFT || button_id >= APP_MOUSE_BUTTON_INVALID) return;
	if (APP__data.mouse.buttons[button_id] == APP__KEY_STATUS_PRESSED ||
		APP__data.mouse.buttons[button_id] == APP__KEY_STATUS_DOWN) {

		APP__data.mouse.buttons[button_id] = APP__KEY_STATUS_DOWN;
	}
	else {
		APP__data.mouse.buttons[button_id] = APP__KEY_STATUS_PRESSED;
	}

	// Handle pointer case
	if (button_id == APP_MOUSE_BUTTON_LEFT) {
		if (APP__data.pointer.state & APP_POINTER_STATE_PRESSED) {
			APP__data.pointer.state = APP_POINTER_STATE_DOWN;
		}
		else {
			APP__data.pointer.state = (APP_POINTER_STATE_PRESSED|APP_POINTER_STATE_DOWN);
		}
	}
}

void
APP__Report_mouse_button_up(APP_MouseButton button_id) {
	if (button_id < APP_MOUSE_BUTTON_LEFT || button_id >= APP_MOUSE_BUTTON_INVALID) return;
	APP__data.mouse.buttons[button_id] = APP__KEY_STATUS_RELEASED;

	// Handle pointer case
	if (button_id == APP_MOUSE_BUTTON_LEFT) {
		APP__data.pointer.state = (APP_POINTER_STATE_RELEASED|APP_POINTER_STATE_UP);
	}
}

void
APP__Report_mouse_move(float x, float y) {
	APP__data.mouse.x = x;
	APP__data.mouse.y = y;
	APP__data.pointer.x = x;
	APP__data.pointer.y = y;
}


void
APP__Report_touch_event(int id, int state, float x, float y) {
	int target_index = -1;
	for (int i = 0; i < APP__MAX_TOUCH_POINTS; i+=1) {
		// We set the target to the first invalid point that we see
		if (APP__data.touch_points[i].state == APP_TOUCH_STATE_INVALID && target_index < 0)  target_index = i;
		// If the touch point already exists and has a valid state we target it
		else if (APP__data.touch_points[i].id == id) {
			target_index = i;
			break;
		}
	}
	// If the target index is less than 0 means that all the touch points are in use
	if (target_index >= 0) {
		APP__data.touch_points[target_index].id = id;
		APP__data.touch_points[target_index].x = x;
		APP__data.touch_points[target_index].y = y;
		if      (state == 0) APP__data.touch_points[target_index].state = APP_TOUCH_STATE_BEGIN;
		else if (state == 1) APP__data.touch_points[target_index].state = APP_TOUCH_STATE_MOVE;
		else if (state == 2) APP__data.touch_points[target_index].state = APP_TOUCH_STATE_END;
		else if (state == 3) APP__data.touch_points[target_index].state = APP_TOUCH_STATE_CANCEL;
		else                 APP__data.touch_points[target_index].state = APP_TOUCH_STATE_INVALID;
		
		//if (target_index == 0) {
			APP__data.pointer.x = x;
			APP__data.pointer.y = y;

			if (state == 0 || state == 1) {
				if (APP__data.pointer.state & APP_POINTER_STATE_PRESSED) {
					APP__data.pointer.state = APP_POINTER_STATE_DOWN;
				}
				else {
					APP__data.pointer.state = (APP_POINTER_STATE_PRESSED|APP_POINTER_STATE_DOWN);
				}
			}
			else {
				APP__data.pointer.state = (APP_POINTER_STATE_RELEASED|APP_POINTER_STATE_UP);
			}
		//}
	}
}


int
APP__Handle_frame(void) {

	int64_t time_now = APP_Time();
	int64_t frame_duration = time_now - APP__data.prev_time;
	APP__data.prev_time = time_now;

	int head = APP__data.frame_duration_samples_head;
	head = (head + APP__MAX_FRAME_DURATION_SAMPLES - 1) % APP__MAX_FRAME_DURATION_SAMPLES;
	APP__data.frame_duration_samples[head] = frame_duration;
	APP__data.frame_duration_samples_head  = head;
	if (APP__data.frame_duration_samples_count < APP__MAX_FRAME_DURATION_SAMPLES) {
		APP__data.frame_duration_samples_count += 1;
	}

	#if defined (APP_LINUX)
		APP__linux_Process_events();
	#elif defined (APP_WINDOWS)
		APP__win32_Process_events();
	#elif defined (APP_WINDOWS)
		APP__wasm_Process_events();
	#endif
	
	
	int result = -1;
	if (APP__data.frame_callback) {
		result = APP__data.frame_callback();
	}

	APP__Clear_events();

	// If the focus has changed to not focus
	// Puts all the keys down to up because will never notify the up event
	if (!APP__data.focus) {
		APP__Put_keys_up();
	}
	
	#if defined (APP_LINUX)
		APP__linux_Swap_buffers();
	#elif defined (APP_WINDOWS)
		APP__win32_Swap_buffers();
	#endif

	return result;
}



/////////////////////////////////////////////////////////////////////////////////
//
//
//
//                     WINDOWS IMPLEMENTATION
//
//
//
////////////////////////////////////////////////////////////////////////////////
#if defined(APP_WINDOWS)

// https://www.opengl.org/archives/resources/code/samples/win32_tutorial/
// https://github.com/floooh/sokol/blob/master/sokol_app.h

#include <windowsx.h> // GET_X_LPARAM ...


typedef HGLRC (WINAPI * PFN_wglCreateContext)(HDC);
typedef BOOL (WINAPI * PFN_wglDeleteContext)(HGLRC);
typedef PROC (WINAPI * PFN_wglGetProcAddress)(LPCSTR);
typedef HDC (WINAPI * PFN_wglGetCurrentDC)(void);
typedef BOOL (WINAPI * PFN_wglMakeCurrent)(HDC,HGLRC);
typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC)(int);
#define WGL_NUMBER_PIXEL_FORMATS_ARB 0x2000
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_TYPE_RGBA_ARB 0x202b
#define WGL_ACCELERATION_ARB 0x2003
#define WGL_NO_ACCELERATION_ARB 0x2025
#define WGL_RED_BITS_ARB 0x2015
#define WGL_GREEN_BITS_ARB 0x2017
#define WGL_BLUE_BITS_ARB 0x2019
#define WGL_ALPHA_BITS_ARB 0x201b
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_SAMPLES_ARB 0x2042
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096
#define ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB 0x2054


// generate GL function pointers
#define APP__GL_XMACRO(name, ret, args) PFN_ ## name name;
	APP__GL_FUNCS
#undef APP__GL_XMACRO



static struct {
	HWND hwnd;
	HDC  hdc;
	HWND msg_hwnd;
	HDC  msg_hdc;
	wchar_t window_title_wide[128];

	HGLRC gl_ctx;
	HINSTANCE opengl32;
	PFN_wglCreateContext wglCreateContext;
	PFN_wglDeleteContext wglDeleteContext;
	PFN_wglGetProcAddress wglGetProcAddress;
	PFN_wglGetCurrentDC wglGetCurrentDC;
	PFN_wglMakeCurrent wglMakeCurrent;
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

	// Time tracking
	LARGE_INTEGER initial_time;
	LARGE_INTEGER time_freq;
} APP__win32_data = {0};


#define APP__MAX_KEYMAPPING 512

static APP_KeyCode APP__key_mapping[APP__MAX_KEYMAPPING] = {
    /* same as GLFW */
    [0x00B] = APP_KEY_0,
    [0x002] = APP_KEY_1,
    [0x003] = APP_KEY_2,
    [0x004] = APP_KEY_3,
    [0x005] = APP_KEY_4,
    [0x006] = APP_KEY_5,
    [0x007] = APP_KEY_6,
    [0x008] = APP_KEY_7,
    [0x009] = APP_KEY_8,
    [0x00A] = APP_KEY_9,
    [0x01E] = APP_KEY_A,
    [0x030] = APP_KEY_B,
    [0x02E] = APP_KEY_C,
    [0x020] = APP_KEY_D,
    [0x012] = APP_KEY_E,
    [0x021] = APP_KEY_F,
    [0x022] = APP_KEY_G,
    [0x023] = APP_KEY_H,
    [0x017] = APP_KEY_I,
    [0x024] = APP_KEY_J,
    [0x025] = APP_KEY_K,
    [0x026] = APP_KEY_L,
    [0x032] = APP_KEY_M,
    [0x031] = APP_KEY_N,
    [0x018] = APP_KEY_O,
    [0x019] = APP_KEY_P,
    [0x010] = APP_KEY_Q,
    [0x013] = APP_KEY_R,
    [0x01F] = APP_KEY_S,
    [0x014] = APP_KEY_T,
    [0x016] = APP_KEY_U,
    [0x02F] = APP_KEY_V,
    [0x011] = APP_KEY_W,
    [0x02D] = APP_KEY_X,
    [0x015] = APP_KEY_Y,
    [0x02C] = APP_KEY_Z,
    [0x028] = APP_KEY_APOSTROPHE,
    [0x02B] = APP_KEY_BACKSLASH,
    [0x033] = APP_KEY_COMMA,
    [0x00D] = APP_KEY_EQUAL,
    [0x029] = APP_KEY_GRAVE_ACCENT,
    [0x01A] = APP_KEY_LEFT_BRACKET,
    [0x00C] = APP_KEY_MINUS,
    [0x034] = APP_KEY_PERIOD,
    [0x01B] = APP_KEY_RIGHT_BRACKET,
    [0x027] = APP_KEY_SEMICOLON,
    [0x035] = APP_KEY_SLASH,
    [0x056] = APP_KEY_WORLD_2,
    [0x00E] = APP_KEY_BACKSPACE,
    [0x153] = APP_KEY_DELETE,
    [0x14F] = APP_KEY_END,
    [0x01C] = APP_KEY_ENTER,
    [0x001] = APP_KEY_ESCAPE,
    [0x147] = APP_KEY_HOME,
    [0x152] = APP_KEY_INSERT,
    [0x15D] = APP_KEY_MENU,
    [0x151] = APP_KEY_PAGE_DOWN,
    [0x149] = APP_KEY_PAGE_UP,
    [0x045] = APP_KEY_PAUSE,
    [0x146] = APP_KEY_PAUSE,
    [0x039] = APP_KEY_SPACE,
    [0x00F] = APP_KEY_TAB,
    [0x03A] = APP_KEY_CAPS_LOCK,
    [0x145] = APP_KEY_NUM_LOCK,
    [0x046] = APP_KEY_SCROLL_LOCK,
    [0x03B] = APP_KEY_F1,
    [0x03C] = APP_KEY_F2,
    [0x03D] = APP_KEY_F3,
    [0x03E] = APP_KEY_F4,
    [0x03F] = APP_KEY_F5,
    [0x040] = APP_KEY_F6,
    [0x041] = APP_KEY_F7,
    [0x042] = APP_KEY_F8,
    [0x043] = APP_KEY_F9,
    [0x044] = APP_KEY_F10,
    [0x057] = APP_KEY_F11,
    [0x058] = APP_KEY_F12,
    [0x064] = APP_KEY_F13,
    [0x065] = APP_KEY_F14,
    [0x066] = APP_KEY_F15,
    [0x067] = APP_KEY_F16,
    [0x068] = APP_KEY_F17,
    [0x069] = APP_KEY_F18,
    [0x06A] = APP_KEY_F19,
    [0x06B] = APP_KEY_F20,
    [0x06C] = APP_KEY_F21,
    [0x06D] = APP_KEY_F22,
    [0x06E] = APP_KEY_F23,
    [0x076] = APP_KEY_F24,
    [0x038] = APP_KEY_LEFT_ALT,
    [0x01D] = APP_KEY_LEFT_CONTROL,
    [0x02A] = APP_KEY_LEFT_SHIFT,
    [0x15B] = APP_KEY_LEFT_SUPER,
    [0x137] = APP_KEY_PRINT_SCREEN,
    [0x138] = APP_KEY_RIGHT_ALT,
    [0x11D] = APP_KEY_RIGHT_CONTROL,
    [0x036] = APP_KEY_RIGHT_SHIFT,
    [0x15C] = APP_KEY_RIGHT_SUPER,
    [0x150] = APP_KEY_DOWN,
    [0x14B] = APP_KEY_LEFT,
    [0x14D] = APP_KEY_RIGHT,
    [0x148] = APP_KEY_UP,
    [0x052] = APP_KEY_KP_0,
    [0x04F] = APP_KEY_KP_1,
    [0x050] = APP_KEY_KP_2,
    [0x051] = APP_KEY_KP_3,
    [0x04B] = APP_KEY_KP_4,
    [0x04C] = APP_KEY_KP_5,
    [0x04D] = APP_KEY_KP_6,
    [0x047] = APP_KEY_KP_7,
    [0x048] = APP_KEY_KP_8,
    [0x049] = APP_KEY_KP_9,
    [0x04E] = APP_KEY_KP_ADD,
    [0x053] = APP_KEY_KP_DECIMAL,
    [0x135] = APP_KEY_KP_DIVIDE,
    [0x11C] = APP_KEY_KP_ENTER,
    [0x037] = APP_KEY_KP_MULTIPLY,
    [0x04A] = APP_KEY_KP_SUBTRACT,
};


APP_INTERNAL LONG WINAPI
APP__Window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static bool mouse_tracked = false;

	switch (uMsg) {
	    case WM_CLOSE:
			APP__data.quit_requested = true;
	        break;
	    case WM_SYSCOMMAND:
	        break;
	    case WM_ERASEBKGND:
	        return 1;
	    case WM_SIZE: {
			APP__data.w_width  = LOWORD(lParam);
			APP__data.w_height = HIWORD(lParam);
			APP__data.window_resized = true;
	        break;
		}
	    case WM_SETCURSOR:
	        break;
	    case WM_LBUTTONDOWN: {
			APP__Report_mouse_button_down(APP_MOUSE_BUTTON_LEFT);
	        break;
		}
	    case WM_RBUTTONDOWN: {
			APP__Report_mouse_button_down(APP_MOUSE_BUTTON_RIGHT);
	        break;
		}
	    case WM_MBUTTONDOWN: {
			APP__Report_mouse_button_down(APP_MOUSE_BUTTON_MIDDLE);
	        break;
		}
	    case WM_LBUTTONUP: {
			APP__Report_mouse_button_up(APP_MOUSE_BUTTON_LEFT);
	        break;
		}
	    case WM_RBUTTONUP: {
			APP__Report_mouse_button_up(APP_MOUSE_BUTTON_RIGHT);
	        break;
		}
	    case WM_MBUTTONUP: {
			APP__Report_mouse_button_up(APP_MOUSE_BUTTON_MIDDLE);
	        break;
		}
		case  WM_MOUSEMOVE: {
			APP__Report_mouse_move((float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam));
			if (!mouse_tracked) {
				TRACKMOUSEEVENT tme;
				memset(&tme, 0, sizeof(tme));
				tme.cbSize = sizeof(tme);
				tme.dwFlags = TME_LEAVE;
				tme.hwndTrack = APP__win32_data.hwnd;
				TrackMouseEvent(&tme);
			}
			break;
		}
	    case WM_INPUT:
	        break;
	    case WM_MOUSELEAVE: {
			mouse_tracked = false;
			// Puts all the keys down to up because will never notify the up event
			APP__Put_keys_up();
	        break;
		}
	    case WM_MOUSEWHEEL:
			APP__data.mouse.wheel_y = (float)((SHORT)HIWORD(wParam));
	        break;
	    case WM_MOUSEHWHEEL:
			APP__data.mouse.wheel_x = (float)((SHORT)HIWORD(wParam));
	        break;
	    case WM_CHAR: {
			wchar_t input_char = (wchar_t)wParam;
			char multibyte_buffer[32] = "";
			int multibyte_len = WideCharToMultiByte(CP_UTF8, 0, &input_char, 1, multibyte_buffer, 31, NULL, NULL);
			if (!APP__Is_char_filtered(multibyte_buffer[0]) &&
				APP__data.text_input_bytes_count + multibyte_len < APP__TEXT_INPUT_BUFFER_MAX) {

				for (int i = 0; i < multibyte_len; ++i) {
					APP__data.text_input_buffer[APP__data.text_input_bytes_count+i] = multibyte_buffer[i];
				}
				APP__data.text_input_bytes_count = APP__data.text_input_bytes_count + multibyte_len;
				APP__data.text_input_buffer[APP__data.text_input_bytes_count] = '\0';
			}
			break;
		 }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: {
			int key = (int)(HIWORD(lParam)&0x1FF);
			if (key >= 0 && key < APP__MAX_KEYMAPPING) {
				int key_id = APP__key_mapping[key];
				if (APP__data.keyboard[key_id] & APP__KEY_STATUS_PRESSED ||
					APP__data.keyboard[key_id] & APP__KEY_STATUS_DOWN) {

					APP__data.keyboard[key_id] = APP__KEY_STATUS_DOWN;
				}
				else {
					APP__data.keyboard[key_id] = APP__KEY_STATUS_PRESSED;
				}
				APP__data.keyboard[key_id] |= APP__KEY_STATUS_REPEAT;
			}
            break;
		}
        case WM_KEYUP:
        case WM_SYSKEYUP: {
			int key = (int)(HIWORD(lParam)&0x1FF);
			if (key >= 0 && key < APP__MAX_KEYMAPPING) {
				APP__data.keyboard[APP__key_mapping[key]] = APP__KEY_STATUS_RELEASED;
			}
			break;
		}
		case WM_KILLFOCUS: {
			// Puts all the keys down to up because will never notify the up event
			APP__Put_keys_up();
			break;
		}
	    case WM_ENTERSIZEMOVE:
	        break;
	    case WM_EXITSIZEMOVE:
	        break;
	    case WM_TIMER:
	        //    SwapBuffers(hdc);
	        break;
	    case WM_DROPFILES:
	        break;
	    default:
	        break;
	}
	
    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
} 


/*
 * Extracted from sokol_app.h _sAPP_win32_uwp_utf8_to_wide
 *
 */
APP_INTERNAL bool
APP__String_to_wide(const char* src, wchar_t* dst, int dst_num_bytes) {
    assert(src && dst && (dst_num_bytes > 1));
    memset(dst, 0, (size_t)dst_num_bytes);
    const int dst_chars = dst_num_bytes / (int)sizeof(wchar_t);
    const int dst_needed = MultiByteToWideChar(CP_UTF8, 0, src, -1, 0, 0);
    if ((dst_needed > 0) && (dst_needed < dst_chars)) {
        MultiByteToWideChar(CP_UTF8, 0, src, -1, dst, dst_chars);
        return true;
    }
    else {
        /* input string doesn't fit into destination buffer */
        return false;
    }
}


APP_INTERNAL void *
APP__Load_gl_function(const char *func_name) {
    void* proc_addr = (void*)APP__win32_data.wglGetProcAddress(func_name);
	if (proc_addr == NULL) {
		proc_addr = (void*) GetProcAddress(APP__win32_data.opengl32, func_name);
	}
    if (proc_addr == NULL) {
		printf("CANNOT LOAD %s\n", func_name);
	}
    return proc_addr;
}



APP_INTERNAL int
APP__win32_Init(const char *title, int width, int height) {

	APP__data.default_width  = width;
	APP__data.default_height = height;
	APP__data.w_width  = width;
	APP__data.w_height = height;
	
	APP__String_to_wide(
			title,
			APP__win32_data.window_title_wide,
			sizeof(APP__win32_data.window_title_wide));

    WNDCLASSW wndclassw;
    memset(&wndclassw, 0, sizeof(wndclassw));
    wndclassw.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclassw.lpfnWndProc = (WNDPROC) APP__Window_proc;
    wndclassw.hInstance = GetModuleHandleW(NULL);
    wndclassw.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclassw.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndclassw.lpszClassName = L"APP";
    RegisterClassW(&wndclassw);

    DWORD win_style;
    const DWORD win_ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    RECT rect = { 0, 0, 0, 0 };
    win_style = WS_CLIPSIBLINGS |
				WS_CLIPCHILDREN |
				WS_CAPTION |
				WS_SYSMENU |
				WS_MINIMIZEBOX |
				WS_MAXIMIZEBOX |
				WS_SIZEBOX;

    rect.right  = width;
    rect.bottom = height;

    AdjustWindowRectEx(&rect, win_style, FALSE, win_ex_style);
    const int win_width = rect.right - rect.left;
    const int win_height = rect.bottom - rect.top;
    APP__win32_data.hwnd = CreateWindowExW(
        win_ex_style,                 /* dwExStyle */
        L"APP",                       /* lpClassName */
        APP__win32_data.window_title_wide, /* lpWindowName */
        win_style,                    /* dwStyle */
        CW_USEDEFAULT,                /* X */
        CW_USEDEFAULT,                /* Y */
        win_width,                    /* nWidth */
        win_height,                   /* nHeight */
        NULL,                         /* hWndParent */
        NULL,                         /* hMenu */
        GetModuleHandle(NULL),        /* hInstance */
        NULL);                        /* lParam */
    ShowWindow(APP__win32_data.hwnd, SW_SHOW);
    APP__win32_data.hdc = GetDC(APP__win32_data.hwnd);
	if (!APP__win32_data.hdc) {
		APP_Destroy_window();
		return -1;
	}

	// SETUP GL
	{
		APP__win32_data.opengl32 = LoadLibraryA("opengl32.dll");
		if (!APP__win32_data.opengl32) {
		    fprintf(stderr, "Failed to load opengl32.dll\n");
			APP_Destroy_window();
			return -1;
		}

		APP__win32_data.wglCreateContext = (PFN_wglCreateContext)(void*)GetProcAddress(APP__win32_data.opengl32, "wglCreateContext");
		if (!APP__win32_data.wglCreateContext) {
		    fprintf(stderr, "Failed to get proc address wglCreateContext\n");
			APP_Destroy_window();
			return -1;
		}

		APP__win32_data.wglDeleteContext  = (PFN_wglDeleteContext)(void*)GetProcAddress(APP__win32_data.opengl32, "wglDeleteContext");
		if (!APP__win32_data.wglDeleteContext) {
		    fprintf(stderr, "Failed to get proc address wglDeleteContext\n");
			APP_Destroy_window();
			return -1;
		}

		APP__win32_data.wglGetProcAddress = (PFN_wglGetProcAddress)(void*)GetProcAddress(APP__win32_data.opengl32, "wglGetProcAddress");
		if (!APP__win32_data.wglGetProcAddress) {
		    fprintf(stderr, "Failed to get proc address wglGetProcAddress\n");
			APP_Destroy_window();
			return -1;
		}

		APP__win32_data.wglGetCurrentDC = (PFN_wglGetCurrentDC)(void*)GetProcAddress(APP__win32_data.opengl32, "wglGetCurrentDC");
		if (!APP__win32_data.wglGetCurrentDC) {
		    fprintf(stderr, "Failed to get proc address wglGetCurrentDC\n");
			APP_Destroy_window();
			return -1;
		}

		APP__win32_data.wglMakeCurrent = (PFN_wglMakeCurrent)(void*)GetProcAddress(APP__win32_data.opengl32, "wglMakeCurrent");
		if (!APP__win32_data.wglMakeCurrent) {
		    fprintf(stderr, "Failed to get proc address wglMakeCurrent\n");
			APP_Destroy_window();
			return -1;
		}
    	

		PIXELFORMATDESCRIPTOR pfd;
    	/* there is no guarantee that the contents of the stack that become
    	   the pfd are zeroed, therefore _make sure_ to clear these bits. */
    	memset(&pfd, 0, sizeof(pfd));
    	pfd.nSize        = sizeof(pfd);
    	pfd.nVersion     = 1;
    	pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    	pfd.iPixelType   = PFD_TYPE_RGBA;
    	pfd.cColorBits   = 24;
		pfd.cDepthBits   = 24;

    	int pf = ChoosePixelFormat(APP__win32_data.hdc, &pfd);
    	if (pf == 0) {
			fprintf(stderr, "ChoosePixelFormat() failed: Cannot find a suitable pixel format."); 
			APP_Destroy_window();
			return -1;
    	} 
 
    	if (!SetPixelFormat(APP__win32_data.hdc, pf, &pfd)) {
			fprintf(stderr, "SetPixelFormat() failed: Cannot set format specified.");
			APP_Destroy_window();
			return -1;
    	} 

    	DescribePixelFormat(APP__win32_data.hdc, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

		APP__win32_data.gl_ctx = APP__win32_data.wglCreateContext(APP__win32_data.hdc);
		if (!APP__win32_data.gl_ctx) {
			const DWORD err = GetLastError();
			if (err == (0xc0070000 | ERROR_INVALID_VERSION_ARB)) {
				fprintf(stderr, "WGL: Driver does not support OpenGL version 3.3\n");
				APP_Destroy_window();
				return -1;
			}
			else if (err == (0xc0070000 | ERROR_INVALID_PROFILE_ARB)) {
				fprintf(stderr, "WGL: Driver does not support the requested OpenGL profile");
				APP_Destroy_window();
				return -1;
			}
			else if (err == (0xc0070000 | ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB)) {
				fprintf(stderr, "WGL: The share context is not compatible with the requested context");
				APP_Destroy_window();
				return -1;
			}
			else {
				fprintf(stderr, "WGL: Failed to create OpenGL context");
				APP_Destroy_window();
				return -1;
			}
		}
		APP__win32_data.wglMakeCurrent(APP__win32_data.hdc, APP__win32_data.gl_ctx);
		

		// What the fuck is this (Tano)
		//if (_sapp.wgl.ext_swap_control) {
		//	/* FIXME: DwmIsCompositionEnabled() (see GLFW) */
		//	_sapp.wgl.SwapIntervalEXT(_sapp.swap_interval);
		//}
		
		APP__win32_data.wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)(void*) APP__win32_data.wglGetProcAddress("wglSwapIntervalEXT");
		if (!APP__win32_data.wglSwapIntervalEXT) {
		    fprintf(stderr, "Failed to get proc address wglSwapIntervalEXT\n");
		}

		// BIND ALL GL FUNCTIONS
		#define APP__GL_XMACRO(name, ret, args) name = (PFN_ ## name) APP__Load_gl_function(#name);
			APP__GL_FUNCS
    	#undef APP__GL_XMACRO
	}

	{ // INIT APP TIME
		QueryPerformanceFrequency(&APP__win32_data.time_freq);
		QueryPerformanceCounter(&APP__win32_data.initial_time);
	}

	return 0;
}

APP_INTERNAL void
APP__win32_Set_fullscreen(bool enable) {
    HMONITOR monitor = MonitorFromWindow(APP__win32_data.hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO minfo;
    memset(&minfo, 0, sizeof(minfo));
    minfo.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(monitor, &minfo);
    const RECT mr = minfo.rcMonitor;
    const int monitor_w = mr.right - mr.left;
    const int monitor_h = mr.bottom - mr.top;

    const DWORD win_ex_style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    DWORD win_style;
    RECT rect = { 0, 0, 0, 0 };

    if (enable) {
        win_style = WS_POPUP | WS_SYSMENU | WS_VISIBLE;
        rect.right = monitor_w;
        rect.bottom = monitor_h;
    }
    else {
        win_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX;
        rect.right  = APP__data.default_width;
        rect.bottom = APP__data.default_height;
    }

    AdjustWindowRectEx(&rect, win_style, FALSE, win_ex_style);

    int win_width = rect.right - rect.left;
    int win_height = rect.bottom - rect.top;

    if (!enable) {
        rect.left = (monitor_w - win_width) / 2;
        rect.top = (monitor_h - win_height) / 2;
    }

    SetWindowLongPtr(APP__win32_data.hwnd, GWL_STYLE, win_style);
    SetWindowPos(APP__win32_data.hwnd, HWND_TOP, mr.left + rect.left, mr.top + rect.top, win_width, win_height, SWP_SHOWWINDOW | SWP_FRAMECHANGED);
	
	// Seems that when we call SetWindowPos it calls internally to our Window_proc with the WM_SIZE
	// event, but Set_fullscreen is called from the frame, and Clear_events clears all events after
	// the frame callback, so the application wouldn't notice the resize.
	//
	// To fix this we set fullscreen_changed to true and clear events will handle this case
	// correctly.
	//
	// Tano 15-08-2021
	APP__data.fullscreen_changed = true;
}

APP_INTERNAL void
APP__win32_Show_mouse(bool show) {
    ShowCursor((BOOL)show);
}

APP_INTERNAL void
APP__win32_Set_window_title(const char *title) {
	APP__String_to_wide(
			title,
			APP__win32_data.window_title_wide,
			sizeof(APP__win32_data.window_title_wide)
	);
    SetWindowTextW(APP__win32_data.hwnd, APP__win32_data.window_title_wide);
}



APP_INTERNAL void
APP__win32_Shutdown() {
	{ // Cleanup GL
		APP__win32_data.wglDeleteContext(APP__win32_data.gl_ctx);
    	APP__win32_data.gl_ctx = 0;
    	FreeLibrary(APP__win32_data.opengl32);
		APP__win32_data.opengl32 = 0;
	}
    DestroyWindow(APP__win32_data.hwnd);
}


APP_INTERNAL void
APP__win32_Process_events() {
	MSG msg;
	while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (WM_QUIT == msg.message) {
			APP__data.quit_requested = true;
			continue;
		}
		else {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

APP_INTERNAL void
APP__win32_Swap_buffers(void) {
	/* get rendered buffer to the screen */
	SwapBuffers(APP__win32_data.hdc);
}

APP_INTERNAL void
APP__win32_Set_swap_interval(unsigned int interval) {
	if (APP__win32_data.wglSwapIntervalEXT) {
		APP__win32_data.wglSwapIntervalEXT(interval);
	}
}

APP_INTERNAL int64_t
APP__win32_Time(void) {
	LARGE_INTEGER qpc_t;
	QueryPerformanceCounter(&qpc_t);

	int64_t counter_diff = qpc_t.QuadPart - APP__win32_data.initial_time.QuadPart;
	int64_t freq         = APP__win32_data.time_freq.QuadPart;
	
	// This is to preserve the precission (from sokol time)
    int64_t q = counter_diff / freq;
    int64_t r = counter_diff % freq;

	const int64_t SECOND = 1000*1000*1000;
	
    return q * SECOND + (r * SECOND) / freq;
}



////////////////////////////////////////////////////////////////////////////////
//
//
//
// SOUND API
//
//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <synchapi.h>
#ifndef CINTERFACE
#define CINTERFACE
#endif
#ifndef COBJMACROS
#define COBJMACROS
#endif
#ifndef CONST_VTABLE
#define CONST_VTABLE
#endif
#include <mmdeviceapi.h>
#include <audioclient.h>
static const IID splayer_IID_IAudioClient = { 0x1cb9ad4c, 0xdbfa, 0x4c32, { 0xb1, 0x78, 0xc2, 0xf5, 0x68, 0xa7, 0x03, 0xb2 } };
static const IID splayer_IID_IMMDeviceEnumerator = { 0xa95664d2, 0x9614, 0x4f35, { 0xa7, 0x46, 0xde, 0x8d, 0xb6, 0x36, 0x17, 0xe6 } };
static const CLSID splayer_CLSID_IMMDeviceEnumerator = { 0xbcde0395, 0xe52f, 0x467c, { 0x8e, 0x3d, 0xc4, 0x57, 0x92, 0x91, 0x69, 0x2e } };
static const IID splayer_IID_IAudioRenderClient = { 0xf294acfc, 0x3146, 0x4483,{ 0xa7, 0xbf, 0xad, 0xdc, 0xa7, 0xc2, 0x60, 0xe2 } };
static const IID splayer_IID_Devinterface_Audio_Render = { 0xe6327cad, 0xdcec, 0x4949, {0xae, 0x8a, 0x99, 0x1e, 0x97, 0x6a, 0x79, 0xd2 } };
static const IID splayer_IID_IActivateAudioInterface_Completion_Handler = { 0x94ea2b94, 0xe9cc, 0x49e0, {0xc0, 0xff, 0xee, 0x64, 0xca, 0x8f, 0x5b, 0x90} };
#define AUDIO_WIN32COM_ID(x) (&x)
/* fix for Visual Studio 2015 SDKs */



static struct {
	IMMDeviceEnumerator* device_enumerator;
	IMMDevice* device;
	IAudioClient* audio_client;
	IAudioRenderClient* render_client;
	int si16_bytes_per_frame;
	struct {
	    HANDLE thread_handle;
	    HANDLE buffer_end_event;
	    volatile bool stop;
	    UINT32 dst_buffer_frames;
	    int src_buffer_frames;
	    int src_buffer_byte_size;
	    int src_buffer_pos;
	    float* src_buffer;
	} thread;
} APP__sound_player_backend = {0};



APP_INTERNAL void
APP__Cleanup_sound_player(void) {
    if (APP__sound_player_backend.thread.src_buffer) {
        free(APP__sound_player_backend.thread.src_buffer);
        APP__sound_player_backend.thread.src_buffer = NULL;
    }
    if (APP__sound_player_backend.render_client) {
        IAudioRenderClient_Release(APP__sound_player_backend.render_client);
        APP__sound_player_backend.render_client = 0;
    }
    if (APP__sound_player_backend.audio_client) {
        IAudioClient_Release(APP__sound_player_backend.audio_client);
        APP__sound_player_backend.audio_client = 0;
    }
	if (APP__sound_player_backend.device) {
	    IMMDevice_Release(APP__sound_player_backend.device);
	    APP__sound_player_backend.device = 0;
	}
	if (APP__sound_player_backend.device_enumerator) {
	    IMMDeviceEnumerator_Release(APP__sound_player_backend.device_enumerator);
	    APP__sound_player_backend.device_enumerator = 0;
	}
	if (0 != APP__sound_player_backend.thread.buffer_end_event) {
	    CloseHandle(APP__sound_player_backend.thread.buffer_end_event);
	    APP__sound_player_backend.thread.buffer_end_event = 0;
	}
}





APP_INTERNAL void
APP__Sound_player_submit_buffer(int num_frames) {
    BYTE* wasapi_buffer = 0;
    if (FAILED(IAudioRenderClient_GetBuffer(APP__sound_player_backend.render_client, num_frames, &wasapi_buffer))) {
        return;
    }

    /* convert float samples to int16_t, refill float buffer if needed */
    const int num_samples = num_frames * APP__data.sound_player_info.num_channels;
    int16_t* dst = (int16_t*) wasapi_buffer;
    int buffer_pos = APP__sound_player_backend.thread.src_buffer_pos;
    const int buffer_float_size = APP__sound_player_backend.thread.src_buffer_byte_size / (int)sizeof(float);
    float* src = APP__sound_player_backend.thread.src_buffer;
    for (int i = 0; i < num_samples; i++) {
        if (0 == buffer_pos) {
			APP__data.sound_player_info.stream_cb(
					APP__data.sound_player_info.user_data,
					APP__sound_player_backend.thread.src_buffer,
					APP__data.sound_player_info.buffer_frames,
					APP__data.sound_player_info.num_channels
			);
        }
		int value = (src[buffer_pos] * 0x7FFF);
		value = value < -32768 ? -32768 : (value > 32767 ? 32767 : value); // Clamp the value to prevent overflow
        dst[i] = (int16_t) (value);
        buffer_pos += 1;
        if (buffer_pos == buffer_float_size) {
            buffer_pos = 0;
        }
    }
    APP__sound_player_backend.thread.src_buffer_pos = buffer_pos;

    IAudioRenderClient_ReleaseBuffer(APP__sound_player_backend.render_client, num_frames, 0);
}

APP_INTERNAL DWORD WINAPI
APP__Sound_player_thread(LPVOID param) {
    (void)param;
    APP__Sound_player_submit_buffer(APP__sound_player_backend.thread.src_buffer_frames);
    IAudioClient_Start(APP__sound_player_backend.audio_client);
    while (!APP__sound_player_backend.thread.stop) {
        WaitForSingleObject(APP__sound_player_backend.thread.buffer_end_event, INFINITE);
        UINT32 padding = 0;
        if (FAILED(IAudioClient_GetCurrentPadding(APP__sound_player_backend.audio_client, &padding))) {
            continue;
        }
        if (APP__sound_player_backend.thread.dst_buffer_frames < padding) {
			fprintf(stderr, "Error, on sound player thread, buffer frames less than padding");
			return 1;
		}
        int num_frames = (int)APP__sound_player_backend.thread.dst_buffer_frames - (int)padding;
        if (num_frames > 0) {
            APP__Sound_player_submit_buffer(num_frames);
        }
    }
    return 0;
}


APP_PUBLIC int
APP_Launch_sound_player(APP_SoundPlayerDesc *desc) {
	REFERENCE_TIME dur;
	/* CoInitializeEx could have been called elsewhere already, in which
	    case the function returns with S_FALSE (thus it does not make much
	    sense to check the result)
	*/
	CoInitializeEx(0, COINIT_MULTITHREADED);
	APP__sound_player_backend.thread.buffer_end_event = CreateEvent(0, FALSE, FALSE, 0);
	if (0 == APP__sound_player_backend.thread.buffer_end_event) {
	    fprintf(stderr, "failed to create buffer_end_event.\n");
		APP__Cleanup_sound_player();
		return -1;
	}
	if (FAILED(CoCreateInstance(
					&splayer_CLSID_IMMDeviceEnumerator,
					0,
					CLSCTX_ALL,
					&splayer_IID_IMMDeviceEnumerator,
					(void**)&APP__sound_player_backend.device_enumerator))
	) {
	    fprintf(stderr, "failed to create device enumerator.\n");
		APP__Cleanup_sound_player();
		return -1;
	}

	if (FAILED(IMMDeviceEnumerator_GetDefaultAudioEndpoint(APP__sound_player_backend.device_enumerator,
			eRender, eConsole,
			&APP__sound_player_backend.device))) {
	    fprintf(stderr, "GetDefaultAudioEndPoint failed.\n");
		APP__Cleanup_sound_player();
		return -1;
	}

	if (FAILED(IMMDevice_Activate(APP__sound_player_backend.device, &splayer_IID_IAudioClient, CLSCTX_ALL, 0,
	    (void**)&APP__sound_player_backend.audio_client)))
	{
	    fprintf(stderr, "device activate failed\n");
		APP__Cleanup_sound_player();
		return -1;
	}

	WAVEFORMATEX fmt;
	memset(&fmt, 0, sizeof(fmt));
	fmt.nChannels = (WORD)desc->num_channels;
	fmt.nSamplesPerSec = (DWORD)desc->sample_rate;
	fmt.wFormatTag = WAVE_FORMAT_PCM;
	fmt.wBitsPerSample = 16;
	fmt.nBlockAlign = (fmt.nChannels * fmt.wBitsPerSample) / 8;
	fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nBlockAlign;
	dur = (REFERENCE_TIME)
	    (((double)desc->buffer_frames) / (((double)desc->sample_rate) * (1.0/10000000.0)));
	if (FAILED(IAudioClient_Initialize(APP__sound_player_backend.audio_client,
	    AUDCLNT_SHAREMODE_SHARED,
	    AUDCLNT_STREAMFLAGS_EVENTCALLBACK|AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM|AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY,
	    dur, 0, &fmt, 0)))
	{
	    fprintf(stderr, "audio client initialize failed.\n");
		APP__Cleanup_sound_player();
		return -1;
	}
	if (FAILED(IAudioClient_GetBufferSize(APP__sound_player_backend.audio_client, &APP__sound_player_backend.thread.dst_buffer_frames))) {
	    fprintf(stderr, "audio client get buffer size failed.\n");
		APP__Cleanup_sound_player();
		return -1;
	}
	if (FAILED(IAudioClient_GetService(APP__sound_player_backend.audio_client, &splayer_IID_IAudioRenderClient,
			(void**)&APP__sound_player_backend.render_client))) {
	    fprintf(stderr, "audio client GetService failed.\n");
		APP__Cleanup_sound_player();
		return -1;
	}
	if (FAILED(IAudioClient_SetEventHandle(APP__sound_player_backend.audio_client,
			APP__sound_player_backend.thread.buffer_end_event))) {
	    fprintf(stderr, "audio client SetEventHandle failed.\n");
		APP__Cleanup_sound_player();
		return -1;
	}
	APP__sound_player_backend.si16_bytes_per_frame = desc->num_channels * (int)sizeof(int16_t);
	size_t bytes_per_frame = desc->num_channels * (int)sizeof(float);
	APP__sound_player_backend.thread.src_buffer_frames = desc->buffer_frames;
	APP__sound_player_backend.thread.src_buffer_byte_size = APP__sound_player_backend.thread.src_buffer_frames * bytes_per_frame;
	
	/* allocate an intermediate buffer for sample format conversion */
	// TODO(Tano) Check this??
	APP__sound_player_backend.thread.src_buffer = (float *)malloc(sizeof(float) * desc->num_channels*desc->buffer_frames);
	
	/* create streaming thread */
	APP__sound_player_backend.thread.thread_handle = CreateThread(NULL, 0, APP__Sound_player_thread, 0, 0, 0);
	if (0 == APP__sound_player_backend.thread.thread_handle) {
	    fprintf(stderr, "audio wasapi: CreateThread failed\n");
		APP__Cleanup_sound_player();
		return -1;
	}

	APP__data.sound_player_info.sample_rate   = desc->sample_rate;
	APP__data.sound_player_info.buffer_frames = desc->buffer_frames;
	APP__data.sound_player_info.user_data     = desc->user_data;
	APP__data.sound_player_info.stream_cb     = desc->stream_cb;
	APP__data.sound_player_info.num_channels  = desc->num_channels;

	return 0;
}





APP_PUBLIC void
APP_Terminate_sound_player(void) {
	if (APP__sound_player_backend.thread.thread_handle) {
	    APP__sound_player_backend.thread.stop = true;
	    SetEvent(APP__sound_player_backend.thread.buffer_end_event);
	    WaitForSingleObject(APP__sound_player_backend.thread.thread_handle, INFINITE);
	    CloseHandle(APP__sound_player_backend.thread.thread_handle);
	    APP__sound_player_backend.thread.thread_handle = 0;
	}
	if (APP__sound_player_backend.audio_client) {
	    IAudioClient_Stop(APP__sound_player_backend.audio_client);
	}
	APP__Cleanup_sound_player();
	CoUninitialize();
}








////////////////////////////////////////////////////////////////////////////////
//
//
//
// THREAD API
//
//
//
////////////////////////////////////////////////////////////////////////////////


void
Mutex_init(Mutex *mutex) {
	*mutex = CreateMutex( 
			NULL,              // default security attributes.
			FALSE,             // initially not owned
			NULL);             // unnamed mutex

	if (*mutex == NULL) {
		abort();
	}
}

void
Mutex_deinit(Mutex *mutex) {
	CloseHandle(*mutex);
}

void
Mutex_lock(Mutex *mutex) {
	DWORD dwWaitResult = dwWaitResult = WaitForSingleObject( 
			*mutex,     // handle to mutex
			INFINITE);  // no time-out interval

	if (WAIT_OBJECT_0 != dwWaitResult) {
		abort();
	}
}

void
Mutex_unlock(Mutex *mutex) {
	if (!ReleaseMutex(*mutex)) {
		abort();
	}
}


////////////////////////////////////////////////////////////////////////////////
//
//
//
// FILESYSTEM API
//
//
//
////////////////////////////////////////////////////////////////////////////////


// Documented above
#if !defined(BUNDLED_TREE)
uint64_t
Get_file_modify_time(const char *filename) {
	HANDLE file_handle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file_handle == INVALID_HANDLE_VALUE) {
		return 0;
	}
	FILETIME time;
	uint64_t result = 0;
	if (GetFileTime(file_handle, NULL, NULL, &time)) {
		result = (uint64_t)time.dwLowDateTime;
		result |= (uint64_t)time.dwHighDateTime << 32;
	}
	CloseHandle(file_handle);
	return result;
}
#endif










/////////////////////////////////////////////////////////////////////////////////
//
//
//
//                     LINUX IMPLEMENTATION ||||
//                                          VVVV
//
//
////////////////////////////////////////////////////////////////////////////////

#elif defined(APP_LINUX)

#include <EGL/egl.h>
#include <EGL/eglplatform.h>
#include <time.h>
#include <X11/keysym.h>
#include <X11/Xcursor/Xcursor.h>

static struct {
	Window root;
	Window  win;
	Display *xdisplay;
	XSetWindowAttributes swa;
    Atom WM_PROTOCOLS;
    Atom WM_DELETE_WINDOW;
	Atom NET_WM_STATE;
    Atom NET_WM_STATE_FULLSCREEN;

	// Text input
	XIM xim;
	XIC	xic;

	Cursor hidden_cursor;

	// EGL-related objects
	EGLDisplay egl_display;
	EGLConfig  egl_conf;
	EGLContext egl_context;
	EGLSurface egl_surface;

	// APP TIME
	struct timespec initial_time;

} APP__x11_data = {0};



APP_INTERNAL int
APP__linux_Init(const char *title, int width, int height) {

	APP__data.default_width  = width;
	APP__data.default_height = height;
	APP__data.w_width  = width;
	APP__data.w_height = height;

	/* open standard display (primary screen) */
	APP__x11_data.xdisplay = XOpenDisplay(NULL);   
	if (APP__x11_data.xdisplay == NULL) {
	    printf("Error opening X display\n");
	    return -1;
	}
	// get the root window (usually the whole screen)
	APP__x11_data.root = DefaultRootWindow(APP__x11_data.xdisplay);
	
	// list all events this window accepts
	APP__x11_data.swa.event_mask =
		StructureNotifyMask |
		ExposureMask        |
		PointerMotionMask   |
		KeyPressMask        |
		KeyReleaseMask      |
		ButtonPressMask     |
		FocusChangeMask     |
		ButtonReleaseMask;
	
	// Xlib's window creation
	APP__x11_data.win = XCreateWindow (
			APP__x11_data.xdisplay, APP__x11_data.root, 0, 0, width, height, 0,
			CopyFromParent, InputOutput, CopyFromParent, CWEventMask,
			&APP__x11_data.swa);
	
	XMapWindow(APP__x11_data.xdisplay, APP__x11_data.win);         // make window visible
	XStoreName(APP__x11_data.xdisplay, APP__x11_data.win, title);
    
	// To handle windows close
	APP__x11_data.WM_PROTOCOLS     = XInternAtom(APP__x11_data.xdisplay, "WM_PROTOCOLS", False);
    APP__x11_data.WM_DELETE_WINDOW = XInternAtom(APP__x11_data.xdisplay, "WM_DELETE_WINDOW", False);
	APP__x11_data.NET_WM_STATE     = XInternAtom(APP__x11_data.xdisplay, "_NET_WM_STATE", False);
	APP__x11_data.NET_WM_STATE_FULLSCREEN = XInternAtom(APP__x11_data.xdisplay, "_NET_WM_STATE_FULLSCREEN", False);
    Atom protocols[] = {
        APP__x11_data.WM_DELETE_WINDOW
    };
    XSetWMProtocols(APP__x11_data.xdisplay, APP__x11_data.win, protocols, 1);

	{ // Prepare for keyboard text input
		APP__x11_data.xim = XOpenIM(APP__x11_data.xdisplay, 0, 0, 0);
		APP__x11_data.xic = XCreateIC(APP__x11_data.xim, XNInputStyle, XIMPreeditNothing | XIMStatusNothing, NULL);
	}

	{ // Create a invisible cursor
		const int w = 16;
    	const int h = 16;
    	XcursorImage* img = XcursorImageCreate(w, h);
		if (img == NULL) {
			APP_Destroy_window();
			return -1;
		}
    	img->xhot = 0;
    	img->yhot = 0;
		for (int i = 0; i < w*h; i+=1) img->pixels[i] = 0; // Set all to 0

    	APP__x11_data.hidden_cursor = XcursorImageLoadCursor(APP__x11_data.xdisplay, img);
    	XcursorImageDestroy(img);
	}

	{ // Setup OpenGL

		EGLint attr[] = {
    	    EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
    	    EGL_RED_SIZE,        8,
    	    EGL_GREEN_SIZE,      8,
    	    EGL_BLUE_SIZE,       8,
			EGL_DEPTH_SIZE,      24,
    	    EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, /* If one needs GLES2 */
    	    EGL_NONE
    	};

    	EGLint num_config;
    	EGLint major, minor;

    	EGLint ctxattr[] = {
    	   EGL_CONTEXT_CLIENT_VERSION, 2,
    	   EGL_NONE
    	};

    	APP__x11_data.egl_display = eglGetDisplay((EGLNativeDisplayType)APP__x11_data.xdisplay);
    	if (APP__x11_data.egl_display == EGL_NO_DISPLAY) {
    	    fprintf(stderr, "Error getting EGL display\n");
			APP_Destroy_window();
    	    return -1;
    	}

    	if (eglInitialize(APP__x11_data.egl_display, &major, &minor) != EGL_TRUE) {
    	    fprintf(stderr, "Error initializing EGL\n");
			APP_Destroy_window();
    	    return -1;
    	}
    	// printf("EGL major: %d, minor %d\n", major, minor);

    	/* create EGL rendering context */
    	if (!eglChooseConfig(APP__x11_data.egl_display, attr, &APP__x11_data.egl_conf, 1, &num_config )) {
    	    fprintf(stderr, "Failed to choose config (eglError: %x)\n", eglGetError());
			APP_Destroy_window();
    	    return -1;
    	}

    	if (num_config != 1) {
    	    return -1;
    	}

    	APP__x11_data.egl_surface = eglCreateWindowSurface(
				APP__x11_data.egl_display,
				APP__x11_data.egl_conf,
				APP__x11_data.win,
				NULL
		);
    	if (APP__x11_data.egl_surface == EGL_NO_SURFACE) {
    	    fprintf(stderr, "CreateWindowSurface, EGL eglError: %d\n", eglGetError());
			APP_Destroy_window();
    	    return -1;
    	}

    	APP__x11_data.egl_context = eglCreateContext(
				APP__x11_data.egl_display,
				APP__x11_data.egl_conf,
				EGL_NO_CONTEXT,
				ctxattr
		);
    	if (APP__x11_data.egl_context == EGL_NO_CONTEXT) {
    	    fprintf(stderr, "CreateContext, EGL eglError: %d\n", eglGetError() );
			APP_Destroy_window();
    	    return -1;
    	}
		
		//
		// WARNING LEAK!!!!
		// This generates a leak, no idea why....
		//
		if (eglMakeCurrent(
				APP__x11_data.egl_display,
				APP__x11_data.egl_surface,
				APP__x11_data.egl_surface,
				APP__x11_data.egl_context
		) != EGL_TRUE) {
    	    fprintf(stderr, "MakeCurrent, EGL eglError: %d\n", eglGetError() );
			APP_Destroy_window();
    	    return -1;
		}
	}

	APP_Set_swap_interval(1);

	return 0;
}

APP_INTERNAL void
APP__X11_send_event(Atom type, int a, int b, int c, int d, int e) {
    XEvent event = {0};

    event.type = ClientMessage;
    event.xclient.window = APP__x11_data.win;
    event.xclient.format = 32;
    event.xclient.message_type = type;
    event.xclient.data.l[0] = a;
    event.xclient.data.l[1] = b;
    event.xclient.data.l[2] = c;
    event.xclient.data.l[3] = d;
    event.xclient.data.l[4] = e;

    XSendEvent(APP__x11_data.xdisplay, APP__x11_data.root,
               False,
               SubstructureNotifyMask | SubstructureRedirectMask,
               &event);
}

APP_INTERNAL void
APP__linux_Set_fullscreen(bool enable) {
	/* NOTE: this function must be called after XMapWindow (which happens in _sAPP_x11_show_window()) */
    if (APP__x11_data.NET_WM_STATE && APP__x11_data.NET_WM_STATE_FULLSCREEN) {
        if (enable) {
            const int _NET_WM_STATE_ADD = 1;
            APP__X11_send_event(APP__x11_data.NET_WM_STATE,
                                _NET_WM_STATE_ADD,
                                APP__x11_data.NET_WM_STATE_FULLSCREEN,
                                0, 1, 0);
        }
        else {
            const int _NET_WM_STATE_REMOVE = 0;
            APP__X11_send_event(APP__x11_data.NET_WM_STATE,
                                _NET_WM_STATE_REMOVE,
                                APP__x11_data.NET_WM_STATE_FULLSCREEN,
                                0, 1, 0);
        }
    }
    XFlush(APP__x11_data.xdisplay);
}


APP_INTERNAL void
APP__linux_Show_mouse(bool show) {
    if (show) {
        XUndefineCursor(APP__x11_data.xdisplay, APP__x11_data.win);
    }
    else {
        XDefineCursor(APP__x11_data.xdisplay, APP__x11_data.win, APP__x11_data.hidden_cursor);
    }	
}

APP_INTERNAL void
APP__linux_Set_window_title(const char *title) {
	XStoreName(APP__x11_data.xdisplay, APP__x11_data.win, title);
	XFlush(APP__x11_data.xdisplay);
}


APP_INTERNAL void
APP__linux_Shutdown(void) {
	{
		// I readed somewhere that is important that all gl commands must finalize before clean
		// everything.
		glFinish();

		// This unbinds the context, must be done before destroy the context.
		if (EGL_TRUE != eglMakeCurrent(
					APP__x11_data.egl_display,
					EGL_NO_SURFACE,
					EGL_NO_SURFACE,
					EGL_NO_CONTEXT)) {

   		 	fprintf(stderr, "Error, cannot unbind context and surfaces.\n");
		}
		
		// Destroys the surface and the context
   		if (eglDestroySurface(APP__x11_data.egl_display, APP__x11_data.egl_surface) != EGL_TRUE) {
   		 	fprintf(stderr, "Error, cannot destroy egl surface.\n");
   		}
		if (eglDestroyContext(APP__x11_data.egl_display, APP__x11_data.egl_context) != EGL_TRUE) {
   		 	fprintf(stderr, "Error, cannot destroy egl context.\n");
   		}

		// Destroys the egl_display
   		if (eglTerminate(APP__x11_data.egl_display) != EGL_TRUE) {
   		 	fprintf(stderr, "Error, cannot terminate egl display connection.\n");
   		}
	}

	XDestroyIC(APP__x11_data.xic);
	XCloseIM(APP__x11_data.xim);
	XUnmapWindow(APP__x11_data.xdisplay, APP__x11_data.win);
	XDestroyWindow(APP__x11_data.xdisplay, APP__x11_data.win);
	XCloseDisplay(APP__x11_data.xdisplay);
}




APP_INTERNAL void
APP__linux_Set_swap_interval(unsigned int interval) {
	eglSwapInterval(APP__x11_data.egl_display, interval);
}

APP_INTERNAL void
APP__linux_Swap_buffers() {
	/* get rendered buffer to the screen */
	eglSwapBuffers (APP__x11_data.egl_display, APP__x11_data.egl_surface);
}

// Based on sokol_app.h
APP_INTERNAL APP_KeyCode
APP__Translate_key(int scancode) {
    int dummy;
    KeySym* keysyms = XGetKeyboardMapping(APP__x11_data.xdisplay, scancode, 1, &dummy);
    if (keysyms == NULL) {
		return APP_KEY_INVALID;
	}

    KeySym keysym = keysyms[0];
    XFree(keysyms);
    switch (keysym) {
        case XK_Escape:         return APP_KEY_ESCAPE;
        case XK_Tab:            return APP_KEY_TAB;
        case XK_Shift_L:        return APP_KEY_LEFT_SHIFT;
        case XK_Shift_R:        return APP_KEY_RIGHT_SHIFT;
        case XK_Control_L:      return APP_KEY_LEFT_CONTROL;
        case XK_Control_R:      return APP_KEY_RIGHT_CONTROL;
        case XK_Meta_L:
        case XK_Alt_L:          return APP_KEY_LEFT_ALT;
        case XK_Mode_switch:    /* Mapped to Alt_R on many keyboards */
        case XK_ISO_Level3_Shift: /* AltGr on at least some machines */
        case XK_Meta_R:
        case XK_Alt_R:          return APP_KEY_RIGHT_ALT;
        case XK_Super_L:        return APP_KEY_LEFT_SUPER;
        case XK_Super_R:        return APP_KEY_RIGHT_SUPER;
        case XK_Menu:           return APP_KEY_MENU;
        case XK_Num_Lock:       return APP_KEY_NUM_LOCK;
        case XK_Caps_Lock:      return APP_KEY_CAPS_LOCK;
        case XK_Print:          return APP_KEY_PRINT_SCREEN;
        case XK_Scroll_Lock:    return APP_KEY_SCROLL_LOCK;
        case XK_Pause:          return APP_KEY_PAUSE;
        case XK_Delete:         return APP_KEY_DELETE;
        case XK_BackSpace:      return APP_KEY_BACKSPACE;
        case XK_Return:         return APP_KEY_ENTER;
        case XK_Home:           return APP_KEY_HOME;
        case XK_End:            return APP_KEY_END;
        case XK_Page_Up:        return APP_KEY_PAGE_UP;
        case XK_Page_Down:      return APP_KEY_PAGE_DOWN;
        case XK_Insert:         return APP_KEY_INSERT;
        case XK_Left:           return APP_KEY_LEFT;
        case XK_Right:          return APP_KEY_RIGHT;
        case XK_Down:           return APP_KEY_DOWN;
        case XK_Up:             return APP_KEY_UP;
        case XK_F1:             return APP_KEY_F1;
        case XK_F2:             return APP_KEY_F2;
        case XK_F3:             return APP_KEY_F3;
        case XK_F4:             return APP_KEY_F4;
        case XK_F5:             return APP_KEY_F5;
        case XK_F6:             return APP_KEY_F6;
        case XK_F7:             return APP_KEY_F7;
        case XK_F8:             return APP_KEY_F8;
        case XK_F9:             return APP_KEY_F9;
        case XK_F10:            return APP_KEY_F10;
        case XK_F11:            return APP_KEY_F11;
        case XK_F12:            return APP_KEY_F12;
        case XK_F13:            return APP_KEY_F13;
        case XK_F14:            return APP_KEY_F14;
        case XK_F15:            return APP_KEY_F15;
        case XK_F16:            return APP_KEY_F16;
        case XK_F17:            return APP_KEY_F17;
        case XK_F18:            return APP_KEY_F18;
        case XK_F19:            return APP_KEY_F19;
        case XK_F20:            return APP_KEY_F20;
        case XK_F21:            return APP_KEY_F21;
        case XK_F22:            return APP_KEY_F22;
        case XK_F23:            return APP_KEY_F23;
        case XK_F24:            return APP_KEY_F24;
        case XK_F25:            return APP_KEY_F25;

        case XK_KP_Divide:      return APP_KEY_KP_DIVIDE;
        case XK_KP_Multiply:    return APP_KEY_KP_MULTIPLY;
        case XK_KP_Subtract:    return APP_KEY_KP_SUBTRACT;
        case XK_KP_Add:         return APP_KEY_KP_ADD;

        case XK_KP_Insert:      return APP_KEY_KP_0;
        case XK_KP_End:         return APP_KEY_KP_1;
        case XK_KP_Down:        return APP_KEY_KP_2;
        case XK_KP_Page_Down:   return APP_KEY_KP_3;
        case XK_KP_Left:        return APP_KEY_KP_4;
        case XK_KP_Begin:       return APP_KEY_KP_5;
        case XK_KP_Right:       return APP_KEY_KP_6;
        case XK_KP_Home:        return APP_KEY_KP_7;
        case XK_KP_Up:          return APP_KEY_KP_8;
        case XK_KP_Page_Up:     return APP_KEY_KP_9;
        case XK_KP_Delete:      return APP_KEY_KP_DECIMAL;
        case XK_KP_Equal:       return APP_KEY_KP_EQUAL;
        case XK_KP_Enter:       return APP_KEY_KP_ENTER;

        case XK_a:              return APP_KEY_A;
        case XK_b:              return APP_KEY_B;
        case XK_c:              return APP_KEY_C;
        case XK_d:              return APP_KEY_D;
        case XK_e:              return APP_KEY_E;
        case XK_f:              return APP_KEY_F;
        case XK_g:              return APP_KEY_G;
        case XK_h:              return APP_KEY_H;
        case XK_i:              return APP_KEY_I;
        case XK_j:              return APP_KEY_J;
        case XK_k:              return APP_KEY_K;
        case XK_l:              return APP_KEY_L;
        case XK_m:              return APP_KEY_M;
        case XK_n:              return APP_KEY_N;
        case XK_o:              return APP_KEY_O;
        case XK_p:              return APP_KEY_P;
        case XK_q:              return APP_KEY_Q;
        case XK_r:              return APP_KEY_R;
        case XK_s:              return APP_KEY_S;
        case XK_t:              return APP_KEY_T;
        case XK_u:              return APP_KEY_U;
        case XK_v:              return APP_KEY_V;
        case XK_w:              return APP_KEY_W;
        case XK_x:              return APP_KEY_X;
        case XK_y:              return APP_KEY_Y;
        case XK_z:              return APP_KEY_Z;
        case XK_1:              return APP_KEY_1;
        case XK_2:              return APP_KEY_2;
        case XK_3:              return APP_KEY_3;
        case XK_4:              return APP_KEY_4;
        case XK_5:              return APP_KEY_5;
        case XK_6:              return APP_KEY_6;
        case XK_7:              return APP_KEY_7;
        case XK_8:              return APP_KEY_8;
        case XK_9:              return APP_KEY_9;
        case XK_0:              return APP_KEY_0;
        case XK_space:          return APP_KEY_SPACE;
        case XK_minus:          return APP_KEY_MINUS;
        case XK_equal:          return APP_KEY_EQUAL;
        case XK_bracketleft:    return APP_KEY_LEFT_BRACKET;
        case XK_bracketright:   return APP_KEY_RIGHT_BRACKET;
        case XK_backslash:      return APP_KEY_BACKSLASH;
        case XK_semicolon:      return APP_KEY_SEMICOLON;
        case XK_apostrophe:     return APP_KEY_APOSTROPHE;
        case XK_grave:          return APP_KEY_GRAVE_ACCENT;
        case XK_comma:          return APP_KEY_COMMA;
        case XK_period:         return APP_KEY_PERIOD;
        case XK_slash:          return APP_KEY_SLASH;
        case XK_less:           return APP_KEY_WORLD_1; /* At least in some layouts... */
        default:                return APP_KEY_INVALID;
    }
}


APP_INTERNAL APP_MouseButton
APP__Translate_mouse_button(unsigned int button) {
    switch (button) {
        case Button1: return APP_MOUSE_BUTTON_LEFT;
        case Button2: return APP_MOUSE_BUTTON_MIDDLE;
        case Button3: return APP_MOUSE_BUTTON_RIGHT;
        default:      return APP_MOUSE_BUTTON_INVALID;
    }
}

APP_INTERNAL void
APP__linux_Process_events() {

	XEvent event;
	for (int remaining_events = XPending(APP__x11_data.xdisplay);
		remaining_events > 0;
		--remaining_events) {

        XNextEvent(APP__x11_data.xdisplay, &event);
		switch (event.type) {
			case ConfigureNotify: {
        	    if ((event.xconfigure.width != APP__data.w_width) ||
					(event.xconfigure.height != APP__data.w_width)) {

					APP__data.w_width  = event.xconfigure.width;
					APP__data.w_height = event.xconfigure.height;
					APP__data.window_resized = true;
        	    }
        	    break;
			}
			case FocusOut: {
				// Puts all the keys down to up because will never notify the up event
				APP__Put_keys_up();
				break;
			}
			case KeyPress: {
                int keycode = (int)event.xkey.keycode;
                APP_KeyCode key = APP__Translate_key(keycode);
				if (APP__data.keyboard[key] == APP__KEY_STATUS_PRESSED ||
					APP__data.keyboard[key] == APP__KEY_STATUS_DOWN) {

					APP__data.keyboard[key] = APP__KEY_STATUS_DOWN;
				}
				else {
					APP__data.keyboard[key] = APP__KEY_STATUS_PRESSED;
				}
				APP__data.keyboard[key] |= APP__KEY_STATUS_REPEAT; // Always set as repeat

				Status return_status;
				char buffer[32] = "";
				int bytes_length = Xutf8LookupString(APP__x11_data.xic, (XKeyPressedEvent *)&event, buffer, 32, NULL, &return_status);
				if (return_status == XLookupChars || return_status == XLookupBoth) {

					if (!APP__Is_char_filtered(buffer[0]) &&
						APP__data.text_input_bytes_count + bytes_length < APP__TEXT_INPUT_BUFFER_MAX) {

						for (int i = 0; i < bytes_length; ++i) {
							APP__data.text_input_buffer[APP__data.text_input_bytes_count+i] = buffer[i];
						}
						APP__data.text_input_bytes_count = APP__data.text_input_bytes_count + bytes_length;
						APP__data.text_input_buffer[APP__data.text_input_bytes_count] = '\0';
					}
				}
				break;
			}
			case KeyRelease: {
				// Checks if the key release is from an autorepeat
				// https://stackoverflow.com/questions/2100654/ignore-auto-repeat-in-x11-applications
				if (XEventsQueued(APP__x11_data.xdisplay, QueuedAfterReading)) {
					XEvent next_event;
					XPeekEvent(APP__x11_data.xdisplay, &next_event);
					if (next_event.type == KeyPress &&
						next_event.xkey.time == event.xkey.time &&
  					    next_event.xkey.keycode == event.xkey.keycode) {
					  break;
  					}
				}
                int keycode = (int)event.xkey.keycode;
                APP_KeyCode key = APP__Translate_key(keycode);
				APP__data.keyboard[key] = APP__KEY_STATUS_RELEASED;
				break;
            }
			case ButtonPress: {
				APP_MouseButton btn = APP__Translate_mouse_button(event.xbutton.button);
				if (btn != APP_MOUSE_BUTTON_INVALID) {
					APP__Report_mouse_button_down(btn);
				}
				else {
					/* might be a scroll event */
					switch (event.xbutton.button) {
                        case 4: APP__data.mouse.wheel_y =  1.0f; break;
                        case 5: APP__data.mouse.wheel_y = -1.0f; break;
                        case 6: APP__data.mouse.wheel_x =  1.0f; break;
                        case 7: APP__data.mouse.wheel_x = -1.0f; break;
                    }
				}
				break;
			}
			case ButtonRelease:
			{
				APP_MouseButton btn = APP__Translate_mouse_button(event.xbutton.button);
				if (btn != APP_MOUSE_BUTTON_INVALID) {
					APP__Report_mouse_button_up(btn);
				}
			    break;
			}
			case ClientMessage: {
				if (event.xclient.message_type == APP__x11_data.WM_PROTOCOLS) {
            	    const Atom protocol = (Atom)event.xclient.data.l[0];
            	    if (protocol == APP__x11_data.WM_DELETE_WINDOW) {
            	        APP__data.quit_requested = true;
            	    }
            	}
				break;
			}
			case MotionNotify: {
				APP__Report_mouse_move((float)event.xmotion.x, (float)event.xmotion.y);
				break;
			}
            break;// TODO(Tano) HANDLE EVERYTHING!!!!!

		}
	}

}




APP_INTERNAL int64_t
APP__linux_Time(void) {
	struct timespec current;
	clock_gettime(CLOCK_MONOTONIC_RAW, &current);
	const int64_t SECOND = 1000*1000*1000;
	int64_t result = (current.tv_sec - APP__x11_data.initial_time.tv_sec) * (1 * SECOND);
	result += current.tv_nsec - APP__x11_data.initial_time.tv_nsec;
	return result;
}






////////////////////////////////////////////////////////////////////////////////
//
//
//
// SOUND API
//
//
//
////////////////////////////////////////////////////////////////////////////////

#include <pthread.h>
#define ALSA_PCM_NEW_HW_PARAMS_API
#include <alsa/asoundlib.h>


static struct {
	snd_pcm_t* device;
	float* buffer;
	pthread_t thread;
	volatile bool thread_stop;
} APP__sound_player_backend = {0};


APP_INTERNAL void
APP__Cleanup_sound_player(void) {
	if (APP__sound_player_backend.device) {
		snd_pcm_close(APP__sound_player_backend.device);
		APP__sound_player_backend.device = NULL;
		snd_config_update_free_global();
	}
}


/* the streaming callback runs in a separate thread */
APP_INTERNAL void *
APP__Sound_player_thread(void *param) {
    snd_pcm_prepare(APP__sound_player_backend.device);
    while (!APP__sound_player_backend.thread_stop) {
        /* snd_pcm_writei() will be blocking until it needs data */
        int write_res = snd_pcm_writei(
				APP__sound_player_backend.device,
				APP__sound_player_backend.buffer,
				(snd_pcm_uframes_t)APP__data.sound_player_info.buffer_frames
		);
        if (write_res < 0) {
            /* underrun occurred */
            snd_pcm_prepare(APP__sound_player_backend.device);
        }
        else {
            /* fill the streaming buffer with new data */
			APP__data.sound_player_info.stream_cb(
					APP__data.sound_player_info.user_data,
					APP__sound_player_backend.buffer,
					APP__data.sound_player_info.buffer_frames,
					APP__data.sound_player_info.num_channels
			);
        }
    }
    return 0;
}



APP_PUBLIC int
APP_Launch_sound_player(APP_SoundPlayerDesc *desc) {
    int dir; uint32_t rate;
    int rc = snd_pcm_open(&APP__sound_player_backend.device, "default", SND_PCM_STREAM_PLAYBACK,	0);
    if (rc < 0) {
        fprintf(stderr, "Cannot open the audio device.\n");
		APP__Cleanup_sound_player();
        return -1;
    }

    /* configuration works by restricting the 'configuration space' step
       by step, we require all parameters except the sample rate and buffer size to
       match perfectly
    */
    snd_pcm_hw_params_t* params = 0;
    snd_pcm_hw_params_alloca(&params);
    int error_code = snd_pcm_hw_params_any(APP__sound_player_backend.device, params);
    if (0 > error_code) {
        printf("Broken configuration for %s PCM: no configurations available\n", snd_strerror(error_code));
        return error_code;
    }
    error_code = snd_pcm_hw_params_set_access(APP__sound_player_backend.device, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (0 > error_code) {
        printf("snd_pcm_hw_params_set_access() failed. Code: %d. Error: %s\n", error_code, snd_strerror(error_code));
        return error_code;
    }
    if (0 > snd_pcm_hw_params_set_format(APP__sound_player_backend.device, params, SND_PCM_FORMAT_FLOAT_LE)) {
        fprintf(stderr, "Cannot device doesn't support floats\n");
		APP__Cleanup_sound_player();
        return -1;
    }

    /* let ALSA pick a nearby sampling rate */
    rate = (uint32_t) desc->sample_rate;
    dir = 0;
    error_code = snd_pcm_hw_params_set_rate_near(APP__sound_player_backend.device, params, &rate, &dir);
    if (0 > error_code) {
        const char *error = snd_strerror(error_code);
        fprintf(stderr, "snd_pcm_hw_params_set_rate_near() failed. Code: %d, Error: %s\n", error_code, error);
		APP__Cleanup_sound_player();
        return -1;
    }

	/* Pick a near buffer size */
	snd_pcm_uframes_t buffer_frames = desc->buffer_frames;
    if (0 > snd_pcm_hw_params_set_buffer_size_near(APP__sound_player_backend.device, params, &buffer_frames)) {
        fprintf(stderr, "Requested buffer size not supported\n");
		APP__Cleanup_sound_player();
        return -1;
    }

    if (0 > snd_pcm_hw_params_set_channels(APP__sound_player_backend.device, params, (uint32_t)desc->num_channels)) {
        fprintf(stderr, "Requested channel count not supported\n");
		APP__Cleanup_sound_player();
        return -1;
    }

    
    if (0 > snd_pcm_hw_params(APP__sound_player_backend.device, params)) {
        fprintf(stderr, "snd_pcm_hw_params() failed\n");
		APP__Cleanup_sound_player();
        return -1;
    }


    /* read back actual sample rate and channels */
    APP__data.sound_player_info.sample_rate   = rate;
	APP__data.sound_player_info.buffer_frames = buffer_frames;
	APP__data.sound_player_info.user_data     = desc->user_data;
	APP__data.sound_player_info.stream_cb     = desc->stream_cb;
	APP__data.sound_player_info.num_channels  = desc->num_channels;

    /* allocate the streaming buffer */
	size_t buffer_nelems = APP__data.sound_player_info.buffer_frames * APP__data.sound_player_info.num_channels;
    APP__sound_player_backend.buffer = (float *)malloc(sizeof(float) * buffer_nelems); // TODO(Tano) Check this
	for (int i = 0; i < buffer_nelems; i+=1) APP__sound_player_backend.buffer[i] = 0.0f;

    /* create the buffer-streaming start thread */
    if (0 != pthread_create(&APP__sound_player_backend.thread, 0, APP__Sound_player_thread, 0)) {
        fprintf(stderr, "pthread_create() failed\n");
		APP__Cleanup_sound_player();
        return -1;
    }

    return 0;
}





APP_PUBLIC void
APP_Terminate_sound_player(void) {
	APP__sound_player_backend.thread_stop = true;
	void *dummy;
	pthread_join(APP__sound_player_backend.thread, &dummy);
	APP__Cleanup_sound_player();
	if (APP__sound_player_backend.buffer != NULL) {
		free(APP__sound_player_backend.buffer);
		APP__sound_player_backend.buffer = NULL;
	}
}












////////////////////////////////////////////////////////////////////////////////
//
//
//
// THREAD API
//
//
//
////////////////////////////////////////////////////////////////////////////////

#include <pthread.h> 

void
Mutex_init(Mutex *mutex) {
	if (pthread_mutex_init(mutex, NULL) != 0) {
		abort();
	}
}

void
Mutex_deinit(Mutex *mutex) {
}

void
Mutex_lock(Mutex *mutex) {
	if (pthread_mutex_lock(mutex) != 0) {
		abort();
	}
}

void
Mutex_unlock(Mutex *mutex) {
	if (pthread_mutex_unlock(mutex) != 0) {
		abort();
	}
}




////////////////////////////////////////////////////////////////////////////////
//
//
//
// FILESYSTEM API
//
//
//
////////////////////////////////////////////////////////////////////////////////


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Documented above
#if !defined(BUNDLED_TREE)
uint64_t
Get_file_modify_time(const char *filename) {
    struct stat file_stat;
    int err = stat(filename, &file_stat);
    if (err != 0) {
		return 0;
	}
    return (uint64_t)file_stat.st_mtime;
}
#endif













/////////////////////////////////////////////////////////////////////////////////
//
//
//
//                     WASM IMPLEMENTATION ||||
//                                         VVVV
//
//
////////////////////////////////////////////////////////////////////////////////

#elif defined(APP_WASM)

// Macro to generate a JavaScript function that can be called from C


APP__WA_JS(void, APP__JS_Init, (void), {
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	Module.ASM.WAFN_report_resize(canvas.width, canvas.height); // We call directly to set the correct size on the first frame

	// Sets the handler to report to the application the windows resizing.
	window.onresize = () => {
		canvas.width = window.innerWidth;
		canvas.height = window.innerHeight;
		Module.ASM.WAFN_report_resize(window.innerWidth, window.innerHeight);
	};

	// Key down
	window.addEventListener('keydown', (e) => {
		if (e.key.length === 1) { // Also fills the text input buffer
			var char_buffer_pointer = Module.ASM.WAFN_get_char_buffer();
			var char_len = stringToUTF8Array(e.key, char_buffer_pointer, 128);
			Module.ASM.WAFN_report_input_char(char_buffer_pointer, char_len);
		}
		// Prevent default browser's shortcuts
		e.preventDefault();
		Module.ASM.WAFN_report_keydown(e.keyCode);
	}, true);
	
	// Key up
	window.addEventListener('keyup', (e) => {
		Module.ASM.WAFN_report_keyup(e.keyCode);
	}, true);

	// Mouse position
	window.addEventListener('mousemove', function(e) {
		let rect = canvas.getBoundingClientRect();
		Module.ASM.APP__Report_mouse_move(e.clientX - rect.left, e.clientY - rect.top);
	}, false);
	
	// Mouse button down
	window.addEventListener('mousedown', function(e) {
		if (e.buttons & 1) Module.ASM.APP__Report_mouse_button_down(0); // left button
		if (e.buttons & 2) Module.ASM.APP__Report_mouse_button_down(1); // right button
		if (e.buttons & 4) Module.ASM.APP__Report_mouse_button_down(2); // middle button
	});

	// Mouse button up
	window.addEventListener('mouseup', function(e) {
		if      (e.button == 0) Module.ASM.APP__Report_mouse_button_up(0); // left button
		else if (e.button == 2) Module.ASM.APP__Report_mouse_button_up(1); // right button
		else if (e.button == 1) Module.ASM.APP__Report_mouse_button_up(2); // middle button
	});

	// Mouse button up
	window.addEventListener('wheel', function(e) {
		Module.ASM.WAFN_set_wheel(e.deltaX, -e.deltaY);
	});

	// Touch start
	window.addEventListener("touchstart", function(e) {
		let touches     = e.changedTouches;
		let canvas_rect = canvas.getBoundingClientRect();
		for (var i = 0; i < touches.length; i++) {
			let pos_x = touches[i].clientX - canvas_rect.left;
			let pos_y = touches[i].clientY - canvas_rect.top;
			Module.ASM.APP__Report_touch_event(touches[i].identifier, 0, pos_x, pos_y);
		}
	}, false);

	// Touch move
	window.addEventListener("touchmove", function(e) {
		let touches     = e.changedTouches;
		let canvas_rect = canvas.getBoundingClientRect();
		for (var i = 0; i < touches.length; i++) {
			let pos_x = touches[i].clientX - canvas_rect.left;
			let pos_y = touches[i].clientY - canvas_rect.top;
			Module.ASM.APP__Report_touch_event(touches[i].identifier, 1, pos_x, pos_y);
		}
	}, false);

	// Touch end
	window.addEventListener("touchend", function(e) {
		let touches     = e.changedTouches;
		let canvas_rect = canvas.getBoundingClientRect();
		for (var i = 0; i < touches.length; i++) {
			let pos_x = touches[i].clientX - canvas_rect.left;
			let pos_y = touches[i].clientY - canvas_rect.top;
			Module.ASM.APP__Report_touch_event(touches[i].identifier, 2, pos_x, pos_y);
		}
	}, false);

	// Touch cancel
	window.addEventListener("touchcancel", function(e) {
		let touches     = e.changedTouches;
		let canvas_rect = canvas.getBoundingClientRect();
		for (var i = 0; i < touches.length; i++) {
			let pos_x = touches[i].clientX - canvas_rect.left;
			let pos_y = touches[i].clientY - canvas_rect.top;
			Module.ASM.APP__Report_touch_event(touches[i].identifier, 3, pos_x, pos_y);
		}
	}, false);

	// Setups the frame handler
	function Application_frame() {
		var result = Module.ASM.APP__Handle_frame();
		if (result == 0) {
			window.requestAnimationFrame(Application_frame);
		}
	}
	window.requestAnimationFrame(Application_frame);

	Module.GLctx;
	Module.GLlastError;
	Module.GLcounter = 1;
	Module.GLbuffers = [];
	Module.GLprograms = [];
	Module.GLframebuffers = [];
	Module.GLtextures = [];
	Module.GLuniforms = [];
	Module.GLshaders = [];
	Module.GLprogramInfos = {};
	Module.GLpackAlignment = 4;
	Module.GLunpackAlignment = 4;
	Module.GLMINI_TEMP_BUFFER_SIZE = 256;
	Module.GLminiTempBuffer = null;
	Module.GLminiTempBufferViews = [0];
	Module.GLminiTempBuffer = new Float32Array(Module.GLMINI_TEMP_BUFFER_SIZE);
	for (var i = 0; i < Module.GLMINI_TEMP_BUFFER_SIZE; i++) Module.GLminiTempBufferViews[i] = Module.GLminiTempBuffer.subarray(0, i+1);

	var attr = { majorVersion: 1, minorVersion: 0, antialias: true, alpha: false };
	var errorInfo = "";
	try
	{
		let onContextCreationError = function(event) { errorInfo = event.statusMessage || errorInfo; };
		canvas.addEventListener('webglcontextcreationerror', onContextCreationError, false);
		try
		{
			Module.GLctx = canvas.getContext('webgl', attr) || canvas.getContext('experimental-webgl', attr);
		}
		finally { canvas.removeEventListener('webglcontextcreationerror', onContextCreationError, false); }
		if (!Module.GLctx) throw 'Could not create context';
	}
	catch (e)
	{
		abort("WEBGL", e + (errorInfo ? " (" + errorInfo + ")" : ""));
	}

	var exts = Module.GLctx.getSupportedExtensions();
	if (exts && exts.length > 0)
	{
		// These are the 'safe' feature-enabling extensions that don't add any performance impact related to e.g. debugging, and
		// should be enabled by default so that client GLES2/GL code will not need to go through extra hoops to get its stuff working.
		// As new extensions are ratified at http://www.khronos.org/registry/webgl/extensions/ , feel free to add your new extensions
		// here, as long as they don't produce a performance impact for users that might not be using those extensions.
		// E.g. debugging-related extensions should probably be off by default.
		var W = 'WEBGL_', O = 'OES_', E = 'EXT_', T = 'texture_', C = 'compressed_'+T;
		var automaticallyEnabledExtensions = [ // Khronos ratified WebGL extensions ordered by number (no debug extensions):
			O+T+'float', O+T+'half_float', O+'standard_derivatives',
			O+'vertex_array_object', W+C+'s3tc', W+'depth_texture',
			O+'element_index_uint', E+T+'filter_anisotropic', E+'frag_depth',
			W+'draw_buffers', 'ANGLE_instanced_arrays', O+T+'float_linear',
			O+T+'half_float_linear', E+'blend_minmax', E+'shader_texture_lod',
			// Community approved WebGL extensions ordered by number:
			W+C+'pvrtc', E+'color_buffer_half_float', W+'color_buffer_float',
			E+'sRGB', W+C+'etc1', E+'disjoint_timer_query',
			W+C+'etc', W+C+'astc', E+'color_buffer_float',
			W+C+'s3tc_srgb', E+'disjoint_timer_query_webgl2'];
		exts.forEach(function(ext)
		{
			if (automaticallyEnabledExtensions.indexOf(ext) != -1)
			{
				// Calling .getExtension enables that extension permanently, no need to store the return value to be enabled.
				Module.GLctx.getExtension(ext);
			}
		});
	}
	
	Module.GLgetNewId = function(table) {
		var ret = Module.GLcounter++;
		for (var i = table.length; i < ret; i++) table[i] = null;
		return ret;
	};

	Module.GLgetSource = function(shader, count, string, length) {
		var source = "";
		for (var i = 0; i < count; ++i)
		{
			var frag;
			if (length)
			{
				var len = HEAP32[(((length)+(i*4))>>2)];
				if (len < 0) frag = Pointer_stringify(HEAP32[(((string)+(i*4))>>2)]);
				else frag = Pointer_stringify(HEAP32[(((string)+(i*4))>>2)], len);
			}
			else frag = Pointer_stringify(HEAP32[(((string)+(i*4))>>2)]);
			source += frag;
		}
		return source;
	};

	Module.GLpopulateUniformTable = function(program) {
		var p = Module.GLprograms[program];
		Module.GLprogramInfos[program] =
		{
			uniforms: {},
			maxUniformLength: 0, // This is eagerly computed below, since we already enumerate all uniforms anyway.
			maxAttributeLength: -1, // This is lazily computed and cached, computed when/if first asked, '-1' meaning not computed yet.
			maxUniformBlockNameLength: -1 // Lazily computed as well
		};

		var ptable = Module.GLprogramInfos[program];
		var utable = ptable.uniforms;

		// A program's uniform table maps the string name of an uniform to an integer location of that uniform.
		// The global GLuniforms map maps integer locations to WebGLUniformLocations.
		var numUniforms = Module.GLctx.getProgramParameter(p, Module.GLctx.ACTIVE_UNIFORMS);
		for (var i = 0; i < numUniforms; ++i)
		{
			var u = Module.GLctx.getActiveUniform(p, i);

			var name = u.name;
			ptable.maxUniformLength = Math.max(ptable.maxUniformLength, name.length+1);

			// Strip off any trailing array specifier we might have got, e.g. '[0]'.
			if (name.indexOf(']', name.length-1) !== -1)
			{
				var ls = name.lastIndexOf('[');
				name = name.slice(0, ls);
			}

			// Optimize memory usage slightly: If we have an array of uniforms, e.g. 'vec3 colors[3];', then
			// only store the string 'colors' in utable, and 'colors[0]', 'colors[1]' and 'colors[2]' will be parsed as 'colors'+i.
			// Note that for the GLuniforms table, we still need to fetch the all WebGLUniformLocations for all the indices.
			var loc = Module.GLctx.getUniformLocation(p, name);
			if (loc != null)
			{
				var id = Module.GLgetNewId(Module.GLuniforms);
				utable[name] = [u.size, id];
				Module.GLuniforms[id] = loc;

				for (var j = 1; j < u.size; ++j)
				{
					var n = name + '['+j+']';
					loc = Module.GLctx.getUniformLocation(p, n);
					id = Module.GLgetNewId(Module.GLuniforms);

					Module.GLuniforms[id] = loc;
				}
			}
		}
	};

	Module.GLrecordError = function(err) {
		if (!GLlastError) GLlastError = err;
	};

	Module.webGLGet = function(name_, p, type) {
		checkHeap();
		// Guard against user passing a null pointer.
		// Note that GLES2 spec does not say anything about how passing a null pointer should be treated.
		// Testing on desktop core GL 3, the application crashes on glGetIntegerv to a null pointer, but
		// better to report an error instead of doing anything random.
		if (!p) { Module.GLrecordError(0x0501); return; } // GL_INVALID_VALUE

		var ret = undefined;
		switch(name_) {
			// Handle a few trivial GLES values
			case 0x8DFA: ret = 1; break; // GL_SHADER_COMPILER
			case 0x8DF8: // GL_SHADER_BINARY_FORMATS
				if (type !== 'Integer' && type !== 'Integer64') Module.GLrecordError(0x0500); // GL_INVALID_ENUM
				return; // Do not write anything to the out pointer, since no binary formats are supported.
			case 0x8DF9: ret = 0; break; // GL_NUM_SHADER_BINARY_FORMATS
			case 0x86A2: // GL_NUM_COMPRESSED_TEXTURE_FORMATS
				// WebGL doesn't have GL_NUM_COMPRESSED_TEXTURE_FORMATS (it's obsolete since GL_COMPRESSED_TEXTURE_FORMATS returns a JS array that can be queried for length),
				// so implement it ourselves to allow C++ GLES2 code get the length.
				var formats = Module.GLctx.getParameter(0x86A3); // GL_COMPRESSED_TEXTURE_FORMATS
				ret = formats.length;
				break;
		}

		if (ret === undefined) {
			var result = Module.GLctx.getParameter(name_);
			switch (typeof(result)) {
				case 'number':
					ret = result;
					break;
				case 'boolean':
					ret = result ? 1 : 0;
					break;
				case 'string':
					Module.GLrecordError(0x0500); // GL_INVALID_ENUM
					return;
				case 'object':
					if (result === null) {
						// null is a valid result for some (e.g., which buffer is bound - perhaps nothing is bound), but otherwise
						// can mean an invalid name_, which we need to report as an error
						switch(name_)
						{
							case 0x8894: // ARRAY_BUFFER_BINDING
							case 0x8B8D: // CURRENT_PROGRAM
							case 0x8895: // ELEMENT_ARRAY_BUFFER_BINDING
							case 0x8CA6: // FRAMEBUFFER_BINDING
							case 0x8CA7: // RENDERBUFFER_BINDING
							case 0x8069: // TEXTURE_BINDING_2D
							case 0x8514: // TEXTURE_BINDING_CUBE_MAP
								ret = 0;
								break;
							default:
								Module.GLrecordError(0x0500); // GL_INVALID_ENUM
								return;
						}
					}
					else if (result instanceof Float32Array || result instanceof Uint32Array || result instanceof Int32Array || result instanceof Array)
					{
						for (var i = 0; i < result.length; ++i) {
							switch (type)
							{
								case 'Integer': HEAP32[(((p)+(i*4))>>2)]=result[i]; break;
								case 'Float':   HEAPF32[(((p)+(i*4))>>2)]=result[i]; break;
								case 'Boolean': HEAP8[(((p)+(i))>>0)]=result[i] ? 1 : 0; break;
								default: abort('WEBGL', 'internal glGet error, bad type: ' + type);
							}
						}
						return;
					}
					else if (result instanceof WebGLBuffer || result instanceof WebGLProgram || result instanceof WebGLFramebuffer || result instanceof WebGLRenderbuffer || result instanceof WebGLTexture)
					{
						ret = result.name | 0;
					}
					else
					{
						Module.GLrecordError(0x0500); // GL_INVALID_ENUM
						return;
					}
					break;
				default:
					Module.GLrecordError(0x0500); // GL_INVALID_ENUM
					return;
			}
		}

		switch (type)
		{
			case 'Integer64': (tempI64 = [ret>>>0,(tempDouble=ret,(+(Math.abs(tempDouble))) >= 1.0 ? (tempDouble > 0.0 ? ((Math.min((+(Math.floor((tempDouble)/4294967296.0))), 4294967295.0))|0)>>>0 : (~~((+(Math.ceil((tempDouble - +(((~~(tempDouble)))>>>0))/4294967296.0)))))>>>0) : 0)],HEAP32[((p)>>2)]=tempI64[0],HEAP32[(((p)+(4))>>2)]=tempI64[1]); break;
			case 'Integer': HEAP32[((p)>>2)] = ret; break;
			case 'Float':   HEAPF32[((p)>>2)] = ret; break;
			case 'Boolean': HEAP8[((p)>>0)] = ret ? 1 : 0; break;
			default: abort('WEBGL', 'internal glGet error, bad type: ' + type);
		}
	};

	Module.webGLGetTexPixelData = function(type, format, width, height, pixels, internalFormat) {
		checkHeap();
		var sizePerPixel;
		var numChannels;
		switch(format) {
			case 0x1906: case 0x1909: case 0x1902: numChannels = 1; break; //GL_ALPHA, GL_LUMINANCE, GL_DEPTH_COMPONENT
			case 0x190A: numChannels = 2; break; //GL_LUMINANCE_ALPHA
			case 0x1907: case 0x8C40: numChannels = 3; break; //GL_RGB, GL_SRGB_EXT
			case 0x1908: case 0x8C42: numChannels = 4; break; //GL_RGBA, GL_SRGB_ALPHA_EXT
			default: throw new Error();//GLrecordError(0x0500); return null; //GL_INVALID_ENUM
		}
		switch (type) {
			case 0x1401: sizePerPixel = numChannels*1; break; //GL_UNSIGNED_BYTE
			case 0x1403: case 0x8D61: sizePerPixel = numChannels*2; break; //GL_UNSIGNED_SHORT, GL_HALF_FLOAT_OES
			case 0x1405: case 0x1406: sizePerPixel = numChannels*4; break; //GL_UNSIGNED_INT, GL_FLOAT
			case 0x84FA: sizePerPixel = 4; break; //GL_UNSIGNED_INT_24_8_WEBGL/GL_UNSIGNED_INT_24_8
			case 0x8363: case 0x8033: case 0x8034: sizePerPixel = 2; break; //GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1
			default: throw new Error();//GLrecordError(0x0500); return null; //GL_INVALID_ENUM
		}

		function roundedToNextMultipleOf(x, y) { return Math.floor((x + y - 1) / y) * y; }
		var plainRowSize = width * sizePerPixel;
		var alignedRowSize = roundedToNextMultipleOf(plainRowSize, Module.GLunpackAlignment);
		var bytes = (height <= 0 ? 0 : ((height - 1) * alignedRowSize + plainRowSize));

		switch(type)
		{
			case 0x1401: return HEAPU8.subarray((pixels),(pixels+bytes)); //GL_UNSIGNED_BYTE
			case 0x1406: return HEAPF32.subarray((pixels)>>2,(pixels+bytes)>>2); //GL_FLOAT
			case 0x1405: case 0x84FA: return HEAPU32.subarray((pixels)>>2,(pixels+bytes)>>2); //GL_UNSIGNED_INT, GL_UNSIGNED_INT_24_8_WEBGL/GL_UNSIGNED_INT_24_8
			case 0x1403: case 0x8363: case 0x8033: case 0x8034: case 0x8D61: return HEAPU16.subarray((pixels)>>1,(pixels+bytes)>>1); //GL_UNSIGNED_SHORT, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1, GL_HALF_FLOAT_OES
			default: throw new Error();//GLrecordError(0x0500); return null; //GL_INVALID_ENUM
		}
	}



});

APP__WA_JS(int32_t, APP__JS_Get_time, (void), {
	return Date.now();
});

APP__WA_JS(void, APP__JS_Set_window_title, (const char *title, int len), {
	const UTF8_decoder = new TextDecoder("utf-8");
	window.document.title = UTF8_decoder.decode(new Uint8Array(Module.ASM.memory.buffer, title, len));
});

APP__WA_JS(void, APP__JS_Set_fullscreen, (bool enable), {
	if(enable) {
		document.documentElement.requestFullscreen().catch(console.log);
	}else {
		document.exitFullscreen();
	}
});

APP__WA_JS(void, APP__JS_Show_mouse, (bool show), {
	if (show) {
		canvas.style.cursor = 'auto';
	}
	else {
		canvas.style.cursor = 'none';

	}
});

APP__WA_JS(bool, APP__JS_Window_has_focus, (void), {
	return document.hasFocus();
});



APP_INTERNAL int
APP__wasm_Init(const char *title, int width, int height) {

	APP__data.default_width  = width;
	APP__data.default_height = height;
	APP__data.w_width  = width;
	APP__data.w_height = height;

	APP__JS_Init();

	APP__wasm_Set_window_title(title);

	int64_t MSECOND = 1000 * 1000;
	APP__wasm_data.initial_time = MSECOND*(int64_t)APP__JS_Get_time();
	return 0;
}


APP_INTERNAL void
APP__wasm_Shutdown(void) {
	// We set the viewport black
	glClearColor(0.0, 0.0, 0.0, 1.0);// background color	
	glClear(GL_COLOR_BUFFER_BIT);
}

APP_INTERNAL void
APP__wasm_Set_window_title(const char *title) {
	int len = 0;
	while (title[len]) len += 1;
	APP__JS_Set_window_title(title, len);
}

APP_INTERNAL void
APP__wasm_Set_fullscreen(bool enable) {
	APP__JS_Set_fullscreen(enable);
}

APP_INTERNAL void
APP__wasm_Show_mouse(bool show) {
	APP__JS_Show_mouse(show);
}

APP_INTERNAL int64_t
APP__wasm_Time(void) {
	int64_t MSECOND = 1000 * 1000;
	return (MSECOND*(int64_t)APP__JS_Get_time()) - APP__wasm_data.initial_time;
}


#define APP__MAX_KEYMAPPING 512

static APP_KeyCode APP__key_mapping[APP__MAX_KEYMAPPING] = {
	[8]   = APP_KEY_BACKSPACE,
	[9]   = APP_KEY_TAB,
	[13]  = APP_KEY_ENTER,
	[16]  = APP_KEY_LEFT_SHIFT,
	[17]  = APP_KEY_LEFT_CONTROL,
	[18]  = APP_KEY_LEFT_ALT,
	[19]  = APP_KEY_PAUSE,
	[27]  = APP_KEY_ESCAPE,
	[32]  = APP_KEY_SPACE,
	[33]  = APP_KEY_PAGE_UP,
	[34]  = APP_KEY_PAGE_DOWN,
	[35]  = APP_KEY_END,
	[36]  = APP_KEY_HOME,
	[37]  = APP_KEY_LEFT,
	[38]  = APP_KEY_UP,
	[39]  = APP_KEY_RIGHT,
	[40]  = APP_KEY_DOWN,
	[45]  = APP_KEY_INSERT,
	[46]  = APP_KEY_DELETE,
	[48]  = APP_KEY_0,
	[49]  = APP_KEY_1,
	[50]  = APP_KEY_2,
	[51]  = APP_KEY_3,
	[52]  = APP_KEY_4,
	[53]  = APP_KEY_5,
	[54]  = APP_KEY_6,
	[55]  = APP_KEY_7,
	[56]  = APP_KEY_8,
	[57]  = APP_KEY_9,
	[59]  = APP_KEY_SEMICOLON,
	[64]  = APP_KEY_EQUAL,
	[65]  = APP_KEY_A,
	[66]  = APP_KEY_B,
	[67]  = APP_KEY_C,
	[68]  = APP_KEY_D,
	[69]  = APP_KEY_E,
	[70]  = APP_KEY_F,
	[71]  = APP_KEY_G,
	[72]  = APP_KEY_H,
	[73]  = APP_KEY_I,
	[74]  = APP_KEY_J,
	[75]  = APP_KEY_K,
	[76]  = APP_KEY_L,
	[77]  = APP_KEY_M,
	[78]  = APP_KEY_N,
	[79]  = APP_KEY_O,
	[80]  = APP_KEY_P,
	[81]  = APP_KEY_Q,
	[82]  = APP_KEY_R,
	[83]  = APP_KEY_S,
	[84]  = APP_KEY_T,
	[85]  = APP_KEY_U,
	[86]  = APP_KEY_V,
	[87]  = APP_KEY_W,
	[88]  = APP_KEY_X,
	[89]  = APP_KEY_Y,
	[90]  = APP_KEY_Z,
	[91]  = APP_KEY_LEFT_SUPER,
	[93]  = APP_KEY_MENU,
	[96]  = APP_KEY_KP_0,
	[97]  = APP_KEY_KP_1,
	[98]  = APP_KEY_KP_2,
	[99]  = APP_KEY_KP_3,
	[100] = APP_KEY_KP_4,
	[101] = APP_KEY_KP_5,
	[102] = APP_KEY_KP_6,
	[103] = APP_KEY_KP_7,
	[104] = APP_KEY_KP_8,
	[105] = APP_KEY_KP_9,
	[106] = APP_KEY_KP_MULTIPLY,
	[107] = APP_KEY_KP_ADD,
	[109] = APP_KEY_KP_SUBTRACT,
	[110] = APP_KEY_KP_DECIMAL,
	[111] = APP_KEY_KP_DIVIDE,
	[112] = APP_KEY_F1,
	[113] = APP_KEY_F2,
	[114] = APP_KEY_F3,
	[115] = APP_KEY_F4,
	[116] = APP_KEY_F5,
	[117] = APP_KEY_F6,
	[118] = APP_KEY_F7,
	[119] = APP_KEY_F8,
	[120] = APP_KEY_F9,
	[121] = APP_KEY_F10,
	[122] = APP_KEY_F11,
	[123] = APP_KEY_F12,
	[144] = APP_KEY_NUM_LOCK,
	[145] = APP_KEY_SCROLL_LOCK,
	[173] = APP_KEY_MINUS,
	[186] = APP_KEY_SEMICOLON,
	[187] = APP_KEY_EQUAL,
	[188] = APP_KEY_COMMA,
	[189] = APP_KEY_MINUS,
	[190] = APP_KEY_PERIOD,
	[191] = APP_KEY_SLASH,
	[192] = APP_KEY_GRAVE_ACCENT,
	[219] = APP_KEY_LEFT_BRACKET,
	[220] = APP_KEY_BACKSLASH,
	[221] = APP_KEY_RIGHT_BRACKET,
	[222] = APP_KEY_APOSTROPHE,
	[224] = APP_KEY_LEFT_SUPER,
};








/* WAFN_report_resize
 * ========================================
 *
 * DESCRIPTIION
 * ----------------------------------------
 * Binding to call from javascript on each frame
 *
 */
__attribute__((export_name("WAFN_report_resize"))) void
WAFN_report_resize(int w, int h) {
	APP__data.w_width  = w;
	APP__data.w_height = h;
	APP__data.window_resized = true;
}


// Buffer to put which character was send from javascript
__attribute__((export_name("WAFN_get_char_buffer"))) char *
WAFN_get_char_buffer(void){
	static char buffer[128] = "";
	return buffer;
}


/* WAFN_report_keydown
 * ========================================
 *
 * DESCRIPTIION
 * ----------------------------------------
 * Binding to call from javascript on each keydown
 *
 */
__attribute__((export_name("WAFN_report_input_char"))) void
WAFN_report_input_char(char *utf8_char, int char_len) {

	if (!APP__Is_char_filtered(utf8_char[0]) &&
		APP__data.text_input_bytes_count + char_len < APP__TEXT_INPUT_BUFFER_MAX) {

		for (int i = 0; i < char_len; ++i) {
			APP__data.text_input_buffer[APP__data.text_input_bytes_count+i] = utf8_char[i];
		}
		APP__data.text_input_bytes_count = APP__data.text_input_bytes_count + char_len;
		APP__data.text_input_buffer[APP__data.text_input_bytes_count] = '\0';

	}
}




/* WAFN_report_keydown
 * ========================================
 *
 * DESCRIPTIION
 * ----------------------------------------
 * Binding to call from javascript on each keydown
 *
 */
__attribute__((export_name("WAFN_report_keydown"))) void
WAFN_report_keydown(int keycode) {
	if (keycode >= 0 && keycode < APP__MAX_KEYMAPPING) {
		int key_id = APP__key_mapping[keycode];
		if (APP__data.keyboard[key_id] & APP__KEY_STATUS_PRESSED ||
			APP__data.keyboard[key_id] & APP__KEY_STATUS_DOWN) {

			APP__data.keyboard[key_id] = APP__KEY_STATUS_DOWN;
		}
		else {
			APP__data.keyboard[key_id] = APP__KEY_STATUS_PRESSED;
		}
		APP__data.keyboard[key_id] |= APP__KEY_STATUS_REPEAT;
	}
}


/* WAFN_report_keyup
 * ========================================
 *
 * DESCRIPTIION
 * ----------------------------------------
 * Binding to call from javascript on each keyup
 *
 */
__attribute__((export_name("WAFN_report_keyup"))) void
WAFN_report_keyup(int keycode) {
	if (keycode >= 0 && keycode < APP__MAX_KEYMAPPING) {
		APP__data.keyboard[APP__key_mapping[keycode]] = APP__KEY_STATUS_RELEASED;
	}
}



__attribute__((export_name("WAFN_set_wheel"))) void
WAFN_set_wheel(float delta_x, float delta_y) {
	APP__data.mouse.wheel_x = delta_x;
	APP__data.mouse.wheel_y = delta_y;
}


APP_INTERNAL void
APP__wasm_Process_events(void) {
	APP__data.focus = APP__JS_Window_has_focus();
}




////////////////////////////////////////////////////////////////////////////////
//
//
//
// SOUND API
//
//
//
////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>

static struct SoundPlayerBackend {
	float *buffer;
} APP__sound_player_backend = {0};

extern void JS_start_audio(uint32_t sample_rate, uint32_t n_channels, uint32_t n_frames, float *buffer);
extern void JS_terminate_audio();


__attribute__((export_name("WAFN_audio_cb"))) bool
WAFN_audio_cb(uint32_t n_frames, uint32_t n_channels, float *buffer) {
	int result = APP__data.sound_player_info.stream_cb(
			APP__data.sound_player_info.user_data,
			buffer,
			n_frames,
			n_channels
	);

	return result == 0;
}


APP_PUBLIC int
APP__Launch_sound_player(APP_SoundPlayerDesc *desc) {
	APP__sound_player_backend.buffer = (float *)malloc(sizeof(float) * desc->num_channels * desc->buffer_frames);
	JS_start_audio(
			desc->sample_rate,
			desc->num_channels,
			desc->buffer_frames,
			APP__sound_player_backend.buffer
	);

	APP__data.sound_player_info.sample_rate   = desc->sample_rate;
	APP__data.sound_player_info.buffer_frames = desc->buffer_frames;
	APP__data.sound_player_info.user_data     = desc->user_data;
	APP__data.sound_player_info.stream_cb     = desc->stream_cb;
	APP__data.sound_player_info.num_channels  = desc->num_channels;
	return 0;
}





APP_PUBLIC void
APP__Terminate_sound_player(void) {
	if (APP__sound_player_backend.buffer != NULL) {
		free(APP__sound_player_backend.buffer);
		APP__sound_player_backend.buffer = NULL;
	}
	JS_terminate_audio();
}








////////////////////////////////////////////////////////////////////////////////
//
//
//
// THREAD API
//
//
//
////////////////////////////////////////////////////////////////////////////////

//
// We don't use threads on wasm, so this does nothing.
//

void
Mutex_init(Mutex *mutex) {
}

void
Mutex_deinit(Mutex *mutex) {
}

void
Mutex_lock(Mutex *mutex) {
}

void
Mutex_unlock(Mutex *mutex) {
}

#endif // defined (APP_WASM)



#if defined(BUNDLED_TREE)
	extern const unsigned int BUNDLE_FILES_COUNT;
	extern const char * const bundle_filenames[];
	extern char * const bundle_files_index[];
	extern const unsigned int bundle_file_sizes[];
#endif



// Documented on the above, on the head section
#if defined(APP_WASM)

APP_PUBLIC int
APP_Run_application_loop(int(*application_frame)(void)) {
	APP__data.frame_callback = application_frame;
	return 0;
}

#else

APP_PUBLIC int
APP_Run_application_loop(int(*application_frame)(void)) {
	assert(application_frame);
	APP__data.frame_callback = application_frame;
	int loop_result = 0;
	for (;;) {
		loop_result = APP__Handle_frame();
		if (loop_result != 0) {break;}
	}
#if defined(APP_WINDOWS)
	// I'm not sure if this can be done here or must be always inside the windowProc :/ Tano.
	PostQuitMessage(0);
#endif
	if (loop_result == 1) {
		return 0;
	}
	return loop_result;
}

#endif




#include <string.h>


// Documented on the above, on the head section
uint8_t *
APP_Get_file_contentsz(const char *filename, uint32_t *size) {
#if defined(BUNDLED_TREE)
	// This is a linear search, we may use a hashmap :/
	for (uint32_t i = 0; i < BUNDLE_FILES_COUNT; ++i) {
		if (strcmp(filename, bundle_filenames[i]) == 0) {
			if (size) { *size = bundle_file_sizes[i]; }
			return (uint8_t *)bundle_files_index[i];
		}
	}
	return NULL;
#else
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		return NULL;
	}
	fseek(f, 0L, SEEK_END);	
	uint32_t file_size = ftell(f);
	fseek(f, 0L, SEEK_SET);	
	uint8_t *data = malloc(file_size + 1); // TODO(Tano) Check this??
	fread(data, 1, file_size, f);
	fclose(f);

	data[file_size] = '\0';
	if (size) {*size = file_size;}
	return data;
#endif
}



// Documented on the above, on the head section
void
APP_Free_file_contents(uint8_t *data) {
	if (data == NULL) {return;}
#if !defined(BUNDLED_TREE)
	free(data);
#endif
}


// Documented above
#if defined(BUNDLED_TREE)
uint64_t
APP_Get_file_modify_time(const char *filename) {
	return 0;
}
#endif


#endif // _APP_H_


