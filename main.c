#include <pebble.h>

static Window* window;
static Layer* layer;

static void up_click_handler(ClickRecognizerRef recognizer, void* context) {
	// Handle up-button clicks
}

static void down_click_handler(ClickRecognizerRef recognizer, void* context) {
	// Handle down-button clicks
}

static void select_click_handler(ClickRecognizerRef recognizer, void* context) {
	// Handle select-button clicks
}

static void click_config_provider(void* context) {
  // How quickly the repeated clicks should fire
  const uint16_t repeat_interval_ms = 100;
  // Attach the UP button to the current context
  window_set_click_context(BUTTON_ID_UP, context);
  // Perform the up_click_handler function repeatedly whilst the UP button is held down
  window_single_repeating_click_subscribe(BUTTON_ID_UP, repeat_interval_ms, up_click_handler);

  // Attach the SELECT button to the current context
  window_set_click_context(BUTTON_ID_SELECT, context);
  // Perform the select_click_handler function repeatedly whilst the SELECT button is held down
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);

  // Attach the DOWN button to the current context
  window_set_click_context(BUTTON_ID_DOWN, context);
  // Perform the down_click_handler function repeatedly whilst the DOWN button is held down
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, repeat_interval_ms, down_click_handler);
	
  // You can guess what things look like for the BACK button
}

// Window is loaded whenever it is pushed onto the window stack
static void window_load(Window *window) {
  // Perform any necessary actions when the window is loaded
}

// A window appears whenever it is displayed on the screen
static void window_appear(Window *window) {
  // Perform any necessary actions whenever the window appears
}

// A window disappears it no longer appears on the screen
static void window_disappear(Window *window) {
  // Perform any necessary actions whenever the window disappears
}

// A window is unloaded when it is popped from the window stack
static void window_unload(Window *window) {
  // Perform any necessary actions when the window is unloaded
}

void init(void) {
  // Stiff we've already seen
  window = window_create();
  window_stack_push(window, true);
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  layer = layer_create(bounds);
  layer_add_child(window_layer, layer);
	
  // Set the click handler config for the specified window
  window_set_click_config_provider(window, click_config_provider);
  // Set all the handlers for the specified window
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
	.appear = window_appear,
	.disappear = window_disappear,
    .unload = window_unload,
  });
}

void deinit(void) {
  layer_destroy(layer);
  window_destroy(window);
}

void main(void) {
  init();
  app_event_loop();
  deinit();
}