#include "pebble.h"
#include "StarsTime.h"

#define NUM_MENU_SECTIONS 1
  
static int nStation = 0;
static void menu_select_callback(int index, void *ctx);

typedef struct {
	char *title;
	SimpleMenuLayerSelectCallback callback;
} subMenu;
static Window *s_main_window;
static SimpleMenuLayer *s_simple_menu_layer;
static SimpleMenuSection s_menu_sections[NUM_MENU_SECTIONS];
static SimpleMenuItem s_first_menu_items[] = {
	{ "T&P Station", NULL, NULL, menu_select_callback },     // 0
	{ "Ft Worth ITC", NULL, NULL, menu_select_callback },    // 1
	{ "Richland Hills", NULL, NULL, menu_select_callback },  // 2
	{ "Bell", NULL, NULL, menu_select_callback },            // 3
	{ "Centerpoint DFW", NULL, NULL, menu_select_callback }, // 4
	{ "West Irving", NULL, NULL, menu_select_callback },      // 5
	{ "Downtown Irving", NULL, NULL, menu_select_callback },  // 6
	{ "Medical Market", NULL, NULL, menu_select_callback },  // 7
};
static const int numMenuItems = (sizeof(s_first_menu_items) / sizeof(s_first_menu_items[0]));
//static GBitmap *s_menu_icon_image;
static void SetSubTitles()
{
  for(int i = 0; i < numMenuItems; ++i){
    s_first_menu_items[i].subtitle = (nStation == i) ? "Selected Station" : NULL;
  }
}
static void menu_select_callback(int index, void *ctx) {
  nStation = index;
  persist_write_int(skStation, nStation);
  SetSubTitles();
	layer_mark_dirty(simple_menu_layer_get_layer(s_simple_menu_layer));
}

static void main_window_load(Window *window) {
	//  s_menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

  nStation = persist_read_int(skStation);
  SetSubTitles();

	s_menu_sections[0] = (SimpleMenuSection) {
		.num_items = numMenuItems,
		.items = s_first_menu_items,
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

void TreMenu()
{
	s_main_window = window_create();
	window_set_window_handlers(s_main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});
	window_stack_push(s_main_window, true);
}


