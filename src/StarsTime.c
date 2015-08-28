#include "simple_analog.h"

#include "pebble.h"
#include "Schedule.h"
  
static Window *window;
static Layer *s_simple_bg_layer, *s_date_layer, *s_hands_layer;
static TextLayer *s_num_label;
static TextLayer *s_OpponentLabel;
static TextLayer *s_GameTimeLabel;
static TextLayer *s_RoadLabel;

static GPath *s_tick_paths[NUM_CLOCK_TICKS];
static GPath *s_minute_arrow, *s_hour_arrow;
static char s_num_buffer[4], s_day_buffer[6];
static char s_Opponent_buffer[4];
static char s_GameTime_buffer[6];
static char s_Road_buffer[4];
static GPath *Star[4];
static GPath *HiLites[6];

static void bg_update_proc(Layer *layer, GContext *ctx) {
    graphics_context_set_fill_color(ctx, GColorKellyGreen);
    graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
    graphics_context_set_fill_color(ctx, GColorWhite);
    gpath_draw_filled(ctx, Star[0]);
    graphics_context_set_fill_color(ctx, GColorBlack);
    gpath_draw_filled(ctx, Star[1]);
    graphics_context_set_fill_color(ctx, GColorWhite);
    gpath_draw_filled(ctx, Star[2]);
    graphics_context_set_fill_color(ctx, GColorLightGray);
    for (int i = 0; i < 6; ++i){
#if 0      
        graphics_context_set_fill_color(ctx, i == 2 ? GColorRed : GColorLightGray);
        graphics_context_set_stroke_color(ctx, i == 2 ? GColorRed : GColorLightGray);
#endif      
        gpath_draw_filled(ctx, HiLites[i]);
    }
    graphics_context_set_fill_color(ctx, GColorBlack);
    gpath_draw_filled(ctx, Star[3]);

    graphics_context_set_fill_color(ctx, GColorWhite);
    for (int i = 0; i < NUM_CLOCK_TICKS; ++i) {
        gpath_draw_filled(ctx, s_tick_paths[i]);
    }
}

static void hands_update_proc(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);
    GPoint center = grect_center_point(&bounds);
    int16_t second_hand_length = bounds.size.w / 2;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int32_t second_angle = TRIG_MAX_ANGLE * t->tm_sec / 60;
    GPoint second_hand = {
        .x = (int16_t)(sin_lookup(second_angle) * (int32_t)second_hand_length / TRIG_MAX_RATIO) + center.x,
        .y = (int16_t)(-cos_lookup(second_angle) * (int32_t)second_hand_length / TRIG_MAX_RATIO) + center.y,
    };

    // second hand
    graphics_context_set_stroke_color(ctx, GColorWhite);
    graphics_draw_line(ctx, second_hand, center);

    // minute/hour hand
    graphics_context_set_fill_color(ctx, GColorWhite);
    graphics_context_set_stroke_color(ctx, GColorBlack);

    gpath_rotate_to(s_minute_arrow, TRIG_MAX_ANGLE * t->tm_min / 60);
    gpath_draw_filled(ctx, s_minute_arrow);
    gpath_draw_outline(ctx, s_minute_arrow);

    gpath_rotate_to(s_hour_arrow, (TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6));
    gpath_draw_filled(ctx, s_hour_arrow);
    gpath_draw_outline(ctx, s_hour_arrow);

    // dot in the middle
    graphics_context_set_fill_color(ctx, GColorKellyGreen);
    graphics_fill_rect(ctx, GRect(bounds.size.w / 2 - 1, bounds.size.h / 2 - 1, 3, 3), 0, GCornerNone);
}

static void date_update_proc(Layer *layer, GContext *ctx) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(s_num_buffer, sizeof(s_num_buffer), "%d", t);
    text_layer_set_text(s_num_label, s_num_buffer);
}

static void handle_second_tick(struct tm *tick_time, TimeUnits units_changed) {
    layer_mark_dirty(window_get_root_layer(window));
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_simple_bg_layer = layer_create(bounds);
    layer_set_update_proc(s_simple_bg_layer, bg_update_proc);
    layer_add_child(window_layer, s_simple_bg_layer);

    s_date_layer = layer_create(bounds);
    layer_set_update_proc(s_date_layer, date_update_proc);
    layer_add_child(window_layer, s_date_layer);

    s_num_label = text_layer_create(GRect(110, 124, 18, 20));
    text_layer_set_text(s_num_label, s_num_buffer);
    text_layer_set_background_color(s_num_label, GColorKellyGreen);
    text_layer_set_text_color(s_num_label, GColorWhite);
    text_layer_set_font(s_num_label, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));

    s_OpponentLabel = text_layer_create(GRect(100, 30, 28, 20));
    strncpy(s_Opponent_buffer, "ANA", sizeof(s_Opponent_buffer));
    text_layer_set_text(s_OpponentLabel, s_Opponent_buffer);
    text_layer_set_background_color(s_OpponentLabel, GColorKellyGreen);
    text_layer_set_text_color(s_OpponentLabel, GColorMediumAquamarine);
    text_layer_set_font(s_OpponentLabel, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));

    s_RoadLabel = text_layer_create(GRect(100, 110, 28, 20));
    strncpy(s_Road_buffer, "XXX", sizeof(s_Road_buffer));
    text_layer_set_text(s_RoadLabel, s_Road_buffer);
    text_layer_set_background_color(s_RoadLabel, GColorKellyGreen);
    text_layer_set_text_color(s_RoadLabel, GColorYellow);
    text_layer_set_font(s_RoadLabel, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));

    s_GameTimeLabel = text_layer_create(GRect(29, 30, 28, 20));
    strncpy(s_GameTime_buffer, "7:30", sizeof(s_GameTime_buffer));
    text_layer_set_text(s_GameTimeLabel, s_GameTime_buffer);
    text_layer_set_background_color(s_GameTimeLabel, GColorKellyGreen);
    text_layer_set_text_color(s_GameTimeLabel, GColorBlack);
    text_layer_set_font(s_GameTimeLabel, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));

    layer_add_child(s_date_layer, text_layer_get_layer(s_num_label));
    layer_add_child(s_date_layer, text_layer_get_layer(s_OpponentLabel));
    layer_add_child(s_date_layer, text_layer_get_layer(s_GameTimeLabel));
    layer_add_child(s_date_layer, text_layer_get_layer(s_RoadLabel));

    s_hands_layer = layer_create(bounds);
    layer_set_update_proc(s_hands_layer, hands_update_proc);
    layer_add_child(window_layer, s_hands_layer);
}

static void window_unload(Window *window) {
    layer_destroy(s_simple_bg_layer);
    layer_destroy(s_date_layer);

    text_layer_destroy(s_num_label);
    text_layer_destroy(s_OpponentLabel);
    text_layer_destroy(s_GameTimeLabel);

    layer_destroy(s_hands_layer);
}

static void init() {
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
            .unload = window_unload,
    });
    window_stack_push(window, true);

    s_day_buffer[0] = '\0';
    s_num_buffer[0] = '\0';

    // init hand paths
    s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS);
    s_hour_arrow = gpath_create(&HOUR_HAND_POINTS);

    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    GPoint center = grect_center_point(&bounds);
    gpath_move_to(s_minute_arrow, center);
    gpath_move_to(s_hour_arrow, center);

    for (int i = 0; i < NUM_CLOCK_TICKS; ++i) {
        s_tick_paths[i] = gpath_create(&ANALOG_BG_POINTS[i]);
    }
    Star[0] = gpath_create(&FillGray);
    Star[1] = gpath_create(&FillBlack);
    Star[2] = gpath_create(&FillWhite);
    Star[3] = gpath_create(&FillCenter);
    for (int i = 0; i < 6; ++i){
        HiLites[i] = gpath_create(&HiLitePts[i]);
    }

    tick_timer_service_subscribe(SECOND_UNIT, handle_second_tick);
}

static void deinit() {
    gpath_destroy(s_minute_arrow);
    gpath_destroy(s_hour_arrow);

    for (int i = 0; i < NUM_CLOCK_TICKS; ++i) {
        gpath_destroy(s_tick_paths[i]);
    }
    for (int i = 0; i < 4; ++i){
        gpath_destroy(Star[i]);
    }

    tick_timer_service_unsubscribe();
    window_destroy(window);
}

int main() {
    init();
    app_event_loop();
    deinit();
}