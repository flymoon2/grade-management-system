#include "input.h"
#include <stdio.h>
#include <string.h>

void clear_stdin_buffer(void) {
	int ch;
	while ( (ch = getchar()) != '\n' && ch != EOF);
}

char *
get_line(char *str, size_t size) {
	if (fgets(str, size, stdin) == NULL)
		return NULL;
	size_t len = strlen(str);
	if (len > 0 && str[len - 1] == '\n') {
		str[len - 1] = '\0';
	} else {
		clear_stdin_buffer();
	}
	return str;
}
