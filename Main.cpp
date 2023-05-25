#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "Player.h"
#include "Globals.h"
#include "PipeManager.h"

#include <vector>

const int gScreenWidth = 600;
const int gScreenHeight = 800;

int main(void) {
    // Initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(240);
    InitWindow(gScreenWidth, gScreenHeight, "Flappy Bird in C!");

    RenderTexture renderTexture = LoadRenderTexture(600, 800);

    Texture2D background = LoadTexture("assets/Background/Background2.png");
    float bg_x = 0;

    // Game init
    int score = 0;

    Player bird = player_create();

    std::vector<Pipe> pipes;

    double previousTime = GetTime();
    double currentTime = 0.0;
    double updateDrawTime = 0.0;
    float deltaTime = 0.0f;

    // Main game loop
    while (!WindowShouldClose()) {

        if (bird.alive) {
            pipe_manager_update(&pipes, deltaTime);
        }

        player_update(&bird, deltaTime);

        for (int i = 0; i < pipes.size(); i++) {
            if (pipes[i].x <= bird.x && pipes[i].isScored == false) {
                score += 1;
                pipes[i].isScored = true;
            }

            if (player_collide_rectangle(&bird, pipes[i].topPipeRect)
                || player_collide_rectangle(&bird, pipes[i].topPipeCap)
                || player_collide_rectangle(&bird, pipes[i].bottomPipeRect)
                || player_collide_rectangle(&bird, pipes[i].bottomPipeCap))
            {
                bird.alive = false;
            }
        }
        
        BeginTextureMode(renderTexture);

        ClearBackground(BLACK);

        DrawTexturePro(
            background,
            Rectangle {bg_x,0, (float)background.width, (float)background.height},
            Rectangle{ 0, 0, gScreenWidth, gScreenHeight },
            Vector2{ 0, 0 },
            0,
            WHITE
        );

        if (bird.alive)
            bg_x += 0.05;

        pipe_manager_draw(&pipes);

        player_draw(&bird);

        DrawRectangleLines(0, 0, gScreenWidth, gScreenHeight, YELLOW);

        // Time calculations for physics
        currentTime = GetTime();

        updateDrawTime = currentTime - previousTime;

        deltaTime = (float)updateDrawTime;

        previousTime = currentTime;

        int scoreWidth = MeasureText(TextFormat("%d", score), 50);
        // Draw Score
        DrawText(TextFormat("%d", score), (gScreenWidth / 2) - (scoreWidth / 2.0f), 40, 50, RAYWHITE);

        if (bird.alive == false) {

            const char deathText[] = "Press R to Restart!";
            int deathTextWidth = MeasureText(deathText, 50);
            // Draw Score
            DrawText(deathText, (gScreenWidth / 2) - (deathTextWidth / 2.0f), 80, 50, RAYWHITE);

            if (IsKeyPressed(KEY_R)) {
                bird.y = gScreenHeight / 2;
                score = 0;
                pipes.clear();
                bird.alive = true;
            }
        }

        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RAYWHITE);

        EndTextureMode();

        // Rendering
        BeginDrawing();

        ClearBackground(BLACK);

        // Maintain Aspect Ratio
        float renderWidth = GetScreenHeight() * ((float)gScreenWidth / (float)gScreenHeight);

        DrawTexturePro(
            renderTexture.texture,
            Rectangle {
                0,
                0,
                (float)renderTexture.texture.width,
                (float)-renderTexture.texture.height
            },
            Rectangle {
                (GetScreenWidth() - renderWidth) / 2.0f,
                0,
                GetScreenHeight() * ((float)gScreenWidth / (float)gScreenHeight),
                (float)GetScreenHeight()
            },
            Vector2 { 0, 0 },
            0,
            WHITE
        );

        EndDrawing();
    }

    UnloadRenderTexture(renderTexture);
    CloseWindow();

    return 0;
}