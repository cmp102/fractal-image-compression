
#ifndef BUNDLE_TREE_H


#include <stdio.h>
#include <stdbool.h>



void
btree_Bundle_tree_to_open_file(FILE *out_file, const char *dirname);


bool
btree_Bundle_tree(const char *out_filename, const char *dirname);






#ifndef BUNDLE_TREE_ONLY_HEADER




#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>	

#ifndef BTREE_MAX_FILES
#define BTREE_MAX_FILES 2000
#endif

static const char *btree__filenames[BTREE_MAX_FILES];
static char       *btree__varnames[BTREE_MAX_FILES];
static size_t      btree__file_sizes[BTREE_MAX_FILES];
static int         btree__filenames_count = 0;

// 
// Takes 2 strings and merges them putting a '/' on the middle
// The result is heap allocated
//
static char *
btree__Merge_paths(const char *path_l, const char *path_r) {
	size_t final_len = strlen(path_l) + strlen(path_r) + 1;
	char * result = malloc(final_len+1); // +1 because has to be null terminated
	if (result == NULL) {
		fprintf(stderr, "Out of memory.\n");
		exit(-1);
	}
	sprintf(result, "%s/%s", path_l, path_r);
	return result;
}


//
// Checks if a char matches with any of the chars on a passed null terminated array
//
static bool
btree__Char_match(char c, char *matches) {
	for (int i = 0; matches[i] != 0; ++i) {
		if (c == matches[i]) { return true; }
	}
	return false;
}

// 
// Converts the filename to a valid variable name removing the invalid chars by _
// Example assets/player.png assets_player_png
//
static char *
btree__Filename_to_var(const char *filename) {
	char * result = malloc(strlen(filename)+1); // +1 because has to be null terminated
	if (result == NULL) {
		fprintf(stderr, "Out of memory.\n");
		exit(-1);
	}
	strcpy(result, filename);
	for (int i = 0; result[i] != 0; ++i) {
		if (!btree__Char_match(result[i], "0987654321qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_")) {
			result[i] = '_';
		}
	}
	return result;
}



//
// Adds a filename to the global filenames storage
//
static void
btree__Add_filename(const char *filename) {
	if (btree__filenames_count == BTREE_MAX_FILES) {
		fprintf(stderr, "Error!!!, Maximum number of files reached (%d).\n", BTREE_MAX_FILES);
		exit(-1);
	}
	btree__filenames[btree__filenames_count] = filename;
	++btree__filenames_count;
}


//
// Walks recursively over directories and saves the last files
//
static void
btree__Walk_tree(const char *dirname) {
	// opendir() returns a pointer of DIR type. 
	DIR *dir = opendir(dirname);
	if (dir == NULL) { // opendir returns NULL if couldn't open directory
		btree__Add_filename(dirname);
	    return;
	}

	struct dirent *sub_dir = NULL;
	for (sub_dir = readdir(dir); sub_dir != NULL; sub_dir = readdir(dir)) {
		if (strcmp(".",  sub_dir->d_name) == 0) { continue; }
		if (strcmp("..", sub_dir->d_name) == 0) { continue; }
		char *full_dir = btree__Merge_paths(dirname, sub_dir->d_name);
		btree__Walk_tree(full_dir);
	}
	closedir(dir);
}

//
// Allocates all file contents on the heap putting a 0 on the end
// Return a pointer to the data and sets the parameter size to the
// real size without counting the appended 0.
// If something fails will return a NULL
//
static unsigned char *
btree__Get_file_contentsz(const char *filename, size_t *size) {
	assert(size != NULL);
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		return NULL;
	}
	fseek(f, 0L, SEEK_END);	
	size_t file_size = ftell(f);
	fseek(f, 0L, SEEK_SET);	
	unsigned char *data = malloc(file_size + 1);
	if (data == NULL) {
		fclose(f);
		fprintf(stderr, "Out of memory.\n");
		exit(-1);
		return NULL;
	}
	fread(data, 1, file_size, f);
	fclose(f);

	data[file_size] = '\0';
	*size = file_size;
	return data;
}

// Saves the valid variable names based on the filenames
static void
btree__Set_varnames() {
	for (int i = 0; i < btree__filenames_count; ++i) {
		btree__varnames[i] = btree__Filename_to_var(btree__filenames[i]);
	}
}


static void
btree__Print_filenames(FILE *out_file) {
	fprintf(out_file, "const char * const bundle_filenames[] = {\n");
	for (int i = 0; i < btree__filenames_count; ++i) {
		fprintf(out_file, "    \"%s\"", btree__filenames[i]);
		if (i < btree__filenames_count-1) {
			fprintf(out_file,",");
		}
		fprintf(out_file,"\n");
	}
	fprintf(out_file,"};\n\n");
}

static void
btree__Print_file_buffers(FILE *out_file) {
	for (int i = 0; i < btree__filenames_count; ++i) {
		size_t file_size;
		unsigned char *file_data = btree__Get_file_contentsz(btree__filenames[i], &file_size);
		if (file_data == NULL) {
			fprintf(stderr, "Cannot load file %s\n", btree__filenames[i]);
			exit(-1);
		}
		btree__file_sizes[i] = file_size; // Stores the filesize to print the array of filesizes later
		fprintf(out_file, "// %s\n", btree__filenames[i]);
		fprintf(out_file, "static char %s[%lu] = {\n", btree__varnames[i], file_size + 1);

		//i <= file_size because is warrantied that is null terminated
		for (int i = 0; i <= file_size;) {
			const int MAX_BYTES_PER_LINE = 20;
			fprintf(out_file, "    ");
			// We print a limited number of bytes per line to improve readability
			for (int j = 0; j < MAX_BYTES_PER_LINE && i <= file_size; ++i, ++j) {
				fprintf(out_file, "0x%02x", file_data[i]);
				if (i < file_size) {
					fprintf(out_file, ", ");
				}
			}
			fprintf(out_file, "\n");
		}

		fprintf(out_file, "};\n");
		
		free(file_data);
	}
}

static void
btree__Print_files_index(FILE *out_file) {
	fprintf(out_file, "char * const bundle_files_index[] = {\n");
	for (int i = 0; i < btree__filenames_count; ++i) {
		fprintf(out_file, "    %s", btree__varnames[i]);
		if (i < btree__filenames_count-1) {
			fprintf(out_file,",");
		}
		fprintf(out_file,"\n");
	}
	fprintf(out_file,"};\n\n");
}


static void
btree__Print_file_sizes(FILE *out_file) {
	fprintf(out_file, "const unsigned int bundle_file_sizes[] = {\n");
	for (int i = 0; i < btree__filenames_count; ++i) {
		fprintf(out_file, "    %lu", btree__file_sizes[i]);
		if (i < btree__filenames_count-1) {
			fprintf(out_file,",");
		}
		fprintf(out_file,"\n");
	}
	fprintf(out_file,"};\n\n");
}

void
btree_Bundle_tree_to_open_file(FILE *out_file, const char *dirname) {
	btree__Walk_tree(dirname);
	btree__Set_varnames();
	
	fprintf(out_file, "//////////////////////////////////////////////////////////////\n");
	fprintf(out_file, "//\n");
	fprintf(out_file, "// FILE GENERATED BY: %s %s\n", __FILE__, dirname);
	fprintf(out_file, "//\n");
	fprintf(out_file, "//////////////////////////////////////////////////////////////\n\n\n\n");
	fprintf(out_file, "const unsigned int BUNDLE_FILES_COUNT = %d;\n\n", btree__filenames_count);
	btree__Print_filenames(out_file);
	btree__Print_file_buffers(out_file);
	btree__Print_files_index(out_file);
	btree__Print_file_sizes(out_file);
}


bool
btree_Bundle_tree(const char *out_filename, const char *dirname) {
	FILE *out_file = fopen(out_filename, "w");
	if (out_file == NULL) return false;
	btree_Bundle_tree_to_open_file(out_file, dirname);
	fclose(out_file);
	return true;
}

#ifdef BTREE_BUNDLE_TREE_AS_PROGRAM

int
main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "USAGE: %s 'directory'\n", argv[0]);
		return -1;
	}
	
	btree_Bundle_tree_to_open_file(stdout, argv[1]);

	return 0;
}

#endif

#endif // BUNDLE_TREE_ONLY_HEADER

#endif // BUNDLE_TREE_H

