#include <pebble.h>
#include "adjust_time.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_42_bold;
static GFont s_res_gothic_18_bold;
static GFont s_res_bitham_30_black;
static TextLayer *s_textlayer_title;
static TextLayer *s_textlayer_subtitle;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_desc;
static TextLayer *s_textlayer_destination;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  // s_textlayer_title
  s_textlayer_title = text_layer_create(GRect(20, 0, 100, 20));
  text_layer_set_text(s_textlayer_title, "Text layer");
  text_layer_set_text_alignment(s_textlayer_title, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_title);
  
  // s_textlayer_subtitle
  s_textlayer_subtitle = text_layer_create(GRect(20, 20, 100, 20));
  text_layer_set_text(s_textlayer_subtitle, "Text layer");
  text_layer_set_text_alignment(s_textlayer_subtitle, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_subtitle);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(13, 51, 119, 51));
  text_layer_set_text(s_textlayer_time, "0:00");
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_time, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_desc
  s_textlayer_desc = text_layer_create(GRect(5, 112, 138, 27));
  text_layer_set_text(s_textlayer_desc, "Travel Time to");
  text_layer_set_text_alignment(s_textlayer_desc, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_desc, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_desc);
  
  // s_textlayer_destination
  s_textlayer_destination = text_layer_create(GRect(26, 135, 100, 30));
  text_layer_set_text(s_textlayer_destination, "AAC");
  text_layer_set_text_alignment(s_textlayer_destination, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_destination, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_destination);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_title);
  text_layer_destroy(s_textlayer_subtitle);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_desc);
  text_layer_destroy(s_textlayer_destination);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_adjust_time(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_adjust_time(void) {
  window_stack_remove(s_window, true);
}
