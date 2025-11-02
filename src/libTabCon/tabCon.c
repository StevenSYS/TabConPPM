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

#include "sha1/sha1.h"
#include "tabCon.h"

void tabCon_generate(
	tabCon_t *tabCon,
	const char *string,
	const int length
) {
	unsigned char x, y, i;
	
	/* Calculate hash */
	SHA1_CTX context;
	
	SHA1Init(&context);
	SHA1Update(
		&context,
		(const unsigned char *)string,
		length
	);
	SHA1Final(tabCon->hash, &context);
	
	/* Convert hash to image */
	for (y = 0; y < TABCON_HEIGHT; y++) {
		for (x = 0; x < TABCON_WIDTH; x++) {
			tabCon->data[
				TABCON_POSITION(x, y, TABCON_MIRRORWIDTH)
			] = tabCon->data[
				TABCON_POSITION(
					(TABCON_MIRRORWIDTH - 1) - x,
					y,
					TABCON_MIRRORWIDTH
				)
			] = tabCon->hash[
				TABCON_POSITION(x, y, TABCON_WIDTH)
			] % 2;
		}
	}
	
	/* Set image color */
	for (i = TABCON_PIXELS; i < TABCON_PIXELS + 3; i++) {
		tabCon->color[i - TABCON_PIXELS] = tabCon->hash[i];
	}
	return;
}