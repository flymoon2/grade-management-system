#include "student.h"
#include <stdio.h>

void copy_student(const student* src, student* dest) {
	snprintf(dest->stu_id, sizeof(src->stu_id), "%s", src->stu_id);
	snprintf(dest->stu_name, sizeof(src->stu_name), "%s", src->stu_name);
}

void add_student(student* stu, const char stu_id[], const char stu_name[]) {
	snprintf(stu->stu_id, sizeof(stu->stu_id), "%s", stu_id);
	snprintf(stu->stu_name, sizeof(stu->stu_name), "%s", stu_name);
}