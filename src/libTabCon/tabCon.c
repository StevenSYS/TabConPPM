#include <stdio.h>
#include <string.h>
#include <sha1/sha1.h>

#include "tabCon.h"

char tabCon_generate(
	tabCon_t *tabCon,
	const char *string
) {
	/* Calculate hash */
	SHA1_CTX context;
	
	SHA1Init(&context);
	SHA1Update(
		&context,
		(const unsigned char *)string,
		strlen(string)
	);
	SHA1Final(tabCon->hash, &context);
	
	/* Convert hash to image */
	for (unsigned char y = 0; y < TABCON_HEIGHT; y++) {
		for (unsigned char x = 0; x < TABCON_WIDTH; x++) {
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
	
	for (unsigned char i = TABCON_PIXELS; i < TABCON_PIXELS + 3; i++) {
		tabCon->color[i - TABCON_PIXELS] = tabCon->hash[i];
	}
	return 0;
}

void tabCon_printHash(tabCon_t tabCon) {
	for (unsigned char i = 0; i < TABCON_LENGTH_HASH; i++) {
		printf("%02x", tabCon.hash[i]);
	}
	return;
}