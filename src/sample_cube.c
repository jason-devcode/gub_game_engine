#include "../include/game_engine.h"
#include "../include/utils/geometry.h"
#include "../include/utils/font.h"
#include "../include/utils/color.h"
#include "../include/utils/trigonometry.h"
#include "../include/utils/vectorial_2D.h"
#include "../include/utils/vectorial_3D.h"

void *gameLoop(void *arg)
{
    Vec2f playerPosition = {1, 0};

    double anglePlayer = 0;

    Vec3f cubeVertices[8] = {
        -1, 1, 1,
        1, 1, 1,
        1, -1, 1,
        -1, -1, 1, 

        -1, 1,  -1,
        1, 1,   -1,
        1, -1,  -1,
        -1, -1, -1, 
    };

    int cubeEdges[12<<1] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,


        0, 4,
        1, 5,
        2, 6,
        3, 7,

        4, 5,
        5, 6,
        6, 7,
        7, 4,
    };

    double cubeSize = 100.0;



    do
    {
        clearScreen();

        // rotate cube vertices
        for (int vertexIndex = 0; vertexIndex < 8; ++vertexIndex)
        {
            vec3f_rotate_xyz_in_place(&cubeVertices[vertexIndex], radian, radian, radian);
        }


        drawFormattedText(
            10, 10, 0xFFFFFF00,
            "FPS: %d\ndeltatime: %lf\nplayer coords: (%lf, %lf,)\nangle player: %lf\n",
            getFps(), getDeltatime(),
            playerPosition.x, playerPosition.y,
            anglePlayer);

        for( int edgeIndex = 0; edgeIndex < 24; edgeIndex += 2 )
        {
            int vertexIndexA = cubeEdges[edgeIndex+0];
            int vertexIndexB = cubeEdges[edgeIndex+1];

            Vec3f* vertexA = &cubeVertices[vertexIndexA];
            Vec3f* vertexB = &cubeVertices[vertexIndexB];

            drawLine( 
                (gScreenWidth >> 1) + (vertexA->x * cubeSize), 
                (gScreenHeight >> 1) + (vertexA->y * cubeSize), 
                (gScreenWidth >> 1) + (vertexB->x * cubeSize), 
                (gScreenHeight >> 1) + (vertexB->y * cubeSize), 
                RGB(255,0,0)
            );
        }

        // drawLine( 
        //     (gScreenWidth >> 1),
        //     (gScreenHeight >> 1),
        //     GET_MOUSE_X(), GET_MOUSE_Y(),
        //     RGB(255,0,0)
        //  );

        drawScreen();

        renderDelay(16); // Limit to 60  FPS
    } while (ON_GAME_RUNNING);

    return NULL;
}

CREATE_GAME(640, 480, "Basic Game Engine");