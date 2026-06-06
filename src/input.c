#include "input.h"
#include <stdio.h>
#include <string.h>

void clear_stdin_buffer(void) {
	int ch;
	while ( (ch = getchar()) != '\n' && ch != EOF);
}

char *
get_line(char *str, size_t size) {
	while (1) {
		if (fgets(str, size, stdin) == NULL) {
			return NULL;
		}
		size_t len = strlen(str);
		if (len > 0 && str[len - 1] == '\n') {
			str[len - 1] = '\0';
			return str;
		} else {
			clear_stdin_buffer();
			printf("输入过长(最多%zu个字符)，请重新输入：", size - 1);
		}
	}
}

int
get_number() {
	int read_num = 1, ret = 0;
	do {
		if (read_num < 1) {
			printf("输入错误，请重新输入：");
		}
		read_num = scanf("%d", &ret);
		clear_stdin_buffer();
	} while (read_num < 1);
	return ret;
}