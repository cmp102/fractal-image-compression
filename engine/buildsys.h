#ifndef BUILDSYS_H

#include <stdbool.h>
#include <stdint.h>


bool
buildsys_Run_command(const char *command);

void
buildsys_Create_directory(const char *directory);

bool
buildsys_Copy_file(const char *src, const char *dst);

typedef enum {
	BUILDSYS_BUILD_MODE_DEBUG,
	BUILDSYS_BUILD_MODE_RELEASE_FAST,
	BUILDSYS_BUILD_MODE_RELEASE_SMALL,
} buildsys_BuildMode;

typedef enum {
	BUILDSYS_BUILD_TARGET_NATIVE,
	BUILDSYS_BUILD_TARGET_LINUX,
	BUILDSYS_BUILD_TARGET_WINDOWS,
	BUILDSYS_BUILD_TARGET_WASM,
} buildsys_BuildTarget;


typedef struct {
	const char *compiler;
	const char **sources;
	uint64_t sources_count;
	uint64_t sources_cap;
	const char *output;
	buildsys_BuildTarget build_target;
	const char **defines;
	uint64_t defines_count;
	uint64_t defines_cap;
	buildsys_BuildMode build_mode;
	const char **link_libraries;
	uint64_t link_libraries_count;
	uint64_t link_libraries_cap;
} buildsys_ExecutableBuilder;


buildsys_ExecutableBuilder
buildsys_Make_executable_builder();

buildsys_ExecutableBuilder
buildsys_Clone_executable_builder(buildsys_ExecutableBuilder *eb);

void
buildsys_Free_executable_builder(buildsys_ExecutableBuilder *eb);

void
buildsys_ExecutableBuilder_set_compiler(buildsys_ExecutableBuilder *eb, const char *compiler);

void
buildsys_ExecutableBuilder_add_source(buildsys_ExecutableBuilder *eb, const char *source);

void
buildsys_ExecutableBuilder_set_output(buildsys_ExecutableBuilder *eb, const char *output);

void
buildsys_ExecutableBuilder_set_target(buildsys_ExecutableBuilder *eb, buildsys_BuildTarget build_target);

void
buildsys_ExecutableBuilder_add_define(buildsys_ExecutableBuilder *eb, const char *define);

void
buildsys_ExecutableBuilder_set_build_mode(buildsys_ExecutableBuilder *eb, buildsys_BuildMode build_mode);

void
buildsys_ExecutableBuilder_add_link_library(buildsys_ExecutableBuilder *eb, const char *library);

bool
buildsys_ExecutableBuilder_build(buildsys_ExecutableBuilder *eb);

#ifndef BUILDYS_ONLY_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#ifdef WIN32
#include <direct.h>
#endif


bool
buildsys_Run_command(const char *command) {
	printf("Command: %s\n", command);
	int success = system(command);
	return (success == 0);
}


buildsys_ExecutableBuilder
buildsys_Make_executable_builder() {
	buildsys_ExecutableBuilder eb = {0};
	eb.compiler = "cc";
	return eb;
}

void
buildsys_Free_executable_builder(buildsys_ExecutableBuilder *eb) {
	free(eb->sources);
	free(eb->defines);
	free(eb->link_libraries);
	*eb = buildsys_Make_executable_builder();
}

buildsys_ExecutableBuilder
buildsys_Clone_executable_builder(buildsys_ExecutableBuilder *eb) {
	buildsys_ExecutableBuilder cloned_eb = *eb;
	if (cloned_eb.sources_count > 0) {
		cloned_eb.sources = malloc(sizeof(const char *) * cloned_eb.sources_cap);
		if (cloned_eb.sources == NULL) {
			fprintf(stderr, "Out of memory\n");
			abort();
		}
		for (uint64_t i = 0; i < cloned_eb.sources_count; ++i) {
			cloned_eb.sources[i] = eb->sources[i];
		}
	}

	if (cloned_eb.defines_count > 0) {
		cloned_eb.defines = malloc(sizeof(const char *) * cloned_eb.defines_cap);
		if (cloned_eb.defines == NULL) {
			fprintf(stderr, "Out of memory\n");
			abort();
		}
		for (uint64_t i = 0; i < cloned_eb.defines_count; ++i) {
			cloned_eb.defines[i] = eb->defines[i];
		}
	}

	if (cloned_eb.link_libraries_count > 0) {
		cloned_eb.link_libraries = malloc(sizeof(const char *) * cloned_eb.link_libraries_cap);
		if (cloned_eb.link_libraries == NULL) {
			fprintf(stderr, "Out of memory\n");
			abort();
		}
		for (uint64_t i = 0; i < cloned_eb.link_libraries_count; ++i) {
			cloned_eb.link_libraries[i] = eb->link_libraries[i];
		}
	}

	return cloned_eb;
}

void
buildsys_ExecutableBuilder_set_compiler(buildsys_ExecutableBuilder *eb, const char *compiler) {
	eb->compiler = compiler;
}



void *
buildsys__Array_pushback(
		void *arr,
		uint64_t len,
		uint64_t cap,
		uint64_t elem_size, 
		void *element,
		uint64_t *len_out,
		uint64_t *cap_out) {

	if (len >= cap) {
		uint32_t new_cap;
		if (cap == 0) {
			new_cap = 1;
		}
		else {
			new_cap = cap * 2;
		}
		void *new_mem = realloc(arr, elem_size * new_cap);
		if (new_mem == NULL) {
			fprintf(stderr, "Out of memory\n");
			abort();
		}
		arr = new_mem;
		cap = new_cap;
	}

	memcpy(&((char *)arr)[len * elem_size], element, elem_size);
	*len_out = len + 1;
	*cap_out = cap;
	return arr;
}

void
buildsys_ExecutableBuilder_add_source(buildsys_ExecutableBuilder *eb, const char *source) {
	eb->sources = buildsys__Array_pushback(
			(void *)eb->sources,
			eb->sources_count,
			eb->sources_cap,
			sizeof(const char *),
			(void*)&source,
			&eb->sources_count,
			&eb->sources_cap);
}

void
buildsys_ExecutableBuilder_set_output(buildsys_ExecutableBuilder *eb, const char *output) {
	eb->output = output;
}

void
buildsys_ExecutableBuilder_set_target(buildsys_ExecutableBuilder *eb, buildsys_BuildTarget build_target) {
	eb->build_target = build_target;
}

void
buildsys_ExecutableBuilder_add_define(buildsys_ExecutableBuilder *eb, const char *define) {
	eb->defines = buildsys__Array_pushback(
			(void *)eb->defines,
			eb->defines_count,
			eb->defines_cap,
			sizeof(const char *),
			(void*)&define,
			&eb->defines_count,
			&eb->defines_cap);
}

void
buildsys_ExecutableBuilder_set_build_mode(buildsys_ExecutableBuilder *eb, buildsys_BuildMode build_mode) {
	eb->build_mode = build_mode;
}

void
buildsys_ExecutableBuilder_add_link_library(buildsys_ExecutableBuilder *eb, const char *library) {
	eb->link_libraries = buildsys__Array_pushback(
			(void *)eb->link_libraries,
			eb->link_libraries_count,
			eb->link_libraries_cap,
			sizeof(const char *),
			(void*)&library,
			&eb->link_libraries_count,
			&eb->link_libraries_cap);
}


#ifndef BUILDSYS_BUILD_COMMAND_BUFFER_MAX_SIZE
#define BUILDSYS_BUILD_COMMAND_BUFFER_MAX_SIZE 8192
#endif

static uint32_t
buildsys__Build_exec_cat_command(char *str_dst, const char *str, uint32_t length) {
	const char *str_cursor = str;
	uint32_t length_result = length;
	while(*str_cursor) {
		if (length_result >= BUILDSYS_BUILD_COMMAND_BUFFER_MAX_SIZE-1) {
			fprintf(stderr, "\nCommand buffer max size exceeded!!\nConsider increasing it. Aborting... \n");
			abort();
		}
		str_dst[length_result] = *str_cursor;
		length_result += 1;
		str_cursor += 1;
	}
	str_dst[length_result] = '\0';
	return length_result;
}


bool
buildsys_ExecutableBuilder_build(buildsys_ExecutableBuilder *eb) {

	static char build_command_buffer[BUILDSYS_BUILD_COMMAND_BUFFER_MAX_SIZE] = {0};
	uint32_t command_len   = 0;

	{ // Compiler command
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, eb->compiler, command_len);
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " ", command_len);
	}

	command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -Wall ", command_len);

	{ // Add the source files
		uint64_t sources_count = eb->sources_count;
		for (uint64_t i = 0; i < sources_count; ++i) {
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, eb->sources[i], command_len);
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, " ", command_len);
		}
	}

	{ // Output executable
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -o ", command_len);
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, eb->output, command_len);
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " ", command_len);
	}

	if (eb->build_target == BUILDSYS_BUILD_TARGET_WINDOWS) {
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -target x86_64-windows-gnu ", command_len);
	}
	else if (eb->build_target == BUILDSYS_BUILD_TARGET_LINUX) {
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -target x86_64-linux-gnu ", command_len);
	}
	else if (eb->build_target == BUILDSYS_BUILD_TARGET_WASM) {
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -target  wasm32-wasi ", command_len);
	}
	
	{ // Add defines
		uint64_t defines_count = eb->defines_count;
		for (uint64_t i = 0; i < defines_count; ++i) {
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -D", command_len);
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, eb->defines[i], command_len);
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, " ", command_len);
		}
	}

	if (eb->build_mode == BUILDSYS_BUILD_MODE_DEBUG) {
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -g ", command_len);
	}
	else if (eb->build_mode == BUILDSYS_BUILD_MODE_RELEASE_FAST) {
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -O2 ", command_len);
	}
	else if (eb->build_mode == BUILDSYS_BUILD_MODE_RELEASE_SMALL) {
		command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -Os ", command_len);
	}

	{ // Add link libraries
		uint64_t link_libraries_count = eb->link_libraries_count;
		for (uint64_t i = 0; i < link_libraries_count; ++i) {
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, " -l", command_len);
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, eb->link_libraries[i], command_len);
			command_len = buildsys__Build_exec_cat_command(build_command_buffer, " ", command_len);
		}
	}

	return buildsys_Run_command(build_command_buffer);
}


void
buildsys_Create_directory(const char *directory) {
#ifdef WIN32
	_mkdir(directory);
#else
	mkdir(directory, 0700);
#endif
}


bool
buildsys_Copy_file(const char *src, const char *dst) {
	static char file_mem_block[1024*1024];
	FILE *src_file = fopen(src, "rb");
	if (src_file == NULL) {
		return false;
	}

	FILE *dst_file = fopen(dst, "wb");
	if (dst_file == NULL) {
		fclose(src_file);
		return false;
	}

	while(true) {
		size_t n_elems = fread(file_mem_block, 1, sizeof(file_mem_block), src_file);
		if (n_elems == 0) break;
		fwrite(file_mem_block, 1, n_elems, dst_file);
	}

	fclose(dst_file);
	fclose(src_file);

	return true;
}


#endif // BUILDYS_ONLY_HEADER

#endif // BUILDSYS_H

