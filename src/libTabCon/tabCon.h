#ifndef __TABCON__
#define __TABCON__

#define TABCON_LENGTH_HASH 20
#define TABCON_WIDTH 3
#define TABCON_HEIGHT 5
#define TABCON_PIXELS (TABCON_WIDTH * TABCON_HEIGHT)
#define TABCON_POSITION(_x, _y, _width) (_y * _width) + _x
#define TABCON_MIRRORWIDTH (TABCON_WIDTH + (TABCON_WIDTH - TABCON_WIDTH % 2))

typedef struct {
	unsigned char hash[TABCON_LENGTH_HASH];
	unsigned char data[TABCON_MIRRORWIDTH * TABCON_HEIGHT];
	unsigned char color[3];
} tabCon_t;

char tabCon_generate(
	tabCon_t *tabCon,
	const char *string
);

void tabCon_printHash(tabCon_t tabCon);

#endif