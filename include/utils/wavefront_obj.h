#ifndef WAVEFRONT_OBJ_UTILS_H
#define WAVEFRONT_OBJ_UTILS_H

/**
 * @file wavefront_obj_utils.h
 * @brief Utility functions and macros for parsing and handling Wavefront OBJ files.
 */

#include "3DEngine/mesh.h"
#include "3DEngine/material.h"
#include "3DEngine/vectorial_3D.h"

#include "3DEngine/linear_lists/vertex_linear_list.h"
#include "3DEngine/linear_lists/vertex_texture_linear_list.h"
#include "3DEngine/linear_lists/vertex_normal_list.h"
#include "3DEngine/linear_lists/mesh_linear_list.h"
#include "3DEngine/linear_lists/face_linear_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_BUFFER_LINE 1024

/**
 * @brief Packs two characters into a single integer.
 *
 * @param a The first character.
 * @param b The second character.
 * @return The packed integer.
 */
#define packTwoChars(a, b) (((int)(b) << 8) | (int)(a))

/* Key definitions for identifying line types in the OBJ file */
#define KEY_READ_MTLLIB_LINE packTwoChars('m', 't')         /**< Key for 'mtllib' line. */
#define KEY_READ_OBJECT_LINE packTwoChars('o', ' ')         /**< Key for 'object' line. */
#define KEY_READ_VERTEX_LINE packTwoChars('v', ' ')         /**< Key for 'vertex' line. */
#define KEY_READ_VERTEX_TEXTURE_LINE packTwoChars('v', 't') /**< Key for 'vertex texture' line. */
#define KEY_READ_VERTEX_NORMAL_LINE packTwoChars('v', 'n')  /**< Key for 'vertex normal' line. */
#define KEY_READ_FACE_LINE packTwoChars('f', ' ')           /**< Key for 'face' line. */
#define KEY_READ_SMOOTHMODE_LINE packTwoChars('s', ' ')     /**< Key for 'smoothmode' line (ignored). */
#define KEY_READ_USE_MTL_LINE packTwoChars('u', 's')        /**< Key for 'usemtl' line. */

/**
 * @brief Parses a vertex line from the OBJ file.
 *
 * @param vertices The list to store parsed vertices.
 * @param line The line containing the vertex data.
 */
void parseVertexLine(VertexLinearList *vertices, char *line)
{
    Vec3f vertex = {0, 0, 0};
    sscanf(line, "v %lf %lf %lf", &vertex.x, &vertex.y, &vertex.z);
    addVertex(vertices, vertex);
}

/**
 * @brief Parses a vertex texture line from the OBJ file.
 *
 * @param verticesTexture The list to store parsed texture vertices.
 * @param line The line containing the texture vertex data.
 */
void parseVertexTextureLine(VertexTextureLinearList *verticesTexture, char *line)
{
    Vec2f vertexTexture = {0, 0};
    sscanf(line, "vt %lf %lf", &vertexTexture.x, &vertexTexture.y); // read UV
    addVertexTexture(verticesTexture, vertexTexture);
}

/**
 * @brief Parses a vertex normal line from the OBJ file.
 *
 * @param normals The list to store parsed normals.
 * @param line The line containing the normal data.
 */
void parseVertexNormalLine(VertexNormalLinearList *normals, char *line)
{
    Vec3f normal = {0, 0, 0};
    sscanf(line, "vn %lf %lf %lf", &normal.x, &normal.y, &normal.z);
    addVertexNormal(normals, normal);
}

/**
 * @brief Parses an object line from the OBJ file.
 *
 * @param currentMesh The mesh to assign the object name.
 * @param line The line containing the object name.
 */
void parseObjectLine(Mesh3D *currentMesh, char *line)
{
    sscanf(line, "o %s", currentMesh->name);
}

/**
 * @brief Adds a face to the face list.
 *
 * @param faces The list to store parsed faces.
 * @param v1 First vertex index.
 * @param vt1 First texture vertex index.
 * @param vn1 First normal vertex index.
 * @param v2 Second vertex index.
 * @param vt2 Second texture vertex index.
 * @param vn2 Second normal vertex index.
 * @param v3 Third vertex index.
 * @param vt3 Third texture vertex index.
 * @param vn3 Third normal vertex index.
 * @param materialIndex The material index used for this face.
 */
void addFaceToList(FaceLinearList *faces, int v1, int vt1, int vn1, int v2, int vt2, int vn2, int v3, int vt3, int vn3, int materialIndex)
{
    FaceIndices face = {v1, vn1, vt1, v2, vn2, vt2, v3, vn3, vt3, materialIndex};
    addFace(faces, face);
}

/**
 * @brief Parses a face line from the OBJ file.
 *
 * @param faces The list to store parsed faces.
 * @param line The line containing the face data.
 */
void parseFaceLine(FaceLinearList *faces, char *line)
{
    // Temporary variables for parsing
    int v[10], vt[10], vn[10];
    int numVertices = 0;

    // Initialize arrays to -1 (indicating no texture or normal)
    memset(v, -1, sizeof(v));
    memset(vt, -1, sizeof(vt));
    memset(vn, -1, sizeof(vn));

    // Read face data
    char *token = strtok(line, " ");
    if (!token || strcmp(token, "f") != 0)
        return; // Not a face line

    while ((token = strtok(NULL, " ")) != NULL)
    {
        int vi = 0, vti = 0, vni = 0;
        if (sscanf(token, "%d/%d/%d", &vi, &vti, &vni) == 3)
        {
        }
        else if (sscanf(token, "%d/%d", &vi, &vti) == 2)
        {
        }
        else if (sscanf(token, "%d//%d", &vi, &vni) == 2)
        {
        }
        else if (sscanf(token, "%d", &vi) == 1)
        {
        }

        v[numVertices] = vi - 1;
        vt[numVertices] = vti - 1;
        vn[numVertices] = vni - 1;
        numVertices++;
    }

    addFaceToList(faces, v[0], vt[0], vn[0], v[1], vt[1], vn[1], v[1 + 1], vt[1 + 1], vn[1 + 1], -1);

    // Triangulate face if more than 3 vertices
    // if (numVertices >= 3)
    // {
    // for (int i = 1; i < numVertices - 1; ++i)
    // {
    // Create a triangle from vertices 0, i, and i+1
    // addFaceToList(faces, v[0], vt[0], vn[0], v[i], vt[i], vn[i], v[i + 1], vt[i + 1], vn[i + 1], -1);
    // }
    // }
}

/**
 * @brief Updates and resets the current mesh, adding it to the mesh list.
 *
 * @param currentMesh The current mesh being processed.
 * @param meshes The list of meshes.
 * @param faces The list of faces to be associated with the current mesh.
 */
#define UPDATE_AND_RESET_MESH(currentMesh, meshes, faces)                \
    do                                                                   \
    {                                                                    \
        if ((currentMesh) != NULL && (faces)->countFaces > 0)            \
        {                                                                \
            (currentMesh)->facesIndices = convertFaceListToArray(faces); \
            (currentMesh)->facesCount = (faces)->countFaces;             \
            addMesh((meshes), *(currentMesh));                           \
                                                                         \
            freeFaceLinearList(faces);                                   \
            free(currentMesh);                                           \
            (currentMesh) = NULL;                                        \
        }                                                                \
    } while (0)

/**
 * @brief Reads a Wavefront OBJ file and parses its contents into a MeshGroup.
 *
 * @param filename The path to the OBJ file.
 * @return A pointer to a MeshGroup containing the parsed data, or NULL on failure.
 */
static inline MeshGroup *readWavefrontObj(const char *filename)
{
    if (filename == NULL)
        return NULL;

    FILE *objFile = fopen(filename, "r");

    if (objFile == NULL)
        return NULL;

    VertexLinearList *vertices = createVertexLinearList();
    VertexTextureLinearList *verticesTexture = createVertexTextureLinearList();
    VertexNormalLinearList *normals = createVertexNormalLinearList();
    FaceLinearList *faces = createFaceLinearList();
    MeshLinearList *meshes = createMeshLinearList();

    Mesh3D *currentMesh = createMesh(); // Create mesh by default if there is not o in file

    MeshGroup *meshGroup = createEmptyMeshGroup();

    char currentFileLine[MAX_BUFFER_LINE] = {0};

    while (fgets(currentFileLine, MAX_BUFFER_LINE, objFile) != NULL)
    {
        uint16_t lineKeyValue = *(uint16_t *)currentFileLine;

        switch (lineKeyValue)
        {
        case KEY_READ_VERTEX_LINE:
            parseVertexLine(vertices, currentFileLine);
            break;
        case KEY_READ_VERTEX_TEXTURE_LINE:
            parseVertexTextureLine(verticesTexture, currentFileLine);
            break;
        case KEY_READ_VERTEX_NORMAL_LINE:
            parseVertexNormalLine(normals, currentFileLine);
            break;
        case KEY_READ_FACE_LINE:
            parseFaceLine(faces, currentFileLine);
            break;
        case KEY_READ_OBJECT_LINE:
            UPDATE_AND_RESET_MESH(currentMesh, meshes, faces);

            faces = createFaceLinearList();
            currentMesh = createMesh();
            parseObjectLine(currentMesh, currentFileLine);
            break;
        default:
            break;
        }
    }
    UPDATE_AND_RESET_MESH(currentMesh, meshes, faces);

    meshGroup->meshes = convertMeshListToArray(meshes);
    meshGroup->meshCount = meshes->countMeshes;

    meshGroup->vertices = convertVertexListToArray(vertices);
    meshGroup->vertexCount = vertices->countVertices;

    meshGroup->vertices_texture = convertTextureListToArray(verticesTexture);
    meshGroup->vertexTextureCount = verticesTexture->countTextures;

    meshGroup->normals = convertNormalListToArray(normals);
    meshGroup->normalsCount = normals->countNormals;

    freeVertexLinearList(vertices);
    freeVertexNormalLinearList(normals);
    freeVertexTextureLinearList(verticesTexture);
    freeMeshLinearList(meshes, false);

    fclose(objFile);
    objFile = NULL;

    return meshGroup;
}

#endif