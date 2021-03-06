#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "stego.h"

static const int32_t CHAR_SIZE = 5;

static uint8_t get_bit(uint8_t x) {
	return x & 1;
}

static void set_bit(uint8_t *x, uint8_t b) {
	*x = (*x | (uint8_t)1) ^ ((uint8_t)1 ^ b);
}

static uint8_t get_number_by_char(char c) {
	if ('A' <= c && c <= 'Z') {
		return c - 'A';
	} else if (c == ' ') {
		return 26;
	} else if (c == '.') {
		return 27;
	} else if (c == ',') {
		return 28;
	}
	assert(0);
}

static char get_char_by_number(uint8_t x) {
	if (x < 26) {
		return 'A' + x;
	} else if (x == 26) {
		return ' ';
	} else if (x == 27) {
		return '.';
	} else if (x == 28) {
		return ',';
	}
	assert(0);
}

static int32_t read_next_key(FILE *file, key *k) {
	for (int32_t i = 0; i < CHAR_SIZE; i++) {
		if (fscanf(file, "%d %d %c", &k[i].x, &k[i].y, &k[i].c) == EOF) {
			return 0;
		}
	}
	return 1;
}

static void insert_next_char(bmp *p, char c, key *k) {
	uint8_t code = get_number_by_char(c);

	for (int32_t i = 0; i < CHAR_SIZE; i++, code >>= 1) {
		if (k[i].c == 'R') {
			set_bit(&p->picture[k[i].y][k[i].x].r, get_bit(code));
		} else if (k[i].c == 'G') {
			set_bit(&p->picture[k[i].y][k[i].x].g, get_bit(code));
		} else if (k[i].c == 'B') {
			set_bit(&p->picture[k[i].y][k[i].x].b, get_bit(code));
		}
	}
}

int insert_msg(bmp *to, bmp *from, FILE *msg_in, FILE *key_in) {
	memcpy(&to->header, &from->header, sizeof(file_header));
	memcpy(&to->info, &from->info, sizeof(info_header));
	
	int32_t width = from->info.width, height = from->info.height;
	if (alloc_bmp(to, width, height)) {
		return -1;
	}

	memcpy(to->body, from->body, width * height * sizeof(pixel));
	memcpy(to->picture, from->picture, height * sizeof(pixel*));
	
	char c;
	key *k = malloc(CHAR_SIZE * sizeof(key));
	if (k == NULL) {
		free_bmp(to);
		return -1;
	}

	while (fscanf(msg_in, "%c", &c) != EOF && (!isspace(c) || c == ' ')) {
		read_next_key(key_in, k);
		insert_next_char(to, c, k);
	}

	free(k);

	return 0;
}

static char extract_next_char(bmp *p, key *k) {
	uint8_t result = 0;

	for (int32_t i = CHAR_SIZE - 1; i >= 0; i--) {
		result <<= 1;

		if (k[i].c == 'R') {
			set_bit(&result, get_bit(p->picture[k[i].y][k[i].x].r));
		} else if (k[i].c == 'G') {
			set_bit(&result, get_bit(p->picture[k[i].y][k[i].x].g));
		} else if (k[i].c == 'B') {
			set_bit(&result, get_bit(p->picture[k[i].y][k[i].x].b));
		}
	}

	return get_char_by_number(result);
}

int extract_msg(bmp *p, FILE *key_in, FILE *msg_out) {
	key *k = malloc(CHAR_SIZE * sizeof(key));
	if (k == NULL) {
		return -1;
	}

	while (read_next_key(key_in, k)) {
		fprintf(msg_out, "%c", extract_next_char(p, k));
	}
	fprintf(msg_out, "\n");

	free(k);

	return 0;
}