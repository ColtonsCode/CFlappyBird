#pragma once
#include "raylib.h"

typedef struct Player {
    float x;
    float y;
    float dx;
    float dy;
    float angle;
    bool alive;
    float hitRadius;
    Rectangle drawRect;
    // Animation
    Rectangle currentFrameRect;
    int framesCounter;
    int currentFrame;
} Player;

Player player_create();
void player_update(Player* player, float dt);
void player_draw(Player* player);
bool player_collide_rectangle(Player* player, Rectangle rect);