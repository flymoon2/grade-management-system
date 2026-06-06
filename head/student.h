#ifndef HEAD_STUDENT
#define HEAD_STUDENT

#include "constants.h"
#include <stdio.h>

typedef struct {
	char stu_id[MAX_STU_ID_LENGTH];
	char stu_name[MAX_STU_NAME_LENGTH];
} student;

void copy_student(const student* src, student* dest);
void add_student(student* stu, const char stu_id[], const char stu_name[]);
static inline void modify_student_name(student *stu, const char *name) {
	snprintf(stu->stu_name, sizeof(stu->stu_name), "%s", name);
}

#endif