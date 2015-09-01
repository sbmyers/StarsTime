#include <pebble.h>
#include "tre_schedule.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18_bold;
static TextLayer *s_textlayer_title;
static TextLayer *s_textlayer_station_1;
static TextLayer *s_textlayer_station_2;
static TextLayer *s_textlayer_station_3;
static TextLayer *s_textlayer_station_4;
static TextLayer *s_textlayer_station_5;
static TextLayer *s_textlayer_station_6;
static TextLayer *s_textlayer_station_7;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // s_textlayer_title
  s_textlayer_title = text_layer_create(GRect(0, 0, 144, 21));
  text_layer_set_text(s_textlayer_title, "TRE Station");
  text_layer_set_text_alignment(s_textlayer_title, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_title, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_title);
  
  // s_textlayer_station_1
  s_textlayer_station_1 = text_layer_create(GRect(20, 20, 100, 20));
  text_layer_set_text(s_textlayer_station_1, "T&P Station");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_1);
  
  // s_textlayer_station_2
  s_textlayer_station_2 = text_layer_create(GRect(20, 40, 100, 20));
  text_layer_set_text(s_textlayer_station_2, "Ft Worth ITC");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_2);
  
  // s_textlayer_station_3
  s_textlayer_station_3 = text_layer_create(GRect(20, 60, 100, 20));
  text_layer_set_text(s_textlayer_station_3, "Richland Hills");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_3);
  
  // s_textlayer_station_4
  s_textlayer_station_4 = text_layer_create(GRect(20, 80, 100, 20));
  text_layer_set_text(s_textlayer_station_4, "Bell");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_4);
  
  // s_textlayer_station_5
  s_textlayer_station_5 = text_layer_create(GRect(20, 100, 100, 20));
  text_layer_set_text(s_textlayer_station_5, "Centerpoint DFW");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_5);
  
  // s_textlayer_station_6
  s_textlayer_station_6 = text_layer_create(GRect(20, 120, 100, 20));
  text_layer_set_text(s_textlayer_station_6, "West Irving");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_6);
  
  // s_textlayer_station_7
  s_textlayer_station_7 = text_layer_create(GRect(20, 140, 100, 20));
  text_layer_set_text(s_textlayer_station_7, "Downtown Irving");
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_station_7);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_title);
  text_layer_destroy(s_textlayer_station_1);
  text_layer_destroy(s_textlayer_station_2);
  text_layer_destroy(s_textlayer_station_3);
  text_layer_destroy(s_textlayer_station_4);
  text_layer_destroy(s_textlayer_station_5);
  text_layer_destroy(s_textlayer_station_6);
  text_layer_destroy(s_textlayer_station_7);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_tre_schedule(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_tre_schedule(void) {
  window_stack_remove(s_window, true);
}
