#ifndef HEAD_STUDENT
#define HEAD_STUDENT

#include "constants.h"

typedef struct {
	char stu_id[MAX_STU_ID_LENGTH];
	char stu_name[MAX_STU_NAME_LENGTH];
} student;

void copy_student(const student* src, student* dest);
void add_student(student* stu, const char stu_id[], const char stu_name[]);


#endif
