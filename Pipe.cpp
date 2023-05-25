#include "Pipe.h"

static const float gPipeWidth = 100;

static const float gCapWidth = 125;
static const float gCapHeight = 45;

static const float gPipeGap = 200;

static const float gPipeSpeed = -175;

static Rectangle gPipeCapTextureFrame = { 0, 0, 32, 16 };
static Rectangle gPipeTextureFrame = { 0, 16, 32, 48 };

static bool isPipeTextureLoaded = false;
static Texture2D gPipeTexture;


Pipe pipe_create(float initial_x) {
    if (isPipeTextureLoaded == false) {
        gPipeTexture = LoadTexture("assets/Tileset/Style 1/PipeStyle1.png");
        isPipeTextureLoaded = true;
    }

    float x = initial_x;
    float y = (float)GetRandomValue((int)gCapHeight + 10 + (int)gPipeGap, gScreenHeight - (int)gCapHeight - 10);

    Pipe pipe = { 0 };
    pipe.x = x;
    pipe.y = y;
    pipe.isScored = false;
    pipe.bottomPipeRect = Rectangle{ (float)x, y + gCapHeight, gPipeWidth, (float)gScreenHeight - y };
    pipe.bottomPipeCap = Rectangle{ x + (gPipeWidth / 2) - (gCapWidth / 2), (float)y, gCapWidth, gCapHeight };
    pipe.topPipeRect = Rectangle{ (float)x, 0, gPipeWidth, y - gPipeGap - gCapHeight };
    pipe.topPipeCap = Rectangle{ x + (gPipeWidth / 2) - (gCapWidth / 2), y - gPipeGap - gCapHeight, gCapWidth, gCapHeight };

    return pipe;
}

void pipe_update(Pipe* pipe, float dt) {
    if (IsKeyPressed(KEY_R)) {
        pipe->y = (float)GetRandomValue((int)gCapHeight + 10 + (int)gPipeGap, gScreenHeight - (int)gCapHeight - 10);
    }

    pipe->x += gPipeSpeed * dt;

    pipe->bottomPipeRect.x = pipe->x;
    pipe->bottomPipeRect.y = pipe->y + gCapHeight;
    pipe->bottomPipeRect.height = gScreenHeight - pipe->y;

    pipe->bottomPipeCap.x = pipe->x + (gPipeWidth / 2) - (gCapWidth / 2);
    pipe->bottomPipeCap.y = pipe->y;

    pipe->topPipeRect.x = pipe->x;
    pipe->topPipeRect.height = pipe->y - gPipeGap - gCapHeight;

    pipe->topPipeCap.x = pipe->x + (gPipeWidth / 2) - (gCapWidth / 2);
    pipe->topPipeCap.y = pipe->y - gPipeGap - gCapHeight;
}

void pipe_draw(Pipe* pipe) {
    /*DrawRectangleLinesEx(pipe->bottomPipeRect, 1, RED);
    DrawRectangleLinesEx(pipe->bottomPipeCap, 1, RED);

    DrawRectangleLinesEx(pipe->topPipeRect, 1, RED);
    DrawRectangleLinesEx(pipe->topPipeCap, 1, RED);*/

    DrawTexturePro(gPipeTexture, gPipeTextureFrame, pipe->bottomPipeRect, Vector2{ 0, 0 }, 0.0f, WHITE);
    DrawTexturePro(gPipeTexture, gPipeCapTextureFrame, pipe->bottomPipeCap, Vector2{ 0, 0 }, 0.0f, WHITE);

    DrawTexturePro(gPipeTexture, gPipeTextureFrame, pipe->topPipeRect, Vector2{ 0, 0 }, 0.0f, WHITE);
    DrawTexturePro(gPipeTexture, gPipeCapTextureFrame, pipe->topPipeCap, Vector2{ 0, 0 }, 0.0f, WHITE);
}