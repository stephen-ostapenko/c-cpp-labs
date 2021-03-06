#ifndef _BMP_H_
#define _BMP_H_

#include <stdint.h>

typedef struct file_header_s {
	uint16_t type;
	uint32_t size;
	uint16_t res1;
	uint16_t res2;
	uint32_t offset;
} file_header;

typedef struct info_header_s {
	uint32_t info_size;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bit_count;
	uint32_t compression;
	uint32_t picture_size;
	int32_t x_pels;
	int32_t y_pels;
	uint32_t clr_used;
	uint32_t clr_important;
} info_header;

#pragma pack(push, 1)
typedef struct pixel_s {
	uint8_t b, g, r;
} pixel;
#pragma pack(pop)

typedef struct bmp_s {
	file_header header;
	info_header info;
	pixel **picture;
	pixel *body;
} bmp;

int alloc_bmp(bmp *p, int32_t width, int32_t height);

int load_bmp(FILE *file, bmp *p);

// Crop $b$ and write result into $a$.
int crop(bmp *a, bmp *b, int32_t x, int32_t y, int32_t width, int32_t height);

// Rotate $b$ and write result into $a$.
int rotate(bmp *a, bmp *b);

int save_bmp(FILE *file, bmp *p);

void free_bmp(bmp *p);

#endif