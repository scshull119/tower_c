#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

void loadMstsModel() {
    // Loads an MSTS model and prepares it for rendering by raylib
    char path[128];
    strcpy(path, getenv("TCRS_BASE"));
    strcat(path, "/trains/pacific/pacific.s");
    printf("Loading MSTS model...\n");
    FILE *sFile = fopen(path, "rb");
    if (sFile == NULL) {
        printf("Unable to open .s file.\n");
        return;
    }
    char header[16];
    fread(header, 16, 1, sFile);
    for (int i = 0; i < 16; i++) {
        printf("%d\n", header[i]);
    }
    fclose(sFile);
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
