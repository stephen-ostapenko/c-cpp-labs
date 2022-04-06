#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "mergesort.h"

void merge(void *array, size_t element_size, size_t part1_size, void *part1, size_t part2_size, void *part2, int (*comparator)(const void*, const void*), void *buffer) {
	char *current_buffer = buffer;
	size_t overall_size = part1_size + part2_size;

	while (part1_size > 0 && part2_size > 0) {
		if (comparator(part1, part2) <= 0) {
			memcpy(current_buffer, part1, element_size);
			current_buffer += element_size;
			part1 = (char*)part1 + element_size;
			part1_size--;
		} else {
			memcpy(current_buffer, part2, element_size);
			current_buffer += element_size;
			part2 = (char*)part2 + element_size;
			part2_size--;
		}
	}

	if (part1_size) {
		memcpy(current_buffer, part1, part1_size * element_size);
	}
	if (part2_size) {
		memcpy(current_buffer, part2, part2_size * element_size);
	}

	memcpy(array, buffer, overall_size * element_size);
}

void mergesort_engine(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*), void *buffer) {
	if (elements <= 1) {
		return;
	}

	size_t part1_size = elements / 2;
	size_t part2_size = elements - part1_size;
	void *part1 = array;
	void *part2 = (char*)array + part1_size * element_size;

	mergesort_engine(part1, part1_size, element_size, comparator, buffer);
	mergesort_engine(part2, part2_size, element_size, comparator, buffer);

	merge(array, element_size, part1_size, part1, part2_size, part2, comparator, buffer);
}

int mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)) {
	void *buffer = malloc(elements * element_size);
	
	if (buffer == NULL) {
		return -1;
	}

	mergesort_engine(array, elements, element_size, comparator, buffer);

	free(buffer);
	return 0;
}