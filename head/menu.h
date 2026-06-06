#ifndef HEAD_MENU
#define HEAD_MENU

#include "constants.h"
#include "input.h"

int get_choice(int limitation);
void show_menu();
void read_grade();
void add_grade();
void show_grade_title();
void print_all_records();
void delete_student();
void modify_grade_record();
int confirm(const char *things_you_doing);


#endif
