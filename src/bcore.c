#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdio.h>

#include "blib.h"

typedef struct GameWindow_ {
  Display *display;
  Window window;
  bool shouldClose;
} GameWindow;

GameWindow gameWindow = {NULL, 0, false};

// Window-related functions
void InitWindow(int width, int height, const char *title) {
  Display *display = XOpenDisplay(NULL);

  if (display == NULL)
    printf("Failed to open display");

  gameWindow.window = XCreateSimpleWindow(
      display, DefaultRootWindow(display), 50, 50, width, height, 1,
      BlackPixel(display, 0), WhitePixel(display, 0));

  XSelectInput(display, gameWindow.window,
               ButtonPressMask | ExposureMask | KeyPressMask |
                   StructureNotifyMask);

  XMapWindow(display, gameWindow.window);

  gameWindow.display = display;

  XEvent event;

  for (;;) {
    XNextEvent(display, &event);

    printf("Received event: %d\n", event.type);

    switch (event.type) {
    case Expose:
      XDrawString(display, gameWindow.window, DefaultGC(display, 0), 100, 100,
                  "Hello X11", 9);
      break;

    case ButtonPress:
    case KeyPress:
    case DestroyNotify:
      gameWindow.shouldClose = true;
      break;
    }
  }
}

void CloseWindow() {
  printf("Closing window...\n");
  XDestroyWindow(gameWindow.display, gameWindow.window);
  XCloseDisplay(gameWindow.display);
}

bool WindowShouldClose() {
  printf("Should close window...\n");
  return gameWindow.shouldClose;
}

// Drawing-related functions
void ClearBackground(Color color);
void BeginDrawing(void);
void EndDrawing(void);

// Timing related functions
void SetTargetFPS(int fps) {}
