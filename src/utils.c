#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

char* fileGetContentStr(const char* path) {
	FILE* f = fopen(path, "r");
	if(!f) {
		return 0;
	}

	fseek(f, 0, SEEK_END);
	size_t sz = ftell(f);
	fseek(f, 0, SEEK_SET);

	char* str = malloc(sz + 1);
	size_t rd = fread(str, 1, sz, f);
	fclose(f);

	if(rd != sz) {
		free(str);
		return 0;
	}

	str[sz] = 0; // Null terminator
	return str;
}
