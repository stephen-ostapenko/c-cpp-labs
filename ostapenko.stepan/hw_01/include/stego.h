#ifndef _STEGO_H_
#define _STEGO_H_

#include <stdint.h>
#include "bmp.h"

typedef struct key_s {
	int32_t x, y;
	char c;
} key;

int insert_msg(bmp *to, bmp *from, FILE *msg_in, FILE *key_in);

int extract_msg(bmp *p, FILE *key_in, FILE *msg_out);

#endif