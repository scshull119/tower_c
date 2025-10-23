#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

FILE *loadDataFile(const char *filePath) {
    char path[256];
    strcpy(path, getenv("TCRS_BASE"));
    strcat(path, filePath);
    printf("Loading data from %s\n", path);

    FILE *dataFile = fopen(path, "rb");
    if (dataFile == NULL) {
        printf("Unable to open data file.\n");
        return nullptr;
    }
    return dataFile;
}

void readFileHeader(FILE *file) {
    unsigned char buffer[34];
    bool isUTF16 = false;
    fread(buffer, 1, 2, file);
    if (buffer[0] == 0xFF && buffer[1] == 0xFE) {
        isUTF16 = true;
    }
    if (isUTF16) {
        printf("File is UTF-16.\n");
    } else {
        printf("File is not UTF-16.\n");
    }
}

void processDataFile(const char *filePath) {
    FILE *dataFile = loadDataFile(filePath);
    if (dataFile == NULL) {
        return;
    }
    readFileHeader(dataFile);

    fclose(dataFile);
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

    processDataFile("/trains/pacific/pacific.s");
    // renderWindow();

    printf("TCRS exited.\n");

    return 0;
}
