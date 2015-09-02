#include <pebble.h>
#include "adjust_time.h"

static Window *s_window;
static GFont s_res_bitham_42_bold;
static GFont s_res_gothic_18_bold;
//static GFont s_res_bitham_30_black;
static TextLayer *s_textlayer_title;
static TextLayer *s_textlayer_subtitle;
static TextLayer *s_textlayer_time;
static TextLayer *s_textlayer_desc;
static TextLayer *s_textlayer_destination;
static Layer *s_Caller;

static char s_Destination[4];
static char s_Station[16];
static char s_DayOfWeek[10];
static char s_time[6];
static short s_activeDigit = 0;
static uint32_t s_key = 0;

static void up_single_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  s_time[s_activeDigit]++;
  if(s_time[s_activeDigit] == ((s_activeDigit == 2)?'6':'9')){
    s_time[s_activeDigit] = '0';
  }
  layer_mark_dirty(text_layer_get_layer(s_textlayer_time));
  //Window *window = (Window *)context;
}

static void select_single_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  switch(s_activeDigit){
    case 0:
      s_activeDigit = 2;
      break;
    case 2:
      s_activeDigit = 3;
      break;
    case 3:
      s_activeDigit = 0;
      break;
  }

}

static void down_single_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  if(--s_time[s_activeDigit]<'0'){
    s_time[s_activeDigit] = (s_activeDigit == 2)? '5' : '9';
  }

  layer_mark_dirty(text_layer_get_layer(s_textlayer_time));
}
static void config_provider(Window *window) 
{
 // single click / repeat-on-hold config:
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
}
static void initialise_ui(void) {
  s_window = window_create();
#ifndef PBL_SDK_3
  window_set_fullscreen(s_window, true);
#endif
  
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);

  // s_textlayer_title
  s_textlayer_title = text_layer_create(GRect(0, 0, 144, 20));
  text_layer_set_text(s_textlayer_title, s_Destination);
  text_layer_set_text_alignment(s_textlayer_title, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_title);
  
  // s_textlayer_subtitle
  s_textlayer_subtitle = text_layer_create(GRect(0, 20, 144, 20));
  text_layer_set_text(s_textlayer_subtitle, s_DayOfWeek);
  text_layer_set_text_alignment(s_textlayer_subtitle, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_subtitle);
  
  // s_textlayer_destination
  s_textlayer_destination = text_layer_create(GRect(0, 135, 144, 30));
  text_layer_set_text(s_textlayer_destination,s_Station);
  text_layer_set_text_alignment(s_textlayer_destination, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_destination);
  
  // s_textlayer_time
  s_textlayer_time = text_layer_create(GRect(13, 51, 119, 51));
  text_layer_set_text(s_textlayer_time, s_time);
  text_layer_set_text_alignment(s_textlayer_time, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_time, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_time);
  
  // s_textlayer_desc
  s_textlayer_desc = text_layer_create(GRect(5, 112, 138, 27));
  text_layer_set_text(s_textlayer_desc, "Travel Time to");
  text_layer_set_text_alignment(s_textlayer_desc, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_desc, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_desc);
}

static void destroy_ui(void) {
  
  int nresult = ((s_time[0]-'0')*100)  + ((s_time[2]-'0')*10) + (s_time[3]-'0');
  persist_write_int(s_key, nresult);
  layer_mark_dirty(s_Caller);
  
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_title);
  text_layer_destroy(s_textlayer_subtitle);
  text_layer_destroy(s_textlayer_time);
  text_layer_destroy(s_textlayer_desc);
  text_layer_destroy(s_textlayer_destination);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}
void show_adjust_time(const char *destination, const char *dayofweek, const char * station, uint32_t key, Layer *caller)
{
  s_Caller = caller;
  strncpy(s_Destination, destination,sizeof(s_Destination));
  strncpy(s_Station, station,sizeof(s_Station));
  strncpy(s_DayOfWeek, dayofweek,sizeof(s_DayOfWeek));
  s_key = key;
  char work[6];
  snprintf(work,sizeof(work), "%3.3d",(int)persist_read_int(s_key));
  s_time[0] = work[0];
  s_time[1] = ':';
  s_time[2] = work[1];
  s_time[3] = work[2];
  s_time[4] = '\0';
  
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  window_set_click_config_provider(s_window, (ClickConfigProvider) config_provider);
}

void hide_adjust_time(void) {
  window_stack_remove(s_window, true);
}
