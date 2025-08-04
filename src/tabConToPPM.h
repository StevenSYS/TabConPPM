#ifndef __TABCONTOPPM__
#define __TABCONTOPPM__

#include <tabCon.h>

char tabConToPPM(
	const char *filename,
	const tabCon_t tabCon,
	const unsigned char scale,
	const char *string
);

#endif