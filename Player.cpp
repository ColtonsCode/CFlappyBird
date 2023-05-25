#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "Player.h"
#include "Globals.h"

static const float gGravityAccel = 1000;
static const int gPlayerWidth = 70;
static const int gAnimationSpeed = 10;

static bool gIsTextureLoaded = false;
static Texture2D gPlayerTexture;

Player player_create() {
    if (gIsTextureLoaded == false) {
        gPlayerTexture = LoadTexture("assets/player/bird2.png");
        gIsTextureLoaded = true;
    }

    Rectangle currentFrameRect = { 0.0f, 0.0f, (float)gPlayerTexture.width / 4, (float)gPlayerTexture.height };

    Player player = { 0 };
    player.x = 50.0f;
    player.y = (float)GetScreenHeight() / 2;
    player.dx = 0.0f;
    player.dy = 0.0f;
    player.hitRadius = 20;
    player.alive = true;
    player.angle = 0.0f;
    player.drawRect = Rectangle{ 0.0f, 0.0f,  (float)gPlayerWidth, (float)gPlayerWidth };
    player.framesCounter = 0;
    player.currentFrame = 0;
    player.currentFrameRect = currentFrameRect;

    return player;
}

void player_update(Player* player, float dt) {
    player->dy += gGravityAccel * dt;

    // Stop falling when at the bottom of the screen
    if (player->y + gPlayerWidth - 5 > gScreenHeight) {
        player->dy = 0.0f;
    }

    // Player controls
    if (player->alive) {
        if (IsMouseButtonPressed(0)) {
            player->dy = -425.0f;
        }
        if (IsMouseButtonPressed(1)) {
            player->dy = -350.0f / 1.5f;
        }
    }


    // Update position and relevant rectangles
    player->x += player->dx * dt;
    player->y += player->dy * dt;

    player->drawRect.x = player->x;
    player->drawRect.y = player->y;
}

void player_draw(Player* player) {
    // Animation

    if (player->alive) {
        player->framesCounter++;
        if (player->framesCounter >= (GetFPS() / gAnimationSpeed)) {
            player->framesCounter = 0;
            player->currentFrame++;

            if (player->currentFrame > 3) {
                player->currentFrame = 0;
            }

            player->currentFrameRect.x = (float)player->currentFrame * (float)gPlayerTexture.width / 4;
        }
    }

    // Rotation
    rlPushMatrix();

    rlTranslatef(player->drawRect.x + player->drawRect.x / 2, player->drawRect.y + player->drawRect.height / 2, 0);

    rlRotatef(RAD2DEG * -sinf(Clamp(player->dy / 200, DEG2RAD * -30, DEG2RAD * 90)), 0, 0, -1);

    // "+ 10" is a small nudge forwards to better allign with the hitbox
    rlTranslatef(-player->drawRect.width / 2 + 10, -player->drawRect.width / 2, 0);

	DrawTexturePro(
		gPlayerTexture,
		player->currentFrameRect,
        {0, 0, (float)gPlayerWidth, (float)gPlayerWidth},
		{0, 0},
		0,
        WHITE
	);

    rlPopMatrix();

    //// Draw destination rect
    //DrawRectangleLinesEx(player->drawRect, 1.0f, DARKBLUE);

    //// Draw hitcircle
    //DrawCircle(player->x + (gPlayerWidth / 2), player->y + (gPlayerWidth / 2), player->hitRadius, RED);
}

bool player_collide_rectangle(Player* player, Rectangle rect) {
    return CheckCollisionCircleRec(
        Vector2{ player->x + (gPlayerWidth / 2), player->y + (gPlayerWidth / 2) },
        player->hitRadius,
        rect
    );
}