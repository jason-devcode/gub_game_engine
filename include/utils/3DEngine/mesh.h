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
 * @brief Sets the name of a given 3D mesh.
 *
 * This function assigns a new name to the provided `Mesh3D` structure.
 * If the `mesh` pointer is `NULL`, the function will return immediately without performing any operation.
 *
 * @param mesh A pointer to the `Mesh3D` structure for which the name is to be set.
 * @param name A constant character pointer to the new name string to be assigned to the mesh.
 *
 * @note The `name` string is copied into the mesh's `name` field using `strcpy`.
 * Ensure that the `name` field in `Mesh3D` has enough space to accommodate the new name.
 */
static inline void setMeshName(Mesh3D *mesh, const char *name)
{
    if (mesh == NULL)
        return;
    strcpy(mesh->name, name);
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
 * @brief Merges an array of mesh groups into a single mesh group.
 *
 * This function takes an array of pointers to `MeshGroup` structures and combines them into a single `MeshGroup`.
 * The indices of vertices, normals, and textures are adjusted accordingly.
 *
 * @param groups The array of pointers to mesh groups to be merged.
 * @param groupCount The number of mesh groups in the array.
 * @return Pointer to the merged `MeshGroup`. The caller is responsible for freeing this memory.
 */
MeshGroup *mergeMeshGroups(MeshGroup **groups, int groupCount)
{
    if (!groups || groupCount <= 0)
    {
        fprintf(stderr, "Invalid input for merging mesh groups.\n");
        return NULL;
    }

    MeshGroup *mergedGroup = createEmptyMeshGroup();

    // Calculate total counts
    int totalVertexCount = 0;
    int totalNormalCount = 0;
    int totalTextureCount = 0;
    int totalMeshCount = 0;

    for (int i = 0; i < groupCount; ++i)
    {
        if (groups[i])
        {
            totalVertexCount += groups[i]->vertexCount;
            totalNormalCount += groups[i]->normalsCount;
            totalTextureCount += groups[i]->vertexTextureCount;
            totalMeshCount += groups[i]->meshCount;
        }
    }

    // Allocate memory for the merged group
    mergedGroup->vertices = (Vec3f *)malloc(totalVertexCount * sizeof(Vec3f));
    mergedGroup->normals = (Vec3f *)malloc(totalNormalCount * sizeof(Vec3f));
    mergedGroup->vertices_texture = (Vec2f *)malloc(totalTextureCount * sizeof(Vec2f));
    mergedGroup->meshes = (Mesh3D *)malloc(totalMeshCount * sizeof(Mesh3D));

    if (!mergedGroup->vertices || !mergedGroup->normals || !mergedGroup->vertices_texture || !mergedGroup->meshes)
    {
        fprintf(stderr, "Error allocating memory for merged mesh group.\n");
        releaseMeshGroupResources(mergedGroup);
        return NULL;
    }

    // Copy data and adjust indices
    int vertexOffset = 0;
    int normalOffset = 0;
    int textureOffset = 0;
    int meshOffset = 0;

    for (int i = 0; i < groupCount; ++i)
    {
        MeshGroup *group = groups[i];
        if (!group)
            continue;

        // Copy vertices, normals, and textures
        memcpy(mergedGroup->vertices + vertexOffset, group->vertices, group->vertexCount * sizeof(Vec3f));
        memcpy(mergedGroup->normals + normalOffset, group->normals, group->normalsCount * sizeof(Vec3f));
        memcpy(mergedGroup->vertices_texture + textureOffset, group->vertices_texture, group->vertexTextureCount * sizeof(Vec2f));

        // Copy and adjust meshes
        for (int j = 0; j < group->meshCount; ++j)
        {
            Mesh3D *sourceMesh = &group->meshes[j];
            Mesh3D *targetMesh = &mergedGroup->meshes[meshOffset + j];

            *targetMesh = *sourceMesh;
            targetMesh->facesIndices = (FaceIndices *)malloc(sourceMesh->facesCount * sizeof(FaceIndices));

            if (!targetMesh->facesIndices)
            {
                fprintf(stderr, "Error allocating memory for facesIndices in merged mesh group.\n");
                releaseMeshGroupResources(mergedGroup);
                return NULL;
            }

            memcpy(targetMesh->facesIndices, sourceMesh->facesIndices, sourceMesh->facesCount * sizeof(FaceIndices));

            // Adjust indices
            for (int k = 0; k < sourceMesh->facesCount; ++k)
            {
                targetMesh->facesIndices[k].vertexA += vertexOffset;
                targetMesh->facesIndices[k].vertexB += vertexOffset;
                targetMesh->facesIndices[k].vertexC += vertexOffset;

                targetMesh->facesIndices[k].vertexNormalA += normalOffset;
                targetMesh->facesIndices[k].vertexNormalB += normalOffset;
                targetMesh->facesIndices[k].vertexNormalC += normalOffset;

                targetMesh->facesIndices[k].vertexTextureA += textureOffset;
                targetMesh->facesIndices[k].vertexTextureB += textureOffset;
                targetMesh->facesIndices[k].vertexTextureC += textureOffset;
            }
        }

        vertexOffset += group->vertexCount;
        normalOffset += group->normalsCount;
        textureOffset += group->vertexTextureCount;
        meshOffset += group->meshCount;
    }

    mergedGroup->vertexCount = totalVertexCount;
    mergedGroup->normalsCount = totalNormalCount;
    mergedGroup->vertexTextureCount = totalTextureCount;
    mergedGroup->meshCount = totalMeshCount;

    return mergedGroup;
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
