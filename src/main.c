#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_first_page_layer;
  
static void create_enter_password() {
  s_first_page_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_first_page_layer, GColorClear);
  text_layer_set_text_color(s_first_page_layer, GColorBlack);
  text_layer_set_text(s_first_page_layer, "Enter Password");
}

static void create_set_password() {
  s_first_page_layer = text_layer_create(GRect(1, 55, 144, 50));
  text_layer_set_background_color(s_first_page_layer, GColorClear);
  text_layer_set_text_color(s_first_page_layer, GColorBlack);
  text_layer_set_text(s_first_page_layer, "Set New Password");
}

static void main_window_load(Window *window) {
  // Create first_page TextLayer
  create_enter_password();
  create_set_password();
}

static void main_window_unload(Window *window) {

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