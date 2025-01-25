#include "Sprite.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "BankManager.h"

#include "asm/types.h"
#include "ZGBUtils.h"


// Copied from Scroll.h
#define SCREEN_TILES_H       DEVICE_SCREEN_HEIGHT
#if defined(MASTERSYSTEM)
#define SCREEN_TILES_W       (DEVICE_SCREEN_WIDTH - 1)
#else
#define SCREEN_TILES_W       DEVICE_SCREEN_WIDTH
#endif
#define SCREEN_WIDTH         (SCREEN_TILES_W << 3)
#define SCREEN_HEIGHT        (SCREEN_TILES_H << 3)

#define SCREEN_PAD_LEFT       1
#define SCREEN_PAD_RIGHT      2
#define SCREEN_PAD_TOP        1
#define SCREEN_PAD_BOTTOM     2

#define SCREEN_TILE_REFRES_W (SCREEN_TILES_W + SCREEN_PAD_LEFT + SCREEN_PAD_RIGHT)
#define SCREEN_TILE_REFRES_H (SCREEN_TILES_H + SCREEN_PAD_TOP  + SCREEN_PAD_BOTTOM)


// Jumps the map to a new location and repaints the entire screen
//   You can't use MoveScroll() since it's meant for small panning movements
//   and glitches with large jumps
void ScrollRelocateMapTo(UINT16 new_x, UINT16 new_y) {
	UINT8 __save = CURRENT_BANK;
    //scroll_x = new_x;
    //scroll_y = new_y;
	SWITCH_ROM(scroll_bank);
		INT16 y = scroll_y >> 3;
		for (UINT8 i = 0u; i != (SCREEN_TILE_REFRES_H) && y != scroll_h; ++i, y++) {
			ScrollUpdateRow((scroll_x >> 3) - SCREEN_PAD_LEFT,  y - SCREEN_PAD_TOP);
		}
	SWITCH_ROM(__save);
}