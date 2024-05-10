#include "blib.h"
#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>

extern GameWindow gameWindow;

// Text drawing functions
void DrawText(const char *text, int posX, int posY, int fontSize, Color color) {
  int len = strlen(text);

  int fontNum = 0;
  char **fonts = XListFonts(gameWindow.display, "*", 10, &fontNum);
  printf("%s", fonts[0]);

  if (gameWindow.display)
    XDrawString(gameWindow.display, gameWindow.window, gameWindow.gc, posX,
                posY, text, len);
}
