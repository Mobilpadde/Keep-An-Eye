#include <pebble.h>
#include <config.h>
#include "helper.h"

static Window *mainWindow;
static Layer *scleraLayer, *corneaLayer, *shineLayer, *smileLayer;

static void updateTime(){
	time_t tmp = time(NULL);
	struct tm *tick = localtime(&tmp);
	
	int hoursBefore = hours, minutesBefore = minutes;
	
	hours = tick->tm_hour;
	minutes = tick->tm_min;
	
	if(hoursBefore != hours) layer_mark_dirty(corneaLayer);
	if(minutesBefore != minutes) layer_mark_dirty(shineLayer);
}

static void tickHandler(struct tm *tick, TimeUnits unitsChanged){
	updateTime();
}

static void mainWindowLoad(Window *window){
	window_set_background_color(window, BACKGROUND_COLOR);
	
	Layer *mainLayer = window_get_root_layer(window);
	
	GRect scleraRect = GRect(WIDTH / 2 - SCLERA_RADIUS, HEIGHT / 2 - SCLERA_RADIUS * 1.6, SCLERA_RADIUS * 2, SCLERA_RADIUS * 2);
	scleraLayer = layer_create(scleraRect);
	
	GRect corneaFrame = grect_inset(layer_get_frame(scleraLayer), GEdgeInsets(0));
	corneaLayer = layer_create(corneaFrame);
	
	GRect shineFrame = grect_inset(layer_get_frame(corneaLayer), GEdgeInsets(0));
	shineLayer = layer_create(shineFrame);
	
	GRect mouthRect = GRect(WIDTH / 2 - SCLERA_RADIUS, HEIGHT / 2 - SCLERA_RADIUS * 0.5, SCLERA_RADIUS * 2, SCLERA_RADIUS * 2);
	smileLayer = layer_create(mouthRect);
	
	layer_add_child(mainLayer, scleraLayer);
	layer_add_child(mainLayer, corneaLayer);
	layer_add_child(mainLayer, shineLayer);
	layer_add_child(mainLayer, smileLayer);
	
	layer_set_update_proc(corneaLayer, corneaProc);
	layer_set_update_proc(shineLayer, shineProc);
	layer_set_update_proc(scleraLayer, scleraProc);
	layer_set_update_proc(smileLayer, smileProc);
}

static void mainWindowUnload(Window *window){
	layer_destroy(scleraLayer);
	layer_destroy(corneaLayer);
	layer_destroy(shineLayer);
	
	layer_destroy(smileLayer);
}

void init(void) {
	mainWindow = window_create();
	
	window_set_window_handlers(mainWindow, (WindowHandlers) {
		.load = mainWindowLoad,
		.unload = mainWindowUnload
	});
	
	window_stack_push(mainWindow, true);
	
	updateTime();
	tick_timer_service_subscribe(MINUTE_UNIT, tickHandler);
}

void deinit(void) {
	window_destroy(mainWindow);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
