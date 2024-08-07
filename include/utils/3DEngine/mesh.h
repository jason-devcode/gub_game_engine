#ifndef MESH_DATA_H
#define MESH_DATA_H

#include "vectorial_3D.h"

#define MAX_LENGHT_MESH_NAME 32

typedef struct _tag_face_indices_
{
    int vertexA, vertexNormalA, vertexTextureA;
    int vertexB, vertexNormalB, vertexTextureB;
    int vertexC, vertexNormalC, vertexTextureC;
    int materialIndex;
} FaceIndices;

typedef struct _tag_3d_mesh_data_structure_
{
    char name[MAX_LENGHT_MESH_NAME];
    Vec3f *vertices;
    Vec3f *vertices_normals;
    Vec3f *vertices_texture;
    FaceIndices *facesIndices; // v/vn/vt

    int verticesCount;
} Mesh3D;

#endif