#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "clist.h"
#include "point_list.h"

typedef unsigned char byte;

static const size_t BYTES_COUNT = 3;
static const size_t BITS_IN_BYTE = 8;
static const int FULL_MASK = (1 << 8) - 1;
static const int CHANGE_GREATEST_BIT_MASK = (1 << 7);
static const int SIGN_SHIFT = (1 << 23);

static int get_int_from_bytes(byte *bytes) {
	int result = 0, sign = 0;

	if (bytes[BYTES_COUNT - 1] >> (BITS_IN_BYTE - 1)) {
		sign = 1;
		bytes[BYTES_COUNT - 1] ^= CHANGE_GREATEST_BIT_MASK;
	}

	for (size_t i = 0; i < BYTES_COUNT; i++) {
		result <<= BITS_IN_BYTE;
		result |= bytes[BYTES_COUNT - i - 1];
	}

	if (sign) {
		result -= SIGN_SHIFT;
	}

	return result;
}

static void get_bytes_from_int(int number, byte *bytes) {
	int sign = 0;

	if (number < 0) {
		sign = 1;
		number += SIGN_SHIFT;
	}

	for (size_t i = 0; i < BYTES_COUNT; i++) {
		bytes[i] = number & FULL_MASK;
		number >>= BITS_IN_BYTE;
	}

	if (sign) {
		bytes[BYTES_COUNT - 1] ^= CHANGE_GREATEST_BIT_MASK;
	}

}

static void read_points_from_text_file(FILE *file, struct intrusive_list *list) {
	int x, y;
		
	while (!feof(file) && fscanf(file, "%d %d", &x, &y) == 2) {
		add_point(list, x, y);
	}
}

static void read_points_from_bin_file(FILE *file, struct intrusive_list *list) {
	while (!feof(file)) {
		byte buffer[BYTES_COUNT];

		if (!fread(buffer, 1, BYTES_COUNT, file)) {
			break;
		}
		int x = get_int_from_bytes(buffer);
		if (!fread(buffer, 1, BYTES_COUNT, file)) {
			break;
		}
		int y = get_int_from_bytes(buffer);

		add_point(list, x, y);
	}
}

static void print_points_to_text_file(struct intrusive_node *node, void *file) {
	struct point *current_point = container_of(node, struct point, node);
	fprintf((FILE*)file, "%d %d\n", current_point->x, current_point->y);
}

static void print_points_to_bin_file(struct intrusive_node *node, void *file) {
	struct point *current_point = container_of(node, struct point, node);
	byte buffer[BYTES_COUNT];

	get_bytes_from_int(current_point->x, buffer);
	fwrite(buffer, 1, BYTES_COUNT, (FILE*)file);
	get_bytes_from_int(current_point->y, buffer);
	fwrite(buffer, 1, BYTES_COUNT, (FILE*)file);
}

int main(int argc, char **argv) {
	assert(argc >= 4);

	struct intrusive_list list;
	init_list(&list);
	FILE *fin = fopen(argv[2], "r");

	if (fin == NULL) {
		printf("Input file not found!!!\n");
		return 0;
	}

	if (!strcmp(argv[1], "loadtext")) {
		read_points_from_text_file(fin, &list);
	} else {
		read_points_from_bin_file(fin, &list);
	}

	fclose(fin);

	if (!strcmp(argv[3], "savetext")) {
		assert(argc >= 5);

		FILE *fout = fopen(argv[4], "w");
		apply(&list, print_points_to_text_file, fout);
		fclose(fout);
	}

	if (!strcmp(argv[3], "savebin")) {
		assert(argc >= 5);

		FILE *fout = fopen(argv[4], "w");
		apply(&list, print_points_to_bin_file, fout);
		fclose(fout);
	}

	if (!strcmp(argv[3], "print")) {
		assert(argc >= 5);

		apply(&list, print, argv[4]);
		printf("\n");
	}

	if (!strcmp(argv[3], "count")) {
		size_t result = 0;
		apply(&list, count, &result);
		printf("%d\n", (int)result);
	}

	remove_all_points(&list);

	return 0;
}
