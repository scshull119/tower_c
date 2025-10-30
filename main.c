#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

enum Encoding {
    UTF8,
    UTF16LE,
    UTF16BE
};

enum Endianness {
    LITTLE,
    BIG
};

FILE *loadDataFile(const char *filePath) {
    // TODO: Protect against buffer overflow if filepath is too long
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

enum Encoding processBOM(FILE *file) {
    unsigned char bom[3];
    fread(bom, 1, 3, file);

    if (bom[0] == 0xFF && bom[1] == 0xFE) {
        fseek(file, -1, SEEK_CUR);
        return UTF16LE;

    }
    if (bom[0] == 0xFE && bom[1] == 0xFF) {
        fseek(file, -1, SEEK_CUR);
        return UTF16BE;
    }
    if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
        return UTF8;
    }
    rewind(file);
    return UTF8;
}

unsigned char readCharUTF8(FILE *file) {
    const unsigned char val = fgetc(file);
    if (val > 0x7F) {
        printf("Out-of-bounds character. Currently unable to process UTF-8 code points outside of the ASCII range.\n");
        return 0x3F;
    }
    return val;
}

unsigned char readCharUTF16(FILE *file, const enum Endianness ev) {
    unsigned char val = fgetc(file);
    unsigned char zeroVal = fgetc(file);
    if (ev == BIG) {
        const unsigned char temp = val;
        val = zeroVal;
        zeroVal = temp;
    }
    if (val > 0x7F || zeroVal != 0) {
        printf("Out-of-bounds character. Currently unable to process UTF-16 code points outside of the ASCII range.\n");
        return 0x3F;
    }
    return val;
}

void readStringFromFile(FILE *file, char *header, const int size, const enum Encoding encoding) {
    // TODO: Correctly handle EOF when reading characters.
    if (encoding == UTF8) {
        for (int i = 0; i < size; i++) {
            header[i] = (char) readCharUTF8(file);
        }
    } else {
        enum Endianness ev = encoding == UTF16LE ? LITTLE : BIG;
        for (int i = 0; i < size; i++) {
            header[i] = (char) readCharUTF16(file, ev);
        }
    }
    header[size] = '\0';
}

void processDataFile(const char *filePath) {
    FILE *dataFile = loadDataFile(filePath);
    if (dataFile == NULL) {
        return;
    }
    const enum Encoding fileEncoding = processBOM(dataFile);

    switch (fileEncoding) {
        case UTF8:
            printf("UTF-8 encoding\n");
            break;
        case UTF16LE:
            printf("UTF-16 encoding, little endian\n");
            break;
        case UTF16BE:
            printf("UTF-16 encoding, big endian\n");
            break;
    }

    char header[17];
    char subHeader[15];
    char nextText[6];
    readStringFromFile(dataFile, header, 16, fileEncoding);
    readStringFromFile(dataFile, subHeader, 14, fileEncoding);
    // TODO: Find a safer way to seek for beginning of data after the header and subheader.
    fseek(dataFile, 8, SEEK_CUR);
    readStringFromFile(dataFile, nextText, 5, fileEncoding);
    printf("File header: %s\n", header);
    printf("File sub-header: %s\n", subHeader);
    printf("Next text: %s\n", nextText);

    fclose(dataFile);
}

void renderWindow() {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tower C Rail Simulator");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Tower C Rail Simulator", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
}

int main(void) {
    printf("Tower C Rail Simulator\n");
    printf("Version 0.1\n\n");

    processDataFile("/trains/pacific/pacific.s");
    // renderWindow();

    printf("\nTCRS exited.\n");

    return 0;
}
