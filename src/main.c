#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_first_page_layer
                , *s_enter_password_layer
                , *s_set_password_layer;
  
static void set_first_page_colors() {
  text_layer_set_background_color(s_first_page_layer, GColorClear);
  text_layer_set_text_color(s_first_page_layer, GColorBlack);
}

static void create_enter_password() {
  s_enter_password_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_text_alignment(s_enter_password_layer, GTextAlignmentCenter);
  text_layer_set_text(s_enter_password_layer, "Enter Password");
}

static void create_set_password() {
  s_set_password_layer = text_layer_create(GRect(1, 55, 144, 50));
  text_layer_set_text_alignment(s_set_password_layer, GTextAlignmentCenter);
  text_layer_set_text(s_set_password_layer, "Set New Password");
}

static void create_first_page() {
  set_first_page_colors();
  create_enter_password();
  create_set_password();
}

static void main_window_load(Window *window) {
  // Create first_page TextLayer
  create_first_page();
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_first_page_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_enter_password_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_set_password_layer));
}

static void main_window_unload(Window *window) {
  // Destroy first page
  text_layer_destroy(s_first_page_layer);
  text_layer_destroy(s_enter_password_layer);
  text_layer_destroy(s_set_password_layer);
}

static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();
  
  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  
  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}