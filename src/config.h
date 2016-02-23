#include <pebble.h>

// Let user choose background
#ifndef BACKGROUND_COLOR
#define BACKGROUND_COLOR 0x555555
#endif

#if PBL_PLATFORM_CHALK
#define WIDTH 180
#define HEIGHT 180
#else
#define WIDTH 144
#define HEIGHT 168
#endif

#define SCLERA_RADIUS 50
#define CORNEA_RADIUS SCLERA_RADIUS * 0.5
#define SHINE_RADIUS CORNEA_RADIUS * 0.25

#define CORNEA_INSET CORNEA_RADIUS
#define SHINE_INSET SHINE_RADIUS

#define SCLERA_COLOR GColorWhite
#define CORNEA_COLOR GColorBlack
#define SHINE_COLOR GColorWhite

#define MOUTH_COLOR GColorBlack