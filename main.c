#include <stdio.h>
#include "raylib.h"

int main(void) {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    printf("Tower C Railroad Simulator\n");
    printf("Version 0.1\n");

    InitWindow(screenWidth, screenHeight, "Tower C Railroad Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tower C Railroad Simulator", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
