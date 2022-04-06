#include <assert.h>
#include <string.h>
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

int main() {

	{
		int bytes = 7 * sizeof(int);
		
		int arr[7] = {7, 3, 2, 1, 6, 4, 5};
		int *brr = malloc(bytes);
		memcpy(brr, arr, bytes);

		assert(!mergesort(arr, 7, sizeof(int), int_lt_comparator));
		qsort(brr, 7, sizeof(int), int_lt_comparator);
		
		assert(!memcmp(arr, brr, bytes));

		free(brr);
	}

	{
		int bytes = 6 * sizeof(char);
		
		char arr[6] = {'e', 'b', 'g', 'd', 'a', 'e'};
		char *brr = malloc(bytes);
		memcpy(brr, arr, bytes);
		
		assert(!mergesort(arr, 6, sizeof(char), char_lt_comparator));
		qsort(brr, 6, sizeof(char), char_lt_comparator);
		
		assert(!memcmp(arr, brr, bytes));

		free(brr);
	}

	{
		int bytes = 5 * sizeof(char*);
		
		char *arr[5] = {"foo", "abacaba", "kek", "abracadabra", "lol"};
		char **brr = malloc(bytes);
		for (int i = 0; i < 5; i++) {
			brr[i] = malloc(strlen(arr[i]) * sizeof(char) + 1);
			strcpy(brr[i], arr[i]);
		}
		
		assert(!mergesort(arr, 5, sizeof(char*), string_lt_comparator));
		qsort(brr, 5, sizeof(char*), string_lt_comparator);
		
		for (int i = 0; i < 5; i++) {
			assert(!strcmp(arr[i], brr[i]));
		}

		for (int i = 0; i < 5; i++) {
			free(brr[i]);
		}
		free(brr);
	}

	return 0;
}