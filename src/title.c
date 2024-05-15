#include "constants.h"
#include <raylib.h>

typedef void (*MenuAction)(void);

typedef struct MenuItem {
  char *text;
  MenuAction action;
} MenuItem;

static bool alert = false;

#define ALERT_NYI "NOT YET IMPLEMENTED"

static void draw_alert() {
  static int alert_timer = 5000;
  if (alert == false) {
    alert_timer = 5000;
    return;
  }
  Rectangle rect = {.x = 0, .y = 0, .width = 200, .height = 10};
  if (alert_timer > 0) {
    DrawRectangleRec(rect, RED);
    DrawText(ALERT_NYI, 0, 0, 10, WHITE);
    alert_timer--;
  } else {
    alert = false;
  }
}

static void menu_new() { alert = true; }
static void menu_load() { alert = true; }
static void menu_quit() { CloseWindow(); }

static MenuItem menu[] = {
    {.text = "NEW GAME", .action = menu_new},
    {.text = "LOAD GAME", .action = menu_load},
    {.text = "QUIT", .action = menu_quit},
};

static int menu_selected = 0;

static Color color_table[5] = {
    GREEN, YELLOW, RED, PINK, MAGENTA,
};

static Color const *title_color = &color_table[0];

static Color get_title_color() {
  static int color_ctr = 0;
  if (color_ctr == 120) {
    color_ctr = 0;
    title_color++;
    if (title_color == &color_table[5]) {
      title_color = &color_table[0];
    }
  }
  color_ctr++;
  return *title_color;
}

static void draw_menu() {
  int menu_x = WINDOW_W / 2 - 20 * 5;
  int menu_y = WINDOW_H / 2 + 10;
  for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++) {
    Color c = LIGHTGRAY;
    if (menu_selected == i) {
      c = BLUE;
    }
    DrawText(menu[i].text, menu_x, menu_y + i * 10, 10, c);
  }
}

static void draw_bg() {
  ClearBackground(BLACK);
  /* Weird background, not super cool, but kinda??? */
  /* int const *rand_x = LoadRandomSequence(5, 0, WINDOW_W); */
  /* int const *rand_y = LoadRandomSequence(5, 0, WINDOW_H); */
  /* for (int i = 0; i < 5; i++) { */
  /*   int size = GetRandomValue(6, 36); */
  /*   DrawCircleGradient(rand_x[i], rand_y[i], size, GREEN, PINK); */
  /* } */
}

void title_draw() {

  BeginDrawing();
  draw_bg();
  DrawText("ESCAPE THE RAY", (WINDOW_W / 2) - 20 * 5, WINDOW_H / 2 - 10, 20,
           get_title_color());
  draw_menu();
  draw_alert();

  EndDrawing();
}

void title_update() {
  int key = GetKeyPressed();
  switch (key) {
  case KEY_Q:
    CloseWindow();
    break;
  case KEY_UP:
    if (menu_selected > 0) {
      menu_selected--;
    }
    break;
  case KEY_DOWN:
    if (menu_selected < sizeof(menu) / sizeof(menu[0])) {
      menu_selected++;
    }
    break;
  case KEY_ENTER:
    alert = false;
    menu[menu_selected].action();
  }
}
