#include <stdio.h>
#include <tabCon.h>

#include "progInfo.h"

char tabConToPPM(
	char *filename,
	tabCon_t tabCon,
	unsigned char scale,
	char *string
) {
	FILE *file = fopen(filename, "wb");
	unsigned char pixel;
	
	if (file == NULL) {
		perror("ERROR: Failed to open PPM file (wb Mode)");
		return 1;
	}
	
	fprintf(file, "P6\n");
	fprintf(file, "# Generated with " PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	fprintf(file, "# String: %s\n", string);
	fprintf(file, "# Scale: %u\n", scale);
	fprintf(file, "# Original Filename: %s\n", filename);
	fprintf(
		file,
		"%u %u\n",
		TABCON_MIRRORWIDTH * scale, TABCON_HEIGHT * scale
	);
	fprintf(file, "255\n");
	
	for (unsigned short y = 0; y < TABCON_HEIGHT; y++) {
		for (unsigned char y2 = 0; y2 < scale; y2++) {
			for (unsigned short x = 0; x < TABCON_MIRRORWIDTH; x++) {
				for (unsigned char x2 = 0; x2 < scale; x2++) {
					for (unsigned char i = 0; i < 3; i++) {
						pixel = (
							tabCon.data[
								TABCON_POSITION(x, y, TABCON_MIRRORWIDTH)
							] ? tabCon.color[i] : 0xFF
						);
						fwrite(
							&pixel,
							1,
							sizeof(unsigned char),
							file
						);
					}
				}
			}
		}
	}
	return 0;
}