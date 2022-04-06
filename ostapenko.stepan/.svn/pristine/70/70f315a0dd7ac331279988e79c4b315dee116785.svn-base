#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "stego.h"

int main(int argc, char **argv) {
	assert(argc >= 2);

	if (!strcmp(argv[1], "crop-rotate")) {
		assert(argc >= 8);

		FILE *bmp_in = fopen(argv[2], "rb");
		bmp orig;
		if (load_bmp(bmp_in, &orig)) {
			printf("Error! Memory is not allocated\n");

			fclose(bmp_in);

			return -1;
		}
		fclose(bmp_in);
		
		bmp cropped;
		int32_t x = atoi(argv[4]), y = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);
		if (crop(&cropped, &orig, x, y, w, h)) {
			printf("Error! Memory is not allocated\n");

			free_bmp(&orig);

			return -1;
		}

		bmp crop_rotated;
		if (rotate(&crop_rotated, &cropped)) {
			printf("Error! Memory is not allocated\n");

			free_bmp(&orig);
			free_bmp(&cropped);

			return -1;
		}

		FILE *bmp_out = fopen(argv[3], "wb");
		if (save_bmp(bmp_out, &crop_rotated)) {
			printf("Error! Memory is not allocated\n");

			fclose(bmp_out);
			
			free_bmp(&orig);
			free_bmp(&cropped);
			free_bmp(&crop_rotated);

			return -1;
		}
		fclose(bmp_out);

		free_bmp(&orig);
		free_bmp(&cropped);
		free_bmp(&crop_rotated);

	} else if (!strcmp(argv[1], "insert")) {
		assert(argc >= 6);

		FILE *bmp_in = fopen(argv[2], "rb");
		bmp orig;
		if (load_bmp(bmp_in, &orig)) {
			printf("Error! Memory is not allocated\n");

			fclose(bmp_in);

			return -1;
		}
		fclose(bmp_in);

		FILE *key_in = fopen(argv[4], "r");
		FILE *msg_in = fopen(argv[5], "r");
		bmp result;
		if (insert_msg(&result, &orig, msg_in, key_in)) {
			printf("Error! Memory is not allocated\n");

			fclose(msg_in);
			fclose(key_in);

			free_bmp(&orig);

			return -1;
		}
		fclose(msg_in);
		fclose(key_in);

		FILE *bmp_out = fopen(argv[3], "wb");
		if (save_bmp(bmp_out, &result)) {
			printf("Error! Memory is not allocated\n");

			fclose(bmp_out);

			free_bmp(&orig);
			free_bmp(&result);

			return -1;
		}
		fclose(bmp_out);

		free_bmp(&orig);
		free_bmp(&result);

	} else if (!strcmp(argv[1], "extract")) {
		assert(argc >= 5);

		FILE *bmp_in = fopen(argv[2], "rb");
		bmp orig;
		if (load_bmp(bmp_in, &orig)) {
			printf("Error! Memory is not allocated\n");

			fclose(bmp_in);

			return -1;
		}
		fclose(bmp_in);

		FILE *key_in = fopen(argv[3], "r");
		FILE *msg_out = fopen(argv[4], "w");
		if (extract_msg(&orig, key_in, msg_out)) {
			printf("Error! Memory is not allocated\n");

			fclose(key_in);
			fclose(msg_out);

			free_bmp(&orig);
			
			return -1;
		}
		fclose(key_in);
		fclose(msg_out);

		free_bmp(&orig);

	} else {
		printf("Error! Unknown option %s\n", argv[1]);
		return 1;
	}

	return 0;
}