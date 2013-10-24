#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include <time.h>
#include "mini-printf.h"


#define MY_UUID { 0xC2, 0x30, 0x1D, 0x6E, 0xCE, 0x12, 0x42, 0xC8, 0x96, 0x1C, 0xD8, 0x77, 0xF1, 0xF5, 0xDF, 0xF1 }
PBL_APP_INFO(MY_UUID,
             "Unix Watch Face", "Lindsey Crocker and Sam Agnew",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer hello_layer;
char str[100];

static void update_time(){
	time_t seconds = time(NULL);
	snprintf(str, 20, "%d", seconds);
  	text_layer_set_text(&hello_layer, str);
}

static void handle_second_tick(AppContextRef app_ctx, PebbleTickEvent* e){
	update_time();
}

void handle_init(AppContextRef app_ctx) {
	
	window_init(&window, "Unix Time");
	window_stack_push(&window, true /* Animated */);
	window_set_background_color(&window, GColorWhite);
	
	text_layer_init(&hello_layer, GRect(0, 65, 144, 30));
	text_layer_set_text_alignment(&hello_layer, GTextAlignmentCenter);
	text_layer_set_font(&hello_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
	layer_add_child(&window.layer, &hello_layer.layer);
  
	update_time();
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
	  .tick_info = {
		  .tick_handler = &handle_second_tick,
	  	  .tick_units = SECOND_UNIT
	  }
  };
  app_event_loop(params, &handlers);
}
