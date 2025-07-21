#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <tabCon.h>

#include "tabConToPPM.h"
#include "progInfo.h"

char customFileName = 0;
char filename[LENGTH_FILENAME];
char hashString[LENGTH_HASHSTRING] = { 0 };
char scale = DEFAULT_SCALE;

tabCon_t tabCon;

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
							strcpy(filename, argv[i]);
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
						strcat(hashString, " ");
					}
					strcat(hashString, argv[i]);
					break;
			}
		}
	}
	
	if (!strlen(hashString)) {
		srand(time(NULL));
		char randomChar[2];
		for (unsigned char i = 0; i < 9; i++) {
			snprintf(randomChar, 2, "%u", rand() % 9);
			strcat(hashString, randomChar);
		}
	}
	
	if (strlen(hashString) > LENGTH_HASHSTRING) {
		return 1;
	}
	
	if (!customFileName) {
		strcpy(filename, hashString);
	}
	
	strcat(filename, ".ppm");
	return 0;
}

int main(
	int argc,
	char *argv[]
) {
	printf(PROGRAM_NAME " v" PROGRAM_VERSION "\n");
	
	if (loadArgs(argc, argv)) {
		fprintf(stderr, "ERROR: Failed to load arguments\n");
		return 1;
	}
	
	printf("- String: \"%s\"\n", hashString);
	printf("- Scale: %ux\n", scale);
	
	printf("- Generating TabCon\n");
	
	if (tabCon_generate(&tabCon, hashString)) {
		fprintf(stderr, "ERROR: Failed to generate TabCon\n");
		return 1;
	}
	
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
		fprintf(stderr, "ERROR: Failed to make PPM file\n");
		return 1;
	}
	
	printf("- Made PPM file\n");
	printf("- Filename: \"%s\"\n", filename);
	return 0;
}