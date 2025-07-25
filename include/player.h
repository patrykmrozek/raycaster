#ifndef PLAYER_H
#define PLAYER_H

#include "window.h"
#include "inputs.h"
#include "utils.h"
#include "map.h"
#include "types.h"

#define PLAYER_SIZE 10
#define PLAYER_SPEED_WALK 150.0f
#define PLAYER_SPEED_SPRINT 200.0f
#define PDX_INIT cos(player->a)*3
#define PDY_INIT sin(player->a)*3

typedef struct {
  Uint8 r, g, b, a;
} color_t;

#define COLOR_WHITE (color_t){255, 255, 255, 255}
#define COLOR_RED (color_t){255, 0, 0, 255}

typedef struct {
  vec2_t pos;
  //f32 x, y;
  f64 dx, dy, a, size;
  f32 speed, sens;
  bool is_sprinting;
  color_t color;
} player_t;

void init_player(player_t* player, map_t* map);
bool hit_wall(vec2_t* pos, map_t* map);
void move_left(player_t* player, map_t* map, double delta_time);
void move_right(player_t* player, map_t* map, double delta_time);
void move_forward(player_t* player, map_t* map, double delta_time);
void move_backward(player_t* player, map_t* map, double delta_time);
void look_left(player_t* player, double delta_time);
void look_right(player_t* player, double delta_time);
void move_player(player_t* player, map_t* map, input_state_t* input, double delta_time);
bool has_exit(player_t player, map_t map);


#endif
