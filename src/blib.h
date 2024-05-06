#ifndef BLIB_H
#define BLIB_H
#include <stdbool.h>

// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Color;

// Window-related functions
void InitWindow(int width, int height, const char *title);

void CloseWindow();

bool WindowShouldClose();

// Drawing-related functions
void ClearBackground(Color color);
void BeginDrawing(void);
void EndDrawing(void);

// Timing related functions
void SetTargetFPS(int fps);

#endif
