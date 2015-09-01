#include "pebble.h"

#define NUM_MENU_SECTIONS 1
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
//static GBitmap *s_menu_icon_image;

static void menu_select_callback(int index, void *ctx) {
	s_first_menu_items[index].subtitle = "You've hit select here!";
	layer_mark_dirty(simple_menu_layer_get_layer(s_simple_menu_layer));
}

static void main_window_load(Window *window) {
	//  s_menu_icon_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_1);

	// Although we already defined NUM_FIRST_MENU_ITEMS, you can define
	// an int as such to easily change the order of menu items later

	s_menu_sections[0] = (SimpleMenuSection) {
		.num_items = (uint32_t)sizeof(s_first_menu_items) / sizeof(s_first_menu_items[0]),
			.items = s_first_menu_items,
	};

	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);

	s_simple_menu_layer = simple_menu_layer_create(bounds, window, s_menu_sections, NUM_MENU_SECTIONS, NULL);
	simple_menu_layer_set_selected_index(s_simple_menu_layer, 3, true);

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


