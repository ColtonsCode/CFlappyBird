#pragma once

#include <vector>
#include "Pipe.h"


// Updates all pipes in vector<Pipe>
void pipe_manager_update(std::vector<Pipe>* pipes, float dt);

// Draws all pipes in vector<Pipe>
void pipe_manager_draw(std::vector<Pipe>* pipes);