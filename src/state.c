#include "state.h"
#include "game.h"

//state handler table
//struct of function pointers that maps states to functions (avoids having to use if else or switch statements)
game_state_handler_t state_handlers[STATE_COUNT] = {
  [STATE_MENU] = {game_update_menu, game_render_menu},
  [STATE_PLAYING] = {game_update_playing, game_render_playing},
  [STATE_PAUSED] = {game_update_paused, game_render_paused},
  [STATE_GAMEOVER] = {game_update_gameover, game_render_gameover}
};
 

void game_update_menu(game_t* game, f64 delta_time) {
  if (is_key_pressed(game->input, SDL_SCANCODE_RETURN)) {
    game->state = STATE_PLAYING;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    game->running = 0;
  }

 }

void game_render_menu(game_t* game) {
  const char menu_main_text[] = "MENU";
  const char menu_description_text[] = "PRESS [ENTER] TO PLAY - PRESS [Q] OR [ESC] TO EXIT THE GAME";
  draw_menu(game->renderer, game->font.main, game->font.desc, menu_main_text, menu_description_text);
}


void game_update_playing(game_t* game, f64 delta_time) {
  move_player(&game->player, game->map, game->input, delta_time);
  if (has_exit(game->player, *game->map)) {
    game->state = STATE_GAMEOVER;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_P)) {
    game->state = STATE_PAUSED;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    game_init(game);
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_M)) {
    //printf("M PRESSED\n");
    game->map_visible = !game->map_visible; //inverts map_visible current state
  }

}

void game_render_playing(game_t* game) {
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);//clear screen
    if (game->map_visible) {
      SDL_RenderCopy(game->renderer, game->cached_map, NULL, &game->map_rect);//copy map texture to renderer instead of redrawing every frame
      draw_player(game->renderer, &game->player, game->map, &game->map_rect); 
  };
    //printf("X: %f, Y: %f\n", player.x, player.y);
    //printf("ROW: %f, COL: %f\n", floor(player.y / map->tile_size), floor(player.x / map->tile_size));
    draw_bg(game->renderer, game->map_visible);
    //printf("X: %f, Y: %f ANGLE: %f\n", player.x, player.y, player.a);
    cast_rays(game->renderer, game->map_visible, &game->player, game->map, &game->map_rect);
    SDL_RenderPresent(game->renderer);
}

void game_update_paused(game_t* game, f64 delta_time) {
  if (is_key_pressed(game->input, SDL_SCANCODE_P) || is_key_pressed(game->input, SDL_SCANCODE_RETURN)) {
    game->state = STATE_PLAYING;
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    game_init(game);
  }
  /*
  if (is_key_pressed(game->input, SDL_SCANCODE_R)) {
    printf("\t[[PLAYING]]\nPRESS [P] TO PAUSE\nPRESS [Q] OR [ESC] TO EXIT TO MENU\n\n");
    game_restart(game);
  }
  */
}

void game_render_paused(game_t* game) {
  const char pause_main_text[] = "PAUSED";
  const char pause_description_text[] = "PRESS [P] OR [ENTER] TO UNPAUSE - PRESS[R] TO RESTART - PRESS [Q] OR [ESC] TO EXIT TO MENU";
  draw_menu(game->renderer, game->font.main, game->font.desc, pause_main_text, pause_description_text);
}

void game_update_gameover(game_t* game, f64 delta_time) {
   if (is_key_pressed(game->input, SDL_SCANCODE_Q) || is_key_pressed(game->input, SDL_SCANCODE_ESCAPE)) {
    game_init(game);
    //game_restart(game);
  }
  if (is_key_pressed(game->input, SDL_SCANCODE_RETURN) || is_key_pressed(game->input, SDL_SCANCODE_R)) {
    game_init(game);
    game->state = STATE_PLAYING;
  }


}
void game_render_gameover(game_t* game) {
  const char gameover_main_text[] = "GAMEOVER";
  const char gameover_description_text[] = "PRESS [ENTER] OR [R] TO RESTART - PRESS [Q] OR [ESC] TO EXIT TO MENU";
  draw_menu(game->renderer, game->font.main, game->font.desc, gameover_main_text, gameover_description_text);
}


