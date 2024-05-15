#include "constants.h"
#include "gamestate.h"
#include <raylib.h>

int main(void) {
  InitWindow(WINDOW_W, WINDOW_H, "escape the ray");

  while (!WindowShouldClose()) {
    draw();
    update();
  }

  return 0;
}
