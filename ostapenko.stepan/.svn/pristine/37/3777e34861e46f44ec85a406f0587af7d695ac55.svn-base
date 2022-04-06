#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int int_lt_comparator(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

int char_lt_comparator(const void *a, const void *b) {
	return *(char*)a - *(char*)b;
}

int string_lt_comparator(const void *a, const void *b) {
	return strcmp(*(char**)a, *(char**)b);
}

void print_int_array(int *array, size_t size) {
	if (size) {
		printf("%d", array[0]);
	}
	for (size_t i = 1; i < size; i++) {
		printf(" %d", array[i]);
	}
	printf("\n");
}

void print_char_array(char *array, size_t size) {
	if (size) {
		printf("%c", array[0]);
	}
	for (size_t i = 1; i < size; i++) {
		printf(" %c", array[i]);
	}
	printf("\n");
}

void print_string_array(char **array, size_t size) {
	if (size) {
		printf("%s", array[0]);
	}
	for (size_t i = 1; i < size; i++) {
		printf(" %s", array[i]);
	}
	printf("\n");
}

void error() {
	printf("Error: memory allocation failed.\n");
}

int main(int argc, char **argv) {
	size_t elements_count = argc - 2;

	if (!elements_count) {
		printf("\n");
		return 0;
	}

	if (!strcmp(argv[1], "int")) {
		int *arr = malloc(elements_count * sizeof(int));

		if (arr == NULL) {
			error(); return 0;
		}

		for (int i = 2; i < argc; i++) {
			arr[i - 2] = atoi(argv[i]);
		}

		if (mergesort(arr, elements_count, sizeof(int), int_lt_comparator)) {
			error();
		} else {
			print_int_array(arr, elements_count);
		}

		free(arr);
	}

	if (!strcmp(argv[1], "char")) {
		char *arr = malloc(elements_count * sizeof(char));

		if (arr == NULL) {
			error(); return 0;
		}

		for (int i = 2; i < argc; i++) {
			arr[i - 2] = argv[i][0];
		}

		if (mergesort(arr, elements_count, sizeof(char), char_lt_comparator)) {
			error();
		} else {
			print_char_array(arr, elements_count);
		}

		free(arr);
	}

	if (!strcmp(argv[1], "str")) {
		if (mergesort(argv + 2, elements_count, sizeof(char*), string_lt_comparator)) {
			error();
		} else {
			print_string_array(argv + 2, elements_count);
		}
	}

	return 0;
}