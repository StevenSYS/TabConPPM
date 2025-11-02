/*
	MIT License
	
	Copyright (c) 2025 StevenSYS
	
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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

void tabCon_generate(
	tabCon_t *tabCon,
	const char *string,
	const unsigned int length
);

#endif