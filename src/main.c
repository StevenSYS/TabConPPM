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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <tabCon.h>

#include "tabConToPPM.h"
#include "progInfo.h"

static char customFileName = 0;
static char filename[LENGTH_FILENAME];
static char hashString[LENGTH_HASHSTRING] = { 0 };
static char scale = DEFAULT_SCALE;

static tabCon_t tabCon;

#ifdef MISSING_L_FUNCS
	#define strlcpy(_src, _dst, _len) \
		strncpy(_src, _dst, _len - 1); \
		_src[sizeof(_src) - 1] = 0;
	#define strlcat(_src, _dst, _len) \
		strncat(_src, _dst, _len - 1); \
		_src[sizeof(_src) - 1] = 0;
#endif

char loadArgs(
	int argc,
	char *argv[]
) {
	for (int i = 0; i < argc; i++) {
		if (argv[i] != NULL) {
			switch (i) {
				case 0:
					break;
				case 1:
					if (strcmp(argv[i], "STRINGNAME") != 0) {
						if (strlen(argv[i]) < LENGTH_FILENAME) {
							customFileName = 1;
							strlcpy(
								filename,
								argv[i],
								LENGTH_FILENAME
							);
						}
					}
					break;
				case 2:
					if (atoi(argv[i]) > 0 && atoi(argv[i]) < 141) {
						scale = atoi(argv[i]);
					}
					break;
				default:
					if (i > 3) {
						strlcat(
							hashString,
							" ",
							LENGTH_HASHSTRING
						);
					}
					
					strlcat(
						hashString,
						argv[i],
						LENGTH_HASHSTRING
					);
					break;
			}
		}
	}
	
	if (!strlen(hashString)) {
		srand(time(NULL));
		char randomChar[2];
		for (unsigned char i = 0; i < 9; i++) {
			snprintf(randomChar, 2, "%u", rand() % 9);
			strlcat(
				hashString,
				randomChar,
				LENGTH_HASHSTRING
			);
		}
	}
	
	if (strlen(hashString) > LENGTH_HASHSTRING) {
		fprintf(stderr, "ERROR: Hash string is too long\n");
		return 1;
	}
	
	if (!customFileName) {
		strlcpy(
			filename,
			hashString,
			LENGTH_FILENAME
		);
	}
	
	strlcat(
		filename,
		".ppm",
		LENGTH_FILENAME
	);
	return 0;
}

int main(
	int argc,
	char *argv[]
) {
	printf(PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	printf("Created by StevenSYS\n");
	
	printf("- Loading arguments\n");
	
	if (loadArgs(argc, argv)) {
		return 1;
	}
	
	printf("- Loaded arguments\n");
	
	printf("- String: \"%s\"\n", hashString);
	printf("- Scale: %ux\n", scale);
	printf("- Output: \"%s\"\n", filename);
	
	printf("- Generating TabCon\n");
	
	tabCon_generate(&tabCon, hashString);
	
	printf("- Generated TabCon\n");
	printf("- Hash: \"");
	tabCon_printHash(tabCon);
	printf("\"\n");
	
	printf("- Making PPM file\n");
	
	if (tabConToPPM(
		filename,
		tabCon,
		scale,
		hashString
	)) {
		return 1;
	}
	
	printf("- Made PPM file\n");
	return 0;
}