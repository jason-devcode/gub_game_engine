#ifndef MESH_DATA_H
#define MESH_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strcpy

#include "../vectorial_2D.h"
#include "vectorial_3D.h"

#define MAX_LENGTH_MESH_NAME 128

typedef struct _tag_face_indices_
{
    int vertexA, vertexTextureA, vertexNormalA;
    int vertexB, vertexTextureB, vertexNormalB;
    int vertexC, vertexTextureC, vertexNormalC;
    int materialIndex;
} FaceIndices;

typedef struct _tag_3d_mesh_data_structure_
{
    char name[MAX_LENGTH_MESH_NAME];
    FaceIndices *facesIndices; // v/vt/vn v/vt/vn v/vt/vn format
    int facesCount;
} Mesh3D;

typedef struct _tag_3d_mesh_group_
{
    Vec3f *vertices;
    Vec3f *normals;
    Vec2f *vertices_texture;

    Mesh3D *meshes; // Array of meshes

    int vertexCount;
    int vertexTextureCount;
    int normalsCount;
    int meshCount; // Number of meshes
} MeshGroup;

/**
 * @brief Creates a new Mesh3D structure.
 *
 * Allocates memory for a new `Mesh3D` and initializes its fields to NULL or default values.
 *
 * @return Pointer to the newly created Mesh3D structure.
 */
static inline Mesh3D *createMesh()
{
    Mesh3D *mesh = (Mesh3D *)malloc(sizeof(Mesh3D));
    if (!mesh)
    {
        fprintf(stderr, "Error allocating memory for Mesh3D\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the Mesh3D fields to default values
    strcpy(mesh->name, "default");
    mesh->facesIndices = NULL;
    mesh->facesCount = 0;

    return mesh;
}

/**
 * @brief Releases resources of a Mesh3D structure.
 *
 * Frees the memory allocated for facesIndices.
 *
 * @param mesh Reference to the Mesh3D structure whose resources need to be released.
 */
static inline void releaseMesh3DResources(Mesh3D *mesh)
{
    if (!mesh)
        return;

    // Free the allocated memory for facesIndices
    if (mesh->facesIndices)
        free(mesh->facesIndices);

    // Set pointers to NULL after freeing
    mesh->facesIndices = NULL;
}

/**
 * @brief Prints the details of a Mesh3D structure.
 *
 * Displays the mesh name, face indices, and related information.
 *
 * @param mesh Pointer to the Mesh3D structure to be printed.
 */
static inline void printMeshData(const Mesh3D *mesh)
{
    if (!mesh)
    {
        fprintf(stderr, "Mesh is NULL.\n");
        return;
    }

    printf("Mesh Name: %s\n", mesh->name);
    printf("Face Count: %d\n", mesh->facesCount);

    if (mesh->facesIndices)
    {
        printf("Faces:\n");
        for (int i = 0; i < mesh->facesCount; ++i)
        {
            printf("  Face %d: Vertices(%d, %d, %d) Normals(%d, %d, %d) Textures(%d, %d, %d) Material(%d)\n",
                   i,
                   mesh->facesIndices[i].vertexA, mesh->facesIndices[i].vertexB, mesh->facesIndices[i].vertexC,
                   mesh->facesIndices[i].vertexNormalA, mesh->facesIndices[i].vertexNormalB, mesh->facesIndices[i].vertexNormalC,
                   mesh->facesIndices[i].vertexTextureA, mesh->facesIndices[i].vertexTextureB, mesh->facesIndices[i].vertexTextureC,
                   mesh->facesIndices[i].materialIndex);
        }
    }
}

/**
 * @brief Creates a new MeshGroup structure.
 *
 * Allocates memory for a new `MeshGroup` and initializes its fields to NULL or default values.
 *
 * @return Pointer to the newly created MeshGroup structure.
 */
static inline MeshGroup *createEmptyMeshGroup()
{
    MeshGroup *group = (MeshGroup *)malloc(sizeof(MeshGroup));
    if (!group)
    {
        fprintf(stderr, "Error allocating memory for MeshGroup\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the MeshGroup fields to default values
    group->vertices = NULL;
    group->normals = NULL;
    group->vertices_texture = NULL;
    group->meshes = NULL;
    group->vertexCount = 0;
    group->vertexTextureCount = 0;
    group->normalsCount = 0;
    group->meshCount = 0;

    return group;
}

/**
 * @brief Releases resources of a MeshGroup structure.
 *
 * Frees the memory allocated for vertices, normals, textures, and meshes.
 *
 * @param group Pointer to the MeshGroup structure whose resources need to be released.
 */
static inline void releaseMeshGroupResources(MeshGroup *group)
{
    if (!group)
        return;

    // Free the allocated memory for vertices, normals, textures
    if (group->vertices)
        free(group->vertices);
    if (group->normals)
        free(group->normals);
    if (group->vertices_texture)
        free(group->vertices_texture);

    // Free each mesh within the group
    if (group->meshes)
    {
        for (int i = 0; i < group->meshCount; ++i)
        {
            releaseMesh3DResources(&group->meshes[i]);
        }
        free(group->meshes);
    }

    // Set pointers to NULL after freeing
    group->vertices = NULL;
    group->normals = NULL;
    group->vertices_texture = NULL;
    group->meshes = NULL;
}

/**
 * @brief Prints the details of a MeshGroup structure.
 *
 * Displays the mesh group information, including vertices, normals, texture coordinates, and meshes.
 *
 * @param group Pointer to the MeshGroup structure to be printed.
 */
static inline void printMeshGroupData(const MeshGroup *group)
{
    if (!group)
    {
        fprintf(stderr, "MeshGroup is NULL.\n");
        return;
    }

    printf("Vertex Count: %d\n", group->vertexCount);
    printf("Texture Vertex Count: %d\n", group->vertexTextureCount);
    printf("Normal Count: %d\n", group->normalsCount);
    printf("Mesh Count: %d\n", group->meshCount);

    if (group->vertices)
    {
        printf("Vertices:\n");
        for (int i = 0; i < group->vertexCount; ++i)
        {
            printf("  Vertex %d: (%f, %f, %f)\n", i, group->vertices[i].x, group->vertices[i].y, group->vertices[i].z);
        }
    }

    if (group->vertices_texture)
    {
        printf("Texture Coordinates:\n");
        for (int i = 0; i < group->vertexTextureCount; ++i)
        {
            printf("  Texture %d: (%f, %f)\n", i, group->vertices_texture[i].x, group->vertices_texture[i].y);
        }
    }

    if (group->normals)
    {
        printf("Normals:\n");
        for (int i = 0; i < group->normalsCount; ++i)
        {
            printf("  Normal %d: (%f, %f, %f)\n", i, group->normals[i].x, group->normals[i].y, group->normals[i].z);
        }
    }

    if (group->meshes)
    {
        printf("Meshes:\n");
        for (int i = 0; i < group->meshCount; ++i)
        {
            printMeshData(&group->meshes[i]);
        }
    }
}

#endif
