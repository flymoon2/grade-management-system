#include "menu.h"
#include "input.h"
#include "grade.h"
#include "store.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	if (argc == 1) {
		if (!load_data_file(DEFAULT_FILEPATH)) {
			printf("%s: 出错了! 读取数据失败.\n", argv[0]);
			exit(8);
		}
	}
	else if (argc == 2) {
		if (!load_data_file(argv[1])) {
			printf("%s: 出错了！无法打开%s。\n", argv[0], argv[1]);
			exit(8);
		}
	} else {
		printf("用法: %s [<filepath>]\n", argv[0]);
		exit(8);
	}
	int choice;
	do {
		show_menu();
		printf("请输入您的选项：");
		while ((scanf("%d", &choice)) != 1) {
			printf("请重新输入：");
			clear_stdin_buffer();
		}
		clear_stdin_buffer();
		switch(choice) {
			case 1: 
				add_grade();
				break;
			case 2: 
				delete_student();
				break;
			case 3: break;
			case 4: break;
			case 5: 
				print_all_records();
				break;
			case 6: break;
			case 7: 
				save_to_file();
				printf("再见~\n");
				break;
			default: break;
		}
	} while(choice != 7);

	return 0;
}
