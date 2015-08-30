#include <pebble.h>
#include "TODMenu.h"

static Window *window;
static void window_unload(Window *window);
static void window_load(Window *window);
static void config_provider(Window *window);
static Layer *s_simple_bg_layer;
static Layer *s_text_layer;
static int nActiveLine = 1;
static TextLayer *s_menu_title_label;
static TextLayer *s_label[5];
static Entry items[10];
static int nItems = 0;
static char *Title = NULL;

void ShowTODMenu(char *label, short *times, int nEntries,int first)
{
  Title = label;
  memset(items,0,sizeof(items));
  for(int i = 0; i < nEntries; ++i){
    items[i].startTime = times[i];
    items[i].key = (uint32_t)(first + i);
    snprintf(items[i].label, sizeof(items[0].label), "%2d:%02d",items[i].startTime / 100, items[i].startTime % 100);
  }
  nItems = nEntries;
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
  for(int i = 0; i < (int)(sizeof(s_label)/sizeof(s_label[0]));i++){
    text_layer_destroy(s_label[i]);
  }
}
static void up_single_click_handler(ClickRecognizerRef recognizer, void *context)
{
	//. called on single click ...
  nActiveLine--;
  if(nActiveLine < 0) nActiveLine = nItems - 1;
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
  if(nActiveLine >= nItems) nActiveLine = 0;
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
  for(int i = 0; i < nItems; ++i){
    text_layer_set_background_color(s_label[i], (nActiveLine == i) ? GColorWhite : GColorKellyGreen);
  }
}
static void window_load(Window *window) 
{
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

  int Ys[]={28, 57, 85, 113, 142, };
  for(int i = 0; i < (int)(sizeof(Ys)/sizeof(Ys[0])); ++i){
  	s_label[i] = text_layer_create(GRect(0, Ys[i], 144, 30));
  	text_layer_set_text(s_label[i], items[i].label);
  	text_layer_set_background_color(s_label[i], GColorKellyGreen);
  	text_layer_set_text_color(s_label[i], GColorBlack);
  	text_layer_set_font(s_label[i], fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  	text_layer_set_text_alignment(s_label[i], GTextAlignmentCenter);
  	layer_add_child(s_text_layer, text_layer_get_layer(s_label[i]));
  }
}
