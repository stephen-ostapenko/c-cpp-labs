#include "str.h"

char *my_strcpy(char *s1, char *s2) {
	char *orig = s1;
	
	while ((*s1++) = (*s2++));
	
	return orig;
}

char *my_strcat(char *s1, char *s2) {
	char *orig = s1;
	
	while (*s1) {
		s1++;
	}
	my_strcpy(s1, s2);

	return orig;
}

int my_strcmp(char *s1, char *s2) {
	while (*s1 && *s1 == *s2) {
		s1++; s2++;
	}

	return *s1 - *s2;
}

size_t my_strlen(char *s) {
	size_t ans = 0;
	while (*s++) {
		ans++;
	}

	return ans;
}