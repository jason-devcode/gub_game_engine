#include "../include/gub.h"

#include "../include/utils/vectorial_2D.h"

#include "../include/utils/texture.h"
#include "../include/utils/sprite.h"
#include "../include/utils/geometry.h"
#include "../include/utils/keyboard.h"
#include "../include/utils/sprite_animation.h"
#include "../include/core/engine_properties/screen_dimensions.h"
typedef struct _tag_player_animations_
{
    SpriteAnimation *animations;
    int currentAnimationIndex;
    int numAnimations;
} EntityAnimations;

typedef struct _tag_entity_
{
    EntityAnimations entityAnimations;
    Vec2f position;
    double speed;
    uint32_t collisionLayer; // 0,1,2,3,4,5,6,7
} Entity;

Entity player = {{NULL, 0, 0}, {0, 0}, 10, 0};

Sprite *gBombermanSpritesheet;

typedef enum
{
    PLAYER_WALK_LEFT_ANIMATION,
    PLAYER_WALK_RIGHT_ANIMATION,
    PLAYER_WALK_TOP_ANIMATION,
    PLAYER_WALK_BOTTOM_ANIMATION,

    PLAYER_IDLE_LEFT_ANIMATION,
    PLAYER_IDLE_RIGHT_ANIMATION,
    PLAYER_IDLE_TOP_ANIMATION,
    PLAYER_IDLE_BOTTOM_ANIMATION,

    PLAYER_LAST_ANIMATION
} PlayerAnimations;

bool initializePlayer()
{
    player.speed = 15;
    player.position = (Vec2f){gHalfScreenWidth, gHalfScreenHeight};

    player.entityAnimations.numAnimations = PLAYER_LAST_ANIMATION;
    player.entityAnimations.currentAnimationIndex = PLAYER_IDLE_RIGHT_ANIMATION;

    player.entityAnimations.animations = createSequenceOfEmptySpriteAnimation(player.entityAnimations.numAnimations);

    double frameDuration = 1.0 / 60.0 * 6.0;

    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_WALK_LEFT_ANIMATION], 0, 0, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_WALK_RIGHT_ANIMATION], 0, 1, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_WALK_BOTTOM_ANIMATION], 3, 0, 3, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_WALK_TOP_ANIMATION], 3, 1, 3, 1, frameDuration, gBombermanSpritesheet);

    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_IDLE_LEFT_ANIMATION], 1, 0, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_IDLE_RIGHT_ANIMATION], 1, 1, 1, 1, frameDuration, gBombermanSpritesheet);

    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_IDLE_BOTTOM_ANIMATION], 4, 0, 1, 1, frameDuration, gBombermanSpritesheet);
    populateSpriteAnimation(&player.entityAnimations.animations[PLAYER_IDLE_TOP_ANIMATION], 4, 1, 1, 1, frameDuration, gBombermanSpritesheet);
}

void renderPlayer()
{
    SpriteAnimation *currentAnimation = &player.entityAnimations.animations[player.entityAnimations.currentAnimationIndex];
    SpriteFrame *currentFrame = &currentAnimation->frames[currentAnimation->currentFrame];

    drawScaledSubTexture(
        player.position.x, player.position.y,
        gBombermanSpritesheet->texture,
        currentFrame->x, currentFrame->y, currentFrame->w, currentFrame->h,
        32, 32);

    updateSpriteAnimation(currentAnimation);
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
    player.entityAnimations.currentAnimationIndex = PLAYER_WALK_LEFT_ANIMATION;
    player.position.x -= player.speed * deltatime * 0.001;
}

void onMovePlayerRight()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_WALK_RIGHT_ANIMATION;
    player.position.x += player.speed * deltatime * 0.001;
}

void onMovePlayerTop()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_WALK_TOP_ANIMATION;
    player.position.y -= player.speed * deltatime * 0.001;
}

void onMovePlayerBottom()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_WALK_BOTTOM_ANIMATION;
    player.position.y += player.speed * deltatime * 0.001;
}

void onIdleLeftPlayerState()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_IDLE_LEFT_ANIMATION;
}

void onIdleRightPlayerState()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_IDLE_RIGHT_ANIMATION;
}

void onIdleTopPlayerState()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_IDLE_TOP_ANIMATION;
}

void onIdleBottomPlayerState()
{
    player.entityAnimations.currentAnimationIndex = PLAYER_IDLE_BOTTOM_ANIMATION;
}

void gameLoop()
{
    setClearScreenColor(0x388700);
    gBombermanSpritesheet = loadSpriteFromTextureFile("./resources/bomberman_spritesheet.bmp", 14, 24);

    initializePlayer();

    addKeyPressEventListener(GUB_KEY_a, onMovePlayerLeft);
    addKeyPressEventListener(GUB_KEY_d, onMovePlayerRight);

    addKeyPressEventListener(GUB_KEY_w, onMovePlayerTop);
    addKeyPressEventListener(GUB_KEY_s, onMovePlayerBottom);

    addKeyReleaseEventListener(GUB_KEY_a, onIdleLeftPlayerState);
    addKeyReleaseEventListener(GUB_KEY_d, onIdleRightPlayerState);

    addKeyReleaseEventListener(GUB_KEY_w, onIdleTopPlayerState);
    addKeyReleaseEventListener(GUB_KEY_s, onIdleBottomPlayerState);

    do
    {
        clearScreen();

        renderPlayer();

        drawScreen();
        renderDelay(32);
    } while (isGameRunning);

    releasePlayerResources();
    releaseSpriteResources(gBombermanSpritesheet);
}

CREATE_GAME(640, 700, "BOMBERMAN GAME FANMADE")