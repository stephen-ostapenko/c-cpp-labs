#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

static const uint32_t HEADER_SIZE = 14;
static const uint32_t INFO_SIZE = 40;

static void read_file_header(FILE *file, file_header *header) {
	fread(&header->type, sizeof(header->type), 1, file);
	fread(&header->size, sizeof(header->size), 1, file);
	fread(&header->res1, sizeof(header->res1), 1, file);
	fread(&header->res2, sizeof(header->res2), 1, file);
	fread(&header->offset, sizeof(header->offset), 1, file);
}

static void read_info_header(FILE *file, info_header *info) {
	fread(&info->info_size, sizeof(info->info_size), 1, file);
	fread(&info->width, sizeof(info->width), 1, file);
	fread(&info->height, sizeof(info->height), 1, file);
	fread(&info->planes, sizeof(info->planes), 1, file);
	fread(&info->bit_count, sizeof(info->bit_count), 1, file);
	fread(&info->compression, sizeof(info->compression), 1, file);
	fread(&info->picture_size, sizeof(info->picture_size), 1, file);
	fread(&info->x_pels, sizeof(info->x_pels), 1, file);
	fread(&info->y_pels, sizeof(info->y_pels), 1, file);
	fread(&info->clr_used, sizeof(info->clr_used), 1, file);
	fread(&info->clr_important, sizeof(info->clr_important), 1, file);
}

static void write_file_header(FILE *file, file_header *header) {
	fwrite(&header->type, sizeof(header->type), 1, file);
	fwrite(&header->size, sizeof(header->size), 1, file);
	fwrite(&header->res1, sizeof(header->res1), 1, file);
	fwrite(&header->res2, sizeof(header->res2), 1, file);
	fwrite(&header->offset, sizeof(header->offset), 1, file);
}

static void write_info_header(FILE *file, info_header *info) {
	fwrite(&info->info_size, sizeof(info->info_size), 1, file);
	fwrite(&info->width, sizeof(info->width), 1, file);
	fwrite(&info->height, sizeof(info->height), 1, file);
	fwrite(&info->planes, sizeof(info->planes), 1, file);
	fwrite(&info->bit_count, sizeof(info->bit_count), 1, file);
	fwrite(&info->compression, sizeof(info->compression), 1, file);
	fwrite(&info->picture_size, sizeof(info->picture_size), 1, file);
	fwrite(&info->x_pels, sizeof(info->x_pels), 1, file);
	fwrite(&info->y_pels, sizeof(info->y_pels), 1, file);
	fwrite(&info->clr_used, sizeof(info->clr_used), 1, file);
	fwrite(&info->clr_important, sizeof(info->clr_important), 1, file);
}

static int32_t get_align(int32_t width) {
	return (3 * width + 3) / 4 * 4 - width * 3;
}

static void fix_header_and_info(bmp *p, int32_t width, int32_t height) {
	p->info.width = width;
	p->info.height = height;
	p->info.picture_size = (width * sizeof(pixel) + get_align(width)) * height;
	p->header.size = HEADER_SIZE + INFO_SIZE + p->info.picture_size;
}

int alloc_bmp(bmp *p, int32_t width, int32_t height) {
	p->body = malloc(width * height * sizeof(pixel));
	if (p->body == NULL) {
		return -1;
	}

	p->picture = malloc(height * sizeof(pixel*));
	if (p->picture == NULL) {
		free(p->body);
		return -1;
	}

	for (int i = 0; i < height; i++) {
		p->picture[i] = p->body + i * width;
	}

	return 0;
}

int load_bmp(FILE *file, bmp *p) {
	read_file_header(file, &p->header);
	read_info_header(file, &p->info);

	int32_t width = p->info.width, height = p->info.height;
	if (alloc_bmp(p, width, height)) {
		return -1;
	}
	
	int32_t offset = get_align(width);
	for (int32_t i = height - 1; i >= 0; i--) {
		fread(p->picture[i], sizeof(pixel), width, file);
		fseek(file, offset, SEEK_CUR);
	}

	return 0;
}

// Crop $b$ and write result into $a$.
int crop(bmp *a, bmp *b, int32_t x, int32_t y, int32_t width, int32_t height) {
	memcpy(&a->header, &b->header, sizeof(file_header));
	memcpy(&a->info, &b->info, sizeof(info_header));
	
	if (alloc_bmp(a, width, height)) {
		return -1;
	}

	fix_header_and_info(a, width, height);

	for (int32_t i = y; i < y + height; i++) {
		memcpy(a->picture[i - y], b->picture[i] + x, width * sizeof(pixel));
	}

	return 0;
}

// Rotate $b$ and write result into $a$.
int rotate(bmp *a, bmp *b) {
	memcpy(&a->header, &b->header, sizeof(file_header));
	memcpy(&a->info, &b->info, sizeof(info_header));
	
	int32_t width = b->info.width, height = b->info.height;
	if (alloc_bmp(a, height, width)) {
		return -1;
	}

	fix_header_and_info(a, height, width);

	for (int32_t i = 0; i < height; i++) {
		for (int32_t j = 0; j < width; j++) {
			memcpy(&a->picture[j][height - i - 1], &b->picture[i][j], sizeof(pixel));
		}
	}

	return 0;
}

int save_bmp(FILE *file, bmp *p) {
	write_file_header(file, &p->header);
	write_info_header(file, &p->info);

	int32_t width = p->info.width, height = p->info.height;
	int32_t offset = get_align(width);
	uint8_t align[offset];
	memset(align, 0, offset * sizeof(*align));

	for (int32_t i = height - 1; i >= 0; i--) {
		fwrite(p->picture[i], sizeof(pixel), width, file);
		fwrite(align, sizeof(uint8_t), offset, file);
	}

	return 0;
}

void free_bmp(bmp *p) {
	free(p->body); free(p->picture);
}