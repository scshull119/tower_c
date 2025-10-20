#include <stdio.h>
#include "raylib.h"

void loadMstsModel() {
    // Loads an MSTS model and prepares it for rendering by raylib
    printf("Loading MSTS model...\n");
}

void renderWindow() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tower C Railroad Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tower C Railroad Simulator", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
}

int main(void) {
    printf("Tower C Railroad Simulator\n");
    printf("Version 0.1\n");

    loadMstsModel();
    // renderWindow();

    printf("TCRS exited.\n");

    return 0;
}
