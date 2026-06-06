#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "grade.h"
#include "menu.h"
#include "input.h"
#include "store.h"

int
get_choice(int limitation) {
    int read_num = 1, input = 0;
    while (1) {
        if (read_num == 1 && input >= 0 && input <= limitation) {
            return input;
        } else {
            printf("输入错误，请重新输入！\n");
        }
        input = scanf("%d", &input);
        clear_stdin_buffer();
    }
}

int
confirm(const char *things_you_doing) {
	char prompt[MAX_SENTENCE_LENGTH];
	strncpy(prompt, things_you_doing, MAX_SENTENCE_LENGTH);
	char input[INTERVAL_LENGTH];
	printf("%s\n", prompt);
	printf("您确认要继续吗？输入“yes”以继续，输入其它任何内容退出：");
	get_line(input, INTERVAL_LENGTH);
	if (strcmp(input, "yes") == 0)
		return 1;
	return 0;
}

void show_menu() {
	printf("===== 学生成绩管理系统 =====\n"
	       "1. 添加学生\n"
	       "2. 删除学生\n"
	       "3. 修改学生\n"
	       "4. 查询学生\n"
	       "5. 显示所有学生\n"
	       "6. 统计排名 & 班级均分\n"
	       "7. 退出\n"
	       "============================\n"
	       );
}

void
read_grade(int *grade) {
	int ret = 1;
	do {
		if (ret < 1)
			printf("读取错误！请重新输入：");
		ret = scanf("%d", grade);
		clear_stdin_buffer();
	} while (ret != 1);
}

void
add_grade() {
	grade_record rcd;
	printf("请输入学号：");
	if (get_line(rcd.stu.stu_id, MAX_STU_ID_LENGTH) == NULL) {
		printf("读取输入出错！\n");
		return;
	}
	if (find_by_id(rcd.stu.stu_id) != -1) {
		printf("已存在该生信息！\n");
		return;
	}
	printf("请输入姓名：");
	if (get_line(rcd.stu.stu_name, MAX_STU_NAME_LENGTH) == NULL) {
		printf("读取输入出错！\n");
		return;
	}
	printf("请输入语文成绩：");
	read_grade(&rcd.chinese);
	printf("请输入数学成绩：");
	read_grade(&rcd.math);
	printf("请输入英语成绩：");
	read_grade(&rcd.english);
	calc_grade(&rcd);
	int location = insert_record(&rcd);
	if (location != -1) {
		printf("添加成功！\n");
		show_grade_title();
		show_record(location);
		write_to_file(&rcd);
	}
}

void
show_grade_title() {
	printf("%-*s\t%-*s\t%-*s\t%-*s\t%-*s\t%-*s\t%-s\n",
		MAX_STU_ID_LENGTH, "学号", MAX_STU_NAME_LENGTH, "姓名",
		INTERVAL_LENGTH, "语文", INTERVAL_LENGTH, "数学",
		INTERVAL_LENGTH, "英语", INTERVAL_LENGTH, "总分", "平均分");
}

void print_all_records() {
	show_grade_title();
	show_records();
}

void
modify_grade_record() {
	char input[MAX_STU_NAME_LENGTH];
	int location = -1;
	grade_record gcd;
	char choice[CHOICE_SIZE];
	do {
		printf("请输入学号(输入q退出)：");
		if (get_line(input, MAX_STU_ID_LENGTH) == NULL) {
			printf("读取输入出错，请重新输入。\n");
			continue;
		}
		location = find_by_id(input);
		if (location == -1) {
			printf("未查找到该生成绩！\n");
			continue;
		}
		get_record_by_index(location, &gcd);
		printf("将更改以下记录：\n");
		show_grade_title();
		show_record_entity(&gcd);
		printf("0. 姓名；1. 语文成绩；2. 数学成绩；3. 英语成绩\n"
			"请输入要修改的数据项：");
		if (get_line(choice, CHOICE_SIZE) != NULL) {
			int len = strlen(choice);
			for (int i = 0; i < len; i++) {
				switch(choice[i]) {
					case '0':
						printf("请输入新姓名：");
						if (get_line(input, MAX_STU_NAME_LENGTH)) {
							modify_student_name(&gcd.stu, input);
						} else {
							printf("姓名输入错误，修改未生效！\n");
						}
						break;
					case '1':
						printf("请输入新的语文成绩：");
						gcd.chinese = get_number();
						calc_grade(&gcd);
						break;
					case '2':
						printf("请输入新的数学成绩：");
						gcd.math = get_number();
						calc_grade(&gcd);
						break;
					case '3':
						printf("请输入新的英语成绩：");
						gcd.english = get_number();
						calc_grade(&gcd);
						break;
					default: ;
				}
			}
		}
		printf("修改后的成绩如下：\n");
		show_grade_title();
		show_record_entity(&gcd);
		if (confirm("正在修改成绩！")) {
			modify_record(location, &gcd);
		}
		strncpy(input, "q", MAX_STU_ID_LENGTH);
	} while (strcmp(input, "q") != 0);
}

void
delete_student() {
	char stu_id[MAX_STU_ID_LENGTH];
	int location = -1;
	while(1) {
		printf("请输入学号(输入q退出)：");
		if (get_line(stu_id, MAX_STU_ID_LENGTH) == NULL) {
			printf("读取输入出错，请重新输入。\n");
			continue;
		} else if (strcmp(stu_id, "q") == 0) {
			break;
		} else {
			location = find_by_id(stu_id);
			if (location == -1) {
				printf("未查询到相关结果，请重新输入！\n");
			} else {
				break;
			}
		}
	}
	if (location != -1) {
		if (delete_record(location)) {
			printf("删除成功！\n");
		}	
	}
}