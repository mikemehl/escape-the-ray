#include "gamestate.h"
#include "title.h"
typedef void (*DrawFn)(void);
typedef void (*UpdateFn)(void);

typedef struct GameState {
  StateName name;
  DrawFn draw;
  UpdateFn update;
} GameState;

static GameState states[] = {
    {.name = TITLE, .draw = title_draw, .update = title_update},
};

static GameState const *curr_state = &states[0];

void draw() {
  if (curr_state)
    curr_state->draw();
}

void update() {
  if (curr_state)
    curr_state->update();
}

void set_state(StateName name) {
  for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++) {
    if (states[i].name == name) {
      curr_state = &states[i];
      break;
    }
  }
}
