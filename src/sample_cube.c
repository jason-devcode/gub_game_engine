#include "../include/game_engine.h"
#include "../include/utils/geometry.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/math_constants.h"
#include "../include/utils/vectorial_2D.h"
#include "../include/utils/3DEngine/camera3D.h"
#include "../include/utils/3DEngine/vectorial_3D.h"

#define draw_info()                                                                                                                                             \
    drawFormattedText(                                                                                                                                          \
        10, 10, 0xFFFFFF00,                                                                                                                                     \
        "FPS: %d\ndeltatime: %lf\nmouse screen position: ( %d, %d )\n\ncamera direction: ( %0.2lf, %0.2lf, %0.2lf)\ncamera angle: ( %0.2lf, %0.2lf, %0.2lf)\n", \
        getFps(), getDeltatime(),                                                                                                                               \
        GET_MOUSE_X(), GET_MOUSE_Y(), cameraDirection.x, cameraDirection.y, cameraDirection.z, cameraPitch, cameraYaw, cameraRoll)


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

#define MATRIX_SIZE_X 3
#define MATRIX_SIZE_Y 3
#define MATRIX_SIZE_Z 3

int cubeMatrix[MATRIX_SIZE_X][MATRIX_SIZE_Y][MATRIX_SIZE_Z] = {
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    },
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    },
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    }
};


void *gameLoop(void *arg)
{
    initializeCamera3D((Vec3f){0, 0, -10}, (Vec3f){0, 0, 0}, degreesToRadians(60));

    addKeyPressEventListener(SDLK_w, onMoveForwardCamera);
    addKeyPressEventListener(SDLK_s, onMoveBackwardCamera);
    addKeyPressEventListener(SDLK_a, onRotateCameraLeft);
    addKeyPressEventListener(SDLK_d, onRotateCameraRight);
    addKeyPressEventListener(SDLK_UP, onRotateCameraUp);
    addKeyPressEventListener(SDLK_DOWN, onRotateCameraBottom);

    Vec3f cubeVertices[8] = {
        {-1, 1, 1}, {1, 1, 1},
        {1, -1, 1}, {-1, -1, 1},
        {-1, 1, -1}, {1, 1, -1},
        {1, -1, -1}, {-1, -1, -1}
    };

    Vec3f cubeVerticesTemp[8] = {{0}};

    int cubeFaces[3 * 6 * 2] = {
        // Front face
        0, 1, 2,
        0, 2, 3,

        // Right face
        1, 5, 6,
        1, 6, 2,

        // Left face
        4, 0, 3,
        4, 3, 7,

        // Back face
        5, 4, 7,
        5, 7, 6,

        // Top face
        4, 5, 1,
        4, 1, 0,

        // Bottom face
        3, 2, 6,
        3, 6, 7,
    };

    double cubeSize = 100.0;

    do
    {
        clearScreen();

        for (int x = 0; x < MATRIX_SIZE_X; ++x)
        {
            for (int y = 0; y < MATRIX_SIZE_Y; ++y)
            {
                for (int z = 0; z < MATRIX_SIZE_Z; ++z)
                {
                    if (cubeMatrix[x][y][z] == 1)
                    {
                        Vec3f cubePosition = {(double)x * 3, (double)y * 3, (double)z * 3};

                        for (int vertexIndex = 0; vertexIndex < 8; ++vertexIndex)
                            cubeVerticesTemp[vertexIndex] = vec3f_add(cubeVertices[vertexIndex], cubePosition);

                        for (int vertexIndex = 0; vertexIndex < 8; ++vertexIndex)
                            cubeVerticesTemp[vertexIndex] = vec3f_subtract(cubeVerticesTemp[vertexIndex], cameraPosition);

                        for (int vertexIndex = 0; vertexIndex < 8; ++vertexIndex)
                            cubeVerticesTemp[vertexIndex] = vec3f_rotate_xyz(cubeVerticesTemp[vertexIndex], cameraPitch, -cameraYaw, -cameraRoll);

                        for (int faceIndex = 0; faceIndex < 3 * 12; faceIndex += 3)
                        {
                            int vertexIndexA = cubeFaces[faceIndex + 0];
                            int vertexIndexB = cubeFaces[faceIndex + 1];
                            int vertexIndexC = cubeFaces[faceIndex + 2];

                            Vec3f *vertexA = &cubeVerticesTemp[vertexIndexA];
                            Vec3f *vertexB = &cubeVerticesTemp[vertexIndexB];
                            Vec3f *vertexC = &cubeVerticesTemp[vertexIndexC];

                            if (vertexA->z <= 0.4 || vertexB->z <= 0.4 || vertexC->z <= 0.4)
                                continue;

                            double projAx = vertexA->x / vertexA->z;
                            double projAy = vertexA->y / vertexA->z;

                            double projBx = vertexB->x / vertexB->z;
                            double projBy = vertexB->y / vertexB->z;

                            double projCx = vertexC->x / vertexC->z;
                            double projCy = vertexC->y / vertexC->z;

                            
                            // backface culling
                            if (calculateParallelogramAreaFromCoords(projCx - projAx, projCy - projAy, projCx - projBx, projCy - projBy) > 0)
                                drawFilledTriangleGradient(
                                    (gScreenWidth >> 1) + (projAx * cubeSize),
                                    (gScreenHeight >> 1) + (projAy * -cubeSize),
                                    (gScreenWidth >> 1) + (projBx * cubeSize),
                                    (gScreenHeight >> 1) + (projBy * -cubeSize),
                                    (gScreenWidth >> 1) + (projCx * cubeSize),
                                    (gScreenHeight >> 1) + (projCy * -cubeSize),
                                    RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255));
                        }
                    }
                }
            }
        }

        draw_info();
        drawScreen();

        renderDelay(16); // Limit to 60 FPS
    } while (ON_GAME_RUNNING);

    return NULL;
}

CREATE_GAME(640, 480, "Basic Game Engine");