#include "../include/gub.h"

#include "../include/utils/vectorial_2D.h"

#include "../include/utils/texture.h"
#include "../include/utils/sprite.h"
#include "../include/utils/geometry.h"
#include "../include/utils/keyboard.h"
#include "../include/utils/sprite_animation.h"

typedef struct _tag_player_animations_
{
    SpriteAnimation *animations;
    SpriteAnimation *currentAnimation;
    int numAnimations;
} EntityAnimations;

typedef struct _tag_player_
{
    EntityAnimations entityAnimations;
    Vec2f position;
    double speed;
    uint32_t collisionLayer; // 0,1,2,3,4,5,6,7
} Player;

int playerFrameRow = 1;
int isPlayerMoving = 0;

Player player = {NULL, NULL, 0, 0, 0, 10};

Sprite *gBombermanSpritesheet;

bool initializePlayer()
{
    player.entityAnimations.numAnimations = 14;
    player.entityAnimations.animations = createSequenceOfEmptySpriteAnimation(player.entityAnimations.numAnimations);

    double frameDuration = 1.0 / 60.0 * 8.0;

    populateSpriteAnimation(&player.entityAnimations.animations[0], 0, 0, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[1], 0, 1, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[2], 3, 0, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[3], 3, 1, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[4], 0, 2, 7, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[5], 0, 3, 3, 1, frameDuration * 4, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[6], 4, 3, 7, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[7], 0, 15, 6, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[8], 0, 16, 6, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[9], 0, 17, 6, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[10], 0, 18, 6, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[11], 0, 19, 6, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[12], 0, 20, 6, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[13], 0, 21, 6, 1, frameDuration, gBombermanSpritesheet);
}

void renderPlayer()
{
    for (int animationIndex = 0; animationIndex < player.entityAnimations.numAnimations; ++animationIndex)
    {
        SpriteAnimation *currentAnimation = &player.entityAnimations.animations[animationIndex];
        SpriteFrame *currentFrame = &currentAnimation->frames[currentAnimation->currentFrame];

        drawScaledSubTexture(
            player.position.x + 100, player.position.y + 10 + currentFrame->h * animationIndex * 3,
            gBombermanSpritesheet->texture,
            currentFrame->x, currentFrame->y, currentFrame->w, currentFrame->h,
            32, 32);
    }
}

void releasePlayerResources()
{
    releaseSpriteAnimationResources(player.entityAnimations.animations);
}

void drawScaledSpritesheet(int scaleX, int scaleY)
{
    int width = gBombermanSpritesheet->texture->width * scaleX;
    int height = gBombermanSpritesheet->texture->height * scaleY;

    int cellWidth = ((double)width / (double)gBombermanSpritesheet->numCols) + 0.5;
    int cellHeight = ((double)height / (double)gBombermanSpritesheet->numRows) + 0.5;

    drawScaledTexture(0, 0, gBombermanSpritesheet->texture, width, height);

    for (int col = 1; col < gBombermanSpritesheet->numCols; col++)
        drawVerticalLine(0, height, col * cellWidth, 0xFFFFFFFF);
    for (int row = 1; row < gBombermanSpritesheet->numRows; row++)
        drawHorizontalLine(0, width, row * cellHeight, 0xFFFFFFFF);

    int colMouse = cellWidth * (GET_MOUSE_X() / cellWidth);
    int rowMouse = cellHeight * (GET_MOUSE_Y() / cellHeight);

    drawRectangleWire(colMouse, rowMouse, colMouse + cellWidth, rowMouse + cellHeight, 0xFFFFFF00);
    drawRectangleWire(colMouse + 1, rowMouse + 1, colMouse + cellWidth - 1, rowMouse + cellHeight - 1, 0xFFFFFF00);
    drawRectangleWire(colMouse + 2, rowMouse + 2, colMouse + cellWidth - 2, rowMouse + cellHeight - 2, 0xFFFFFF00);
}

void onMovePlayerLeft()
{
    playerFrameRow = 0;
    isPlayerMoving = 1;
    player.position.x -= player.speed * deltatime * 0.001;
}

void onMovePlayerRight()
{
    playerFrameRow = 1;
    isPlayerMoving = 1;
    player.position.x += player.speed * deltatime * 0.001;
}

void onIdlePlayerState()
{
    isPlayerMoving = 0;
}

void gameLoop()
{
    setClearScreenColor(0x388700);
    gBombermanSpritesheet = loadSpriteFromTextureFile("./resources/bomberman_spritesheet.bmp", 14, 24);

    initializePlayer();

    addKeyPressEventListener(GUB_KEY_a, onMovePlayerLeft);
    addKeyPressEventListener(GUB_KEY_d, onMovePlayerRight);

    addKeyReleaseEventListener(GUB_KEY_a, onIdlePlayerState);
    addKeyReleaseEventListener(GUB_KEY_d, onIdlePlayerState);

    do
    {
        clearScreen();
        // drawScaledSpritesheet(2, 2);

        renderPlayer();

        for (int animationIndex = 0; animationIndex < player.entityAnimations.numAnimations; ++animationIndex)
        {
            SpriteAnimation *animation = &player.entityAnimations.animations[animationIndex];
            updateSpriteAnimation(animation);
        }

        drawScreen();
        renderDelay(16);
    } while (isGameRunning);

    releasePlayerResources();
    releaseSpriteResources(gBombermanSpritesheet);
}

CREATE_GAME(640, 700, "SAMPLE ANIMATIONS")