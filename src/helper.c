#include <pebble.h>
#include <config.h>
#include "helper.h"

int hours = 0, minutes = 0;
GPoint corneaPos;

static float hourAngle(int hour){
	return (hour * 360) / 12;
}

static float minuteAngle(int minute){
	return (minute * 360) / 60;
}

void scleraProc(Layer *layer, GContext *ctx){
	GRect bounds = layer_get_bounds(layer);
	
	graphics_context_set_antialiased(ctx, true);
	graphics_context_set_fill_color(ctx, SCLERA_COLOR);
	graphics_fill_radial(ctx, bounds, GOvalScaleModeFitCircle, SCLERA_RADIUS, DEG_TO_TRIGANGLE(0), DEG_TO_TRIGANGLE(360));
}

void corneaProc(Layer *layer, GContext *ctx){
	GRect bounds = layer_get_bounds(layer);
	GRect frame = grect_inset(bounds, GEdgeInsets(CORNEA_INSET));
	GPoint pos = gpoint_from_polar(frame, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(hourAngle(hours)));
	
	corneaPos = pos;
	
	graphics_context_set_antialiased(ctx, true);
	
	graphics_context_set_fill_color(ctx, CORNEA_COLOR);
	graphics_fill_circle(ctx, pos, CORNEA_RADIUS);
}

void shineProc(Layer *layer, GContext *ctx){
	GRect frame = grect_inset(GRect(corneaPos.x - SHINE_RADIUS * 4, corneaPos.y - SHINE_RADIUS * 4, CORNEA_RADIUS * 2, CORNEA_RADIUS * 2), GEdgeInsets(SHINE_INSET));
	GPoint pos = gpoint_from_polar(frame, GOvalScaleModeFitCircle, DEG_TO_TRIGANGLE(minuteAngle(minutes)));
	
	graphics_context_set_antialiased(ctx, true);
	graphics_context_set_fill_color(ctx, SHINE_COLOR);
	graphics_fill_circle(ctx, pos, SHINE_RADIUS);
}

void smileProc(Layer *layer, GContext *ctx){
	GRect bounds = layer_get_bounds(layer);
	
	graphics_context_set_antialiased(ctx, true);
	graphics_context_set_stroke_color(ctx, SCLERA_COLOR);
	graphics_fill_radial(ctx, bounds, GOvalScaleModeFillCircle, 10, DEG_TO_TRIGANGLE(90), DEG_TO_TRIGANGLE(270));
}