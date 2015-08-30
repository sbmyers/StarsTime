#include <pebble.h>
#include "TimeSelector.h"
#include "Schedule.h"

static Window *window;
static void window_unload(Window *window);
static void window_load(Window *window);
static void config_provider(Window *window);
static Layer *s_simple_bg_layer;
static Layer *s_text_layer;
static int nActiveLine = 1;
static TextLayer *s_menu_title_label;
static TextLayer *s_weekday_label;
static TextLayer *s_saturday_label;
static TextLayer *s_sunday_label;

static char *Title = NULL;

void ShowTimeSelect(char *title, short startTime,int nID)
{
  Title = title;
  nActiveLine = 1;
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers) {
		.load = window_load,
		.unload = window_unload,
	});
	window_stack_push(window, true);
	// Init controls
	window_set_click_config_provider(window, (ClickConfigProvider)config_provider);
}

static void window_unload(Window *window)
{
	layer_destroy(s_simple_bg_layer);
	layer_destroy(s_text_layer);
	text_layer_destroy(s_menu_title_label);
	text_layer_destroy(s_weekday_label);
	text_layer_destroy(s_saturday_label);
	text_layer_destroy(s_sunday_label);
}
static void up_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
	//. called on single click ...
  nActiveLine--;
  if(nActiveLine < 0) nActiveLine = 2;
  layer_mark_dirty(s_text_layer);
}

static void select_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
	//. called on single click ...
}

static void down_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
	//. called on single click ...
  nActiveLine++;
  if(nActiveLine > 2) nActiveLine = 0;
  layer_mark_dirty(s_text_layer);
	//Window *window = (Window *)context;
}

static void config_provider(Window *window)
{
	// single click / repeat-on-hold config:
	window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
	window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
}
static void bg_update_proc(Layer *layer, GContext *ctx)
{
	graphics_context_set_fill_color(ctx, GColorKellyGreen);
	graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}
static void text_update_proc(Layer *layer, GContext *ctx)
{
  text_layer_set_background_color(s_sunday_label, (nActiveLine == 0) ? GColorWhite : GColorKellyGreen);
  text_layer_set_background_color(s_weekday_label, (nActiveLine == 1) ? GColorWhite : GColorKellyGreen);
  text_layer_set_background_color(s_saturday_label, (nActiveLine == 2) ? GColorWhite : GColorKellyGreen);
}
static void window_load(Window *window) {
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(window_layer);
	s_simple_bg_layer = layer_create(bounds);
	layer_set_update_proc(s_simple_bg_layer, bg_update_proc);
	layer_add_child(window_layer, s_simple_bg_layer);


	s_text_layer = layer_create(bounds);
	layer_set_update_proc(s_text_layer, text_update_proc);
	layer_add_child(window_layer, s_text_layer);

	s_menu_title_label = text_layer_create(GRect(0, 0, 144, 40));
	text_layer_set_text(s_menu_title_label, Title);
	text_layer_set_background_color(s_menu_title_label, GColorLightGray);
	text_layer_set_text_color(s_menu_title_label, GColorBlack);
	text_layer_set_font(s_menu_title_label, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(s_menu_title_label, GTextAlignmentCenter);
	layer_add_child(s_text_layer, text_layer_get_layer(s_menu_title_label));

	s_weekday_label = text_layer_create(GRect(0, 43, 144, 30));
	text_layer_set_text(s_weekday_label, "Stuff");
	text_layer_set_background_color(s_weekday_label, GColorKellyGreen);
	text_layer_set_text_color(s_weekday_label, GColorBlack);
	text_layer_set_font(s_weekday_label, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(s_weekday_label, GTextAlignmentCenter);
	layer_add_child(s_text_layer, text_layer_get_layer(s_weekday_label));

	s_saturday_label = text_layer_create(GRect(0, 85, 144, 30));
	text_layer_set_text(s_saturday_label, "More");
	text_layer_set_background_color(s_saturday_label, GColorKellyGreen);
	text_layer_set_text_color(s_saturday_label, GColorBlack);
	text_layer_set_font(s_saturday_label, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(s_saturday_label, GTextAlignmentCenter);
	layer_add_child(s_text_layer, text_layer_get_layer(s_saturday_label));
	
	s_sunday_label = text_layer_create(GRect(0, 128, 144, 30));
	text_layer_set_text(s_sunday_label, "Things");
	text_layer_set_background_color(s_sunday_label, GColorKellyGreen);
	text_layer_set_text_color(s_sunday_label, GColorBlack);
	text_layer_set_font(s_sunday_label, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(s_sunday_label, GTextAlignmentCenter);
	layer_add_child(s_text_layer, text_layer_get_layer(s_sunday_label));
}
