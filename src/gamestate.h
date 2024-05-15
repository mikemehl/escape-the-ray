#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

typedef enum StateName {
  TITLE,
} StateName;

void draw();
void update();
void set_state(StateName);
#endif
