//
// base.h
//
// This header contains basic types, and very basic function helpers (or macros) that don't rely
// on platform specific code.
//
//

#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>


typedef uint8_t  u8;
typedef int8_t   i8;
typedef uint16_t u16;
typedef int16_t  i16;
typedef uint32_t u32;
typedef int32_t  i32;
typedef uint64_t u64;
typedef int64_t  i64;

typedef float  f32;
typedef double f64;







/*
* DESCRIPTIION
* ----------------------------------------------------------------------
* Asserts if the first value is false aborts the program, outputting the
* formated string passed as parameter.
*
* If the program is compiled with release mode this function disapears.
*
* VARIABLES
* ---------------------------------------------------------------------
*   assert_val: bool that triggers the assert.
*   fmt_msg: The format string msg.
*   ... : All the format values.
*
*/
#define Assert(assert_val, ...) _Assert((assert_val), __FILE__, __LINE__, __VA_ARGS__)

static void
_Assert(bool assert_val, const char *filename, int file_line, const char *fmt_msg, ...) {
	#if !defined(NDEBUG)
		if (!assert_val) {
			fprintf(stderr, "ASSERT: %s:%d\n", filename, file_line);
			va_list args;
    		va_start(args, fmt_msg);
    		vfprintf(stderr, fmt_msg, args);
    		va_end(args);
			fprintf(stderr, "\n");
			abort();
		}
	#endif
}


/*
* Panic
* =====================================================================
*
* DESCRIPTIION
* ----------------------------------------------------------------------
* Aborts the program printing a message to stderr and the filename and line
* where was called from.
*
* Note that is a macro to implicitly pass the current line and filename.
*
* VARIABLES
* ---------------------------------------------------------------------
*   fmt_msg: Message to print
*
*/
#define Panic(...) _Panic(__FILE__, __LINE__, __VA_ARGS__)

static void
_Panic(const char *filename, int file_line, const char *fmt_msg, ...) {
	fprintf(stderr, "\n======= PANIC =======\n%s:%d: ", filename, file_line);
	va_list args;
	va_start(args, fmt_msg);
	vfprintf(stderr, fmt_msg, args);
	va_end(args);
	fprintf(stderr, "\n");
	abort();
}






/*
* DESCRIPTIION
* ----------------------------------------------------------------------
* Allocs memory on the heap, this function will always return a valid value
* if cannot reserve enought memory will abort.
*
* Note that this is a macro reserve memory based on le lenght of the type
* passed.
*
*
* VARIABLES
* ---------------------------------------------------------------------
*   T: The type to reserve.
*   size: Amount of elements.
*
* RETURN
* ---------------------------------------------------------------------
*  The reserved amount of memory.
*
*/
#define Alloc(T, size) (T *)_Alloc((size) * sizeof(T))

void *
_Alloc(size_t size) {
	void *result = malloc(size);
	if (result == NULL) {
		Panic("OUT OF MEMORY");
	}
	return result;
}




/*
* DESCRIPTIION
* ----------------------------------------------------------------------
* Allocs memory on the heap, this function will always return a valid value
* if cannot reserve enought memory will abort.
*
* Note that this is a macro reserve memory based on le lenght of the type
* passed.
*
*
* VARIABLES
* ---------------------------------------------------------------------
*   T: The type to reserve.
*   size: Amount of elements.
*
* RETURN
* ---------------------------------------------------------------------
*  The reserved amount of memory.
*
*/
#define Realloc(T, old_pointer, size) (T *)_Relloc((void *)old_pointer, (size) * sizeof(T))

void *
_Relloc(void *old_pointer, size_t size) {
	void *result = realloc(old_pointer, size);
	if (result == NULL) {
		Panic("OUT OF MEMORY");
	}
	return result;
}





#endif // _BASE_H_

