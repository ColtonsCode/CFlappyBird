#pragma once
#include "Globals.h"
#include "raylib.h"

typedef struct Pipe {
    float x;
    float y;
    bool isScored; // Whether or not the player has passed this pipe yet
    Rectangle bottomPipeRect;
    Rectangle bottomPipeCap;
    Rectangle topPipeRect;
    Rectangle topPipeCap;
} Pipe;

Pipe pipe_create(float initial_x);
void pipe_update(Pipe* pipe, float dt);
void pipe_draw(Pipe* pipe);