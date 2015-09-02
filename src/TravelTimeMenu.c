#include "pebble.h"
#include "StarsTime.h"
#include "adjust_time.h"

#define NUM_MENU_SECTIONS 1
  
static int nStation = 0;
static void menu_select_callback(int index, void *ctx);
static int s_nSunday = 0;
static int s_nWeekday = 0;
static int s_nSaturdayday = 0;
  
typedef struct {
	char *title;
	SimpleMenuLayerSelectCallback callback;
} subMenu;
static Window *s_main_window;
static SimpleMenuLayer *s_simple_menu_layer;
static SimpleMenuSection s_menu_sections[NUM_MENU_SECTIONS];

static char sundaySubTitle[30];
static char weekdaySubTitle[30];
static char saturdaySubTitle[30];

static SimpleMenuItem s_first_menu_items[] = {
	{ "Sundays", sundaySubTitle, NULL, menu_select_callback },    // 0
	{ "Weekday", weekdaySubTitle, NULL, menu_select_callback },    // 1
	{ "Saturdays", saturdaySubTitle, NULL, menu_select_callback },  // 2
};
static const int numMenuItems = (sizeof(s_first_menu_items) / sizeof(s_first_menu_items[0]));
static char Title[30];
//static GBitmap *s_menu_icon_image;

static void menu_select_callback(int index, void *ctx) {
  nStation = index;
  persist_write_int(skStation, nStation);
  switch(index){
    case 0:  // Sunday
      show_adjust_time("", "Sundays", "AAC", skTravelTimeSunday);
    break;
    case 1:  // Weekday
      show_adjust_time("TRE", "Weekdays", Title, skTravelTimeWeekDay);
    break;
    case 2:  // Saturday
      show_adjust_time("TRE", "Saturdays", Title, skTravelTimeSaturday);
    break;
  }
	layer_mark_dirty(simple_menu_layer_get_layer(s_simple_menu_layer));
}

static void main_window_load(Window *window) {
	//  s_menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

  nStation = persist_read_int(skStation);

	s_menu_sections[0] = (SimpleMenuSection) {
		.num_items = numMenuItems,
		.items = s_first_menu_items,
    .title = Title,
	};

	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);

	s_simple_menu_layer = simple_menu_layer_create(bounds, window, s_menu_sections, NUM_MENU_SECTIONS, NULL);
	simple_menu_layer_set_selected_index(s_simple_menu_layer, nStation, true);

	layer_add_child(window_layer, simple_menu_layer_get_layer(s_simple_menu_layer));
}

static void main_window_unload(Window *window) {
	simple_menu_layer_destroy(s_simple_menu_layer);
	//  gbitmap_destroy(s_menu_icon_image);
}
static void main_window_appear(Window *window){
  s_nSunday = persist_read_int(skTravelTimeSunday);
  snprintf(sundaySubTitle, sizeof(sundaySubTitle),"%d minutes", s_nSunday);
  s_nWeekday = persist_read_int(skTravelTimeWeekDay);
  snprintf(weekdaySubTitle, sizeof(sundaySubTitle),"%d minutes", s_nWeekday);
  s_nSaturdayday = persist_read_int(skTravelTimeSaturday);
  snprintf(saturdaySubTitle, sizeof(sundaySubTitle),"%d minutes", s_nSaturdayday);
}
void TravelTimeMenu(const char *title)
{
  strncpy(Title, title,sizeof(Title));
  main_window_appear(NULL);
  
	s_main_window = window_create();
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
    .appear = main_window_appear,
	});
	window_stack_push(s_main_window, true);
}