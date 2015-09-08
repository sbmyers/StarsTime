#include <pebble.h>
#include "game_info.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_visitor;
static TextLayer *s_textlayer_vs;
static TextLayer *s_textlayer_host;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text(s_textlayer_1, "Dallas Stars");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_visitor
  s_textlayer_visitor = text_layer_create(GRect(0, 20, 144, 20));
  text_layer_set_background_color(s_textlayer_visitor, GColorClear);
  text_layer_set_text(s_textlayer_visitor, "OPP");
  text_layer_set_text_alignment(s_textlayer_visitor, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_visitor);
  
  // s_textlayer_vs
  s_textlayer_vs = text_layer_create(GRect(0, 40, 144, 20));
  text_layer_set_background_color(s_textlayer_vs, GColorClear);
  text_layer_set_text(s_textlayer_vs, "vs");
  text_layer_set_text_alignment(s_textlayer_vs, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_vs);
  
  // s_textlayer_host
  s_textlayer_host = text_layer_create(GRect(0, 80, 144, 20));
  text_layer_set_background_color(s_textlayer_host, GColorClear);
  text_layer_set_text(s_textlayer_host, "Home");
  text_layer_set_text_alignment(s_textlayer_host, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_host);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_visitor);
  text_layer_destroy(s_textlayer_vs);
  text_layer_destroy(s_textlayer_host);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_game_info(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_game_info(void) {
  window_stack_remove(s_window, true);
}
