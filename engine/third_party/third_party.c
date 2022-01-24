
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_vorbis.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"


// Weird error stpcpy undefined when the target is windows
// https://github.com/Neutron-Clang/neutron-toolchain
// https://github.com/kdrag0n/proton_zf6/commit/cec73f0775526
char *stpcpy(char *__restrict__ dest, const char *__restrict__ src);
char *stpcpy(char *__restrict__ dest, const char *__restrict__ src)
{
	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return --dest;
}
#include "parson.c"

