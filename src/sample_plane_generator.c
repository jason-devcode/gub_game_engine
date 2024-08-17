#include "../include/gub.h"
#include "../include/utils/wavefront_obj.h"
#include "../include/utils/geometry.h"
#include "../include/utils/triangles/clipping_triangle_depth_test.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/3DEngine/camera3D.h"

#include "../include/utils/3DEngine/geometry/plane.h"

#include "../include/utils/keyboard.h"

void onMoveForwardCamera()
{
    moveCameraForward();
}

void onMoveBackwardCamera()
{
    moveCameraBackward();
}

void onRotateCameraLeft()
{
    rotateCameraYaw(-radian);
}

void onRotateCameraRight()
{
    rotateCameraYaw(radian);
}

void onRotateCameraUp()
{
    rotateCameraPitch(radian);
}

void onRotateCameraBottom()
{
    rotateCameraPitch(-radian);
}

int gameLoop(void *ignore)
{
    // initializeCamera3D((Vec3f){7.270224, 0.524233, -6.514976}, (Vec3f){0.044998, 4.972324, 0.0}, 60);
    initializeCamera3D((Vec3f){0, 0.0, -3}, (Vec3f){0, 0, 0}, 60);

#define CUBE_PLANES 6
#define RESOLUTION 20

    MeshGroup *cubeMeshes[CUBE_PLANES] = {
        generatePlane3D(RESOLUTION, RESOLUTION, PLANE_LEFT),
        generatePlane3D(RESOLUTION, RESOLUTION, PLANE_BACK),
        generatePlane3D(RESOLUTION, RESOLUTION, PLANE_RIGHT),
        generatePlane3D(RESOLUTION, RESOLUTION, PLANE_FRONT),
        generatePlane3D(RESOLUTION, RESOLUTION, PLANE_TOP),
        generatePlane3D(RESOLUTION, RESOLUTION, PLANE_BOTTOM),
    };

    MeshGroup *meshGroup = mergeMeshGroups(cubeMeshes, CUBE_PLANES);

    for (int i = 0; i < CUBE_PLANES; ++i)
        releaseMeshGroupResources(cubeMeshes[i]);

    setClearScreenColor(CYAN_500);

    addKeyPressEventListener(GUB_KEY_w, onMoveForwardCamera);
    addKeyPressEventListener(GUB_KEY_s, onMoveBackwardCamera);
    addKeyPressEventListener(GUB_KEY_a, onRotateCameraLeft);
    addKeyPressEventListener(GUB_KEY_d, onRotateCameraRight);
    addKeyPressEventListener(GUB_KEY_j, onRotateCameraUp);
    addKeyPressEventListener(GUB_KEY_k, onRotateCameraBottom);

    Vec3f *tempVertices = (Vec3f *)malloc(meshGroup->vertexCount * sizeof(Vec3f));

    uint32_t *colorMeshes = (uint32_t *)malloc(meshGroup->meshCount * sizeof(uint32_t));

    for (int colorIndex = 0; colorIndex < meshGroup->meshCount; ++colorIndex)
        colorMeshes[colorIndex] = colorTailwindPalette(colorIndex + 5, 4);

    // vamos a esfericar esa malla

    for (int vertexIndex = 0; vertexIndex < meshGroup->vertexCount; ++vertexIndex)
    {
        meshGroup->vertices[vertexIndex] = vec3f_normalize(meshGroup->vertices[vertexIndex]);
    }

    do
    {
        clearScreenDepth();

        int trianglesCount = 0;

        for (int vertexIndex = 0; vertexIndex < meshGroup->vertexCount; ++vertexIndex)
        {
            tempVertices[vertexIndex] = vec3f_scalar(meshGroup->vertices[vertexIndex], 1.0);
            tempVertices[vertexIndex] = vec3f_subtract(tempVertices[vertexIndex], cameraPosition);
            tempVertices[vertexIndex] = vec3f_rotate_yx(tempVertices[vertexIndex], cameraYaw, -cameraPitch);
        }

        for (int meshIndex = 0; meshIndex < meshGroup->meshCount; ++meshIndex)
        {
            Mesh3D *meshToRender = &meshGroup->meshes[meshIndex];
            uint32_t colorMesh = colorMeshes[meshIndex];

            trianglesCount += meshToRender->facesCount;
            for (int faceIndex = 0; faceIndex < meshToRender->facesCount; ++faceIndex)
            {
                register FaceIndices *face = &meshToRender->facesIndices[faceIndex];
                int vertexAIndex = face->vertexA;
                int vertexBIndex = face->vertexB;
                int vertexCIndex = face->vertexC;

                Vec3f *vertexA = &tempVertices[vertexAIndex];
                Vec3f *vertexB = &tempVertices[vertexBIndex];
                Vec3f *vertexC = &tempVertices[vertexCIndex];

                drawTriangleScreenClippingDepthTest(
                    vertexA->x, vertexA->y, vertexA->z,
                    vertexB->x, vertexB->y, vertexB->z,
                    vertexC->x, vertexC->y, vertexC->z,
                    colorMesh);
            }
        }

        drawFormattedText(10, 10, YELLOW, "FPS: %d\nCamera position - X: %lf Y: %lf Z: %lf\nCamera angle - X: %lf Y: %lf Z: %lf\nTotal triangules: %d", getFps(), cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraPitch, cameraYaw, cameraRoll, trianglesCount);

        drawScreen();
        renderDelay(16);
    } while (isGameRunning);

    free(tempVertices);
    releaseMeshGroupResources(meshGroup);

    return EXIT_SUCCESS;
}

CREATE_GAME(640, 640, "SAMPLE RENDER MESH 3D")