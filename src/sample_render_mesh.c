#include "../include/gub.h"
#include "../include/utils/wavefront_obj.h"
#include "../include/utils/geometry.h"
// #include "../include/utils/triangles/simple_clipping_triangle.h"
#include "../include/utils/triangles/clipping_triangle_depth_test.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/color_palette.h"
#include "../include/utils/timers.h"
#include "../include/utils/3DEngine/camera3D.h"

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
    initializeCamera3D((Vec3f){7.270224, 0.524233, -6.514976}, (Vec3f){0.044998, 4.972324, 0.0}, 60);

    MeshGroup *meshGroup = readWavefrontObj("./temp/Bob-omb Battlefield/Bob-omb Battlefield.obj");
    // MeshGroup *meshGroup = readWavefrontObj("./temp/skull/skull.obj");
    setClearScreenColor(CYAN_500);

    addKeyPressEventListener(SDLK_w, onMoveForwardCamera);
    addKeyPressEventListener(SDLK_s, onMoveBackwardCamera);
    addKeyPressEventListener(SDLK_a, onRotateCameraLeft);
    addKeyPressEventListener(SDLK_d, onRotateCameraRight);
    addKeyPressEventListener(SDLK_UP, onRotateCameraUp);
    addKeyPressEventListener(SDLK_DOWN, onRotateCameraBottom);

    Vec3f *tempVertices = (Vec3f *)malloc(meshGroup->vertexCount * sizeof(Vec3f));

    uint32_t *colorMeshes = (uint32_t *)malloc(meshGroup->meshCount * sizeof(uint32_t));

    for (int colorIndex = 0; colorIndex < meshGroup->meshCount; ++colorIndex)
        colorMeshes[colorIndex] = colorTailwindPalette(colorIndex + 5, 4);

    do
    {
        clearScreenDepth();

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
        drawFormattedText(10, 10, YELLOW, "Camera position - X: %lf Y: %lf Z: %lf\nCamera angle - X: %lf Y: %lf Z: %lf", cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraPitch, cameraYaw, cameraRoll);

        drawScreen();
        renderDelay(16);
    } while (isGameRunning);

    free(tempVertices);
    releaseMeshGroupResources(meshGroup);
}

CREATE_GAME(1280, 640, "SAMPLE RENDER MESH 3D")