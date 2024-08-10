#ifndef PLANE_MESH_GENERATOR_H
#define PLANE_MESH_GENERATOR_H

#include "../mesh.h"

/**
 * @enum PlaneOrientations
 * @brief Enum representing the possible orientations of the plane mesh.
 *
 * This enum defines six possible orientations for the plane mesh:
 * - `PLANE_LEFT`: Plane facing left.
 * - `PLANE_BACK`: Plane facing backward.
 * - `PLANE_TOP`: Plane facing upward.
 * - `PLANE_FRONT`: Plane facing forward.
 * - `PLANE_BOTTOM`: Plane facing downward.
 * - `PLANE_RIGHT`: Plane facing right.
 */
enum PlaneOrientations
{
    PLANE_LEFT,
    PLANE_BACK,
    PLANE_TOP,
    PLANE_FRONT,
    PLANE_BOTTOM,
    PLANE_RIGHT
};

/**
 * @brief Generates a 3D mesh for a plane with specified resolution and orientation.
 *
 * This function creates a 3D mesh representing a plane, based on the given horizontal
 * and vertical resolutions. The plane can be oriented in different directions according
 * to the `orientation` parameter, which is one of the values from the `PlaneOrientations` enum.
 *
 * @param horizontalResolution The number of vertices along the horizontal axis. Must be greater than 1.
 * @param verticalResolution The number of vertices along the vertical axis. Must be greater than 1.
 * @param orientation An integer representing the orientation of the plane, based on the `PlaneOrientations` enum.
 * @return A pointer to the generated `MeshGroup` containing the plane mesh data, or `NULL` if the resolution parameters are invalid.
 *
 * @note The `MeshGroup` returned by this function should be freed by the caller to avoid memory leaks.
 */
static inline MeshGroup *generatePlane3D(int horizontalResolution, int verticalResolution, int orientation)
{
    if (horizontalResolution <= 1 || verticalResolution <= 1)
        return NULL;

    MeshGroup *planeMeshData = createEmptyMeshGroup();

    planeMeshData->meshes = createMesh();
    planeMeshData->meshCount = 1;
    setMeshName(planeMeshData->meshes, "plane mesh");

    int totalVertices = horizontalResolution * verticalResolution;

    planeMeshData->vertices = (Vec3f *)malloc(sizeof(Vec3f) * totalVertices);
    planeMeshData->vertexCount = totalVertices;

    Vec3f *vertexIterator = planeMeshData->vertices;

    double invHorizontalResolution = 2 / (double)(horizontalResolution - 1);
    double invVerticalResolution = 2 / (double)(verticalResolution - 1);

    // generate vertices first
    for (int verticalVertexIndex = 0; verticalVertexIndex < verticalResolution; verticalVertexIndex++)
    {
        for (int horizontalVertexIndex = 0; horizontalVertexIndex < verticalResolution; horizontalVertexIndex++)
        {
            double x = -1 + horizontalVertexIndex * invHorizontalResolution;
            double y = 1 + -verticalVertexIndex * invVerticalResolution;

            switch (orientation)
            {
            case PLANE_LEFT:
                vertexIterator->x = -1;
                vertexIterator->y = y;
                vertexIterator->z = x;
                break;
            case PLANE_RIGHT:
                vertexIterator->x = 1;
                vertexIterator->y = y;
                vertexIterator->z = -x;
                break;
            case PLANE_BACK:
                vertexIterator->x = x;
                vertexIterator->y = y;
                vertexIterator->z = 1;
                break;
            case PLANE_FRONT:
                vertexIterator->x = x;
                vertexIterator->y = y;
                vertexIterator->z = -1;
                break;
            case PLANE_TOP:
                vertexIterator->x = x;
                vertexIterator->y = 1;
                vertexIterator->z = y;
                break;
            case PLANE_BOTTOM:
                vertexIterator->x = x;
                vertexIterator->y = -1;
                vertexIterator->z = y;
                break;

            default:
                break;
            }

            ++vertexIterator;
        }
    }

    // generate face indices
    int totalFaces = ((horizontalResolution - 1) << 1) * (verticalResolution - 1);

    planeMeshData->meshes->facesCount = totalFaces;
    planeMeshData->meshes->facesIndices = (FaceIndices *)malloc(sizeof(FaceIndices[totalFaces]));

    FaceIndices *faceIterator = planeMeshData->meshes->facesIndices;

    for (int verticalVertexIndex = 0; verticalVertexIndex < verticalResolution - 1; verticalVertexIndex++)
    {
        for (int horizontalVertexIndex = 0; horizontalVertexIndex < horizontalResolution - 1; horizontalVertexIndex++)
        {
            faceIterator[0].vertexA = horizontalVertexIndex + horizontalResolution * verticalVertexIndex;
            faceIterator[0].vertexB = horizontalVertexIndex + horizontalResolution * verticalVertexIndex + 1;
            faceIterator[0].vertexC = horizontalVertexIndex + horizontalResolution * verticalVertexIndex + horizontalResolution + 1;

            faceIterator[1].vertexA = horizontalVertexIndex + horizontalResolution * verticalVertexIndex;
            faceIterator[1].vertexB = horizontalVertexIndex + horizontalResolution * verticalVertexIndex + horizontalResolution + 1;
            faceIterator[1].vertexC = horizontalVertexIndex + horizontalResolution * verticalVertexIndex + horizontalResolution;

            faceIterator += 2;
        }
    }

    return planeMeshData;
}

#endif