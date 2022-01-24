#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "base.h"
#include "madmath.h"

typedef struct {
	u32 total_verts;
	Vec2 *vertices;
} BoundingMesh;

void
Remove_newline(char *str) {
    u32 c = 0;
    while(str[c] != '\n') {
        c++;
    }
    str[c] = '\0';
}

/*
* Load_mesh
* =============================================================
*
* DESCRIPTIION
* --------------------------------------------------------------
* Loads a mesh from a file.
*
* VARIABLES
* -------------------------------------------------------------------
* filename: Name of the file to load
*
*/
BoundingMesh
Load_mesh(char *filename) {
    BoundingMesh result = {0};
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        Panic("ERROR: Could not load mesh file");
    }

    char sn[100];
    fgets(sn, 100, file);
    Remove_newline(sn);
    result.total_verts = atoi(sn);
    result.vertices = Alloc(Vec2, result.total_verts);

    f32 *data = (f32*)result.vertices;

    for (u32 i = 0; i < result.total_verts*2; i++) {
        fgets(sn, 100, file);
        Remove_newline(sn);
        f32 n = atof(sn);
        data[i] = n;
    }
    return result;
}


#endif // MESH_LOADER_H

