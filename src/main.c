#include <genesis.h>
#include <string.h>
#include <resources.h>

// --START Constants

// Integers / Floats
const int scrollspeed = 1;

// Text

char msg_start[22] = "Press START to begin.";
char msg_reset[22] = "Press START to reset.";

// Bool
bool game_on = FALSE;

// --END constants
// Functions

// Text Functions
void showText(char s[]) {
    VDP_drawText(s, strlen(s)/2,10);
}

void clearText() {
    VDP_clearText(0,10,32);
}

// Game state functions

void startGame(){
	if(game_on == FALSE){
		game_on = TRUE;
		clearText();
	}
}

void endGame(){
	if(game_on == TRUE){
		showText(msg_reset);
		game_on = FALSE;
	}
}

// Joypad handler
void myJoyHandler( u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1)
	{
		/*Start game if START is pressed*/
		if (state & BUTTON_START)
		{
			if(game_on == FALSE){
				startGame();
			}
		}
		if (state & BUTTON_C)
		{
			// I'm guessing this will be the bit that makes the little dude jump
		}
	}
}

// Main Function
int main() {
	//Input initializer
	JOY_init();
	JOY_setEventHandler( &myJoyHandler );

    // START init tiles/sprites
    VDP_setPaletteColor(0,RGB24_TO_VDPCOLOR(0x6dc2ca)); // helper function allows use of RBG24 Hex codes (same as HTML)
    VDP_setPlanSize(32,32);
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE); 
    VDP_loadTileSet(floor.tileset,1,DMA);
    VDP_loadTileSet(wall.tileset,2,DMA);
    VDP_loadTileSet(light.tileset,3,DMA); // auto-split this into 6 tiles (3-8)
    VDP_setPalette(PAL1, light.palette->data);
    //VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),1,1);
    //VDP_setTileMapXY(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,TRUE,2),1,2);
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,1),0,16,32,1);
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1,0,FALSE,TRUE,2),0,17,32,14);

    VDP_fillTileMapRectInc(BG_B,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE,3),15,13,2,3); // draw the light post

    //END init tiles/sprites

	// showText(msg_start);
    int offset = 0;
    while(1) {
        VDP_setHorizontalScroll(BG_B, offset -= scrollspeed);
        if (offset <= -256) offset = 0;

    }
    SYS_doVBlankProcess();
}
