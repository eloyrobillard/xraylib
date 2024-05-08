#include <stdio.h>

#include "blib.h"

GameWindow gameWindow = {NULL, 0, false, NULL};

char *GetEventName(int eventID) {
  switch (eventID) {
  case 2:
    return "KeyPress";
  case 3:
    return "KeyRelease";
  case 4:
    return "ButtonPress";
  case 5:
    return "ButtonRelease";
  case 6:
    return "MotionNotify";
  case 7:
    return "EnterNotify";
  case 8:
    return "LeaveNotify";
  case 9:
    return "FocusIn";
  case 10:
    return "FocusOut";
  case 11:
    return "KeymapNotify";
  case 12:
    return "Expose";
  case 13:
    return "GraphicsExpose";
  case 14:
    return "NoExpose";
  case 15:
    return "VisibilityNotify";
  case 16:
    return "CreateNotify";
  case 17:
    return "DestroyNotify";
  case 18:
    return "UnmapNotify";
  case 19:
    return "MapNotify";
  case 20:
    return "MapRequest";
  case 21:
    return "ReparentNotify";
  case 22:
    return "ConfigureNotify";
  case 23:
    return "ConfigureRequest";
  case 24:
    return "GravityNotify";
  case 25:
    return "ResizeRequest";
  case 26:
    return "CirculateNotify";
  case 27:
    return "CirculateRequest";
  case 28:
    return "PropertyNotify";
  case 29:
    return "SelectionClear";
  case 30:
    return "SelectionRequest";
  case 31:
    return "SelectionNotify";
  case 32:
    return "ColormapNotify";
  case 33:
    return "ClientMessage";
  case 34:
    return "MappingNotify";
  case 35:
    return "GenericEvent";
  case 36:
    return "LASTEvent";
  default:
    return "";
  }
}

// Window-related functions
void InitWindow(int width, int height, const char *title) {
  Display *display = XOpenDisplay(NULL);

  if (display == NULL)
    printf("Failed to open display/n");

  gameWindow.display = display;
  gameWindow.window = XCreateSimpleWindow(
      display, DefaultRootWindow(display), 50, 50, width, height, 1,
      BlackPixel(display, 0), WhitePixel(display, 0));

  XSelectInput(display, gameWindow.window, KeyPressMask | StructureNotifyMask);

  XMapWindow(display, gameWindow.window);
}

void CloseWindow() {
  printf("Closing window...\n");
  XDestroyWindow(gameWindow.display, gameWindow.window);
  XCloseDisplay(gameWindow.display);
}

Bool FindKeyPressOrDestroyNotify(Display *d, XEvent *e, XPointer arg) {
  if (e != NULL)
    return e->type == KeyPress || e->type == DestroyNotify;

  return false;
}

bool WindowShouldClose() {
  if (gameWindow.display == NULL)
    return false;

  XEvent event;

  int gotEvent = XCheckIfEvent(gameWindow.display, &event,
                               FindKeyPressOrDestroyNotify, "");

  if (gotEvent)
    printf("Received event: %s\n", GetEventName(event.type));

  switch (event.type) {
  case KeyPress:
  case DestroyNotify:
    gameWindow.shouldClose = true;
    printf("Should close window...\n");
    break;
  }

  return gameWindow.shouldClose;
}

// Drawing-related functions
void ClearBackground(Color color) {
  if (gameWindow.gc != NULL) {
    XGCValues vals;
    vals.background =
        (color.r << 24) + (color.g << 16) + (color.b << 8) + color.a;

    XSetBackground(gameWindow.display, gameWindow.gc, 1L << 3);
  }
}

void BeginDrawing(void) {
  if (gameWindow.display != NULL && gameWindow.gc == NULL) {
    GC graphicsContext =
        XCreateGC(gameWindow.display, gameWindow.window, 0, NULL);
    gameWindow.gc = graphicsContext;
  }
}

void EndDrawing(void) {
  if (gameWindow.gc != NULL) {
    XFreeGC(gameWindow.display, gameWindow.gc);
    gameWindow.gc = NULL;
  }
}

// Timing related functions
void SetTargetFPS(int fps) {}
