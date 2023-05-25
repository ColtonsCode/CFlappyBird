#include "PipeManager.h"

static int gPipeFramesCounter = 0;
static float gPipeCreationSpeed = 0.6f;

void pipe_manager_update(std::vector<Pipe>* pipes, float dt) {
    for (int i = 0; i < pipes->size(); i++) {
        pipe_update(&pipes->at(i), dt);

        if (pipes->at(i).x < -100) {
            pipes->erase(pipes->begin() + i);
        }
    }

    // Pipe spawning
    gPipeFramesCounter++;
    if (gPipeFramesCounter >= (GetFPS() / gPipeCreationSpeed)) {
        gPipeFramesCounter = 0;

        pipes->push_back(pipe_create(gScreenWidth + 20));
    }
}

void pipe_manager_draw(std::vector<Pipe>* pipes) {
    for (int i = 0; i < pipes->size(); i++) {
        pipe_draw(&pipes->at(i));
    }
}