#ifndef HEAD_GRADE
#define HEAD_GRADE


#include "constants.h"
#include "student.h"
#include <stddef.h>
#include <stdio.h>

typedef struct {
	double average;
	int chinese;
	int math;
	int english;
	int total;
	student stu;
} grade_record;

enum sort_key {
	SORT_BY_ID,
	SORT_BY_NAME,
	SORT_BY_TOTAL,
	SORT_BY_CHINESE,
	SORT_BY_MATH,
	SORT_BY_ENGLISH,
	SORT_BY_AVERAGE
};

enum sort_order {
	SORT_DESC,
	SORT_ASC
};

enum find_key {
	FIND_BY_ID,
	FIND_BY_NAME
};


static inline void
calc_grade(grade_record *rcd) {
	rcd->total = rcd->chinese + rcd->math + rcd->english;
	rcd->average = (rcd->total) / 3;
}

static inline void
show_record_entity(const grade_record *rcd) {
	printf("%-*s\t%-*s\t%-*d\t%-*d\t%-*d\t%-*d\t%-.2f\n",
			MAX_STU_ID_LENGTH,rcd->stu.stu_id,
			MAX_STU_NAME_LENGTH, rcd->stu.stu_name,
			INTERVAL_LENGTH, rcd->chinese,
			INTERVAL_LENGTH, rcd->math,
			INTERVAL_LENGTH, rcd->english,
			INTERVAL_LENGTH, rcd->total,
			rcd->average);
}

void copy_record(const grade_record *src, grade_record *dest);
grade_record *duplicate_records();
int initial_records();
int increse_capacity();
int lack_capacity();
int insert_record(grade_record *stu_grade);
int delete_record(int location);
int modify_record(int location, grade_record *stu_grade);
int get_record_by_index(int location, grade_record *stu_grade);
int find_by_id(const char *stu_id);
void clear_records();
int comp(grade_record* a, grade_record* b, enum sort_key sort_by, enum sort_order sort_in);
void quick_sort(grade_record* dest, size_t count, int (*comp)(grade_record*, grade_record*, enum sort_key, enum sort_order));
void show_records();
void show_record(int location);
void save_to_file();

#endif
