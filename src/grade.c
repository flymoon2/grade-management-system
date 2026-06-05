#include "grade.h"
#include "menu.h"
#include "student.h"
#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static grade_record* records = NULL;
static int record_count = 0;
static int record_capacity = 0;

void
calc_grade(grade_record *rcd) {
	rcd->total = rcd->chinese + rcd->math + rcd->english;
	rcd->average = rcd->total / 3.0;
}

void
copy_record(const grade_record* src, grade_record* dest) {
	copy_student(&src->stu, &dest->stu);
	dest->chinese = src->chinese;
	dest->math = src->math;
	dest->english = src->english;
	dest->total = src->total;
	dest->average = src->average;
}

int
find_by_id(const char *stu_id) {
	for (int i = 0; i < record_count; i++) {
		if (strcmp(records[i].stu.stu_id, stu_id) == 0)
			return i;
	}
	return -1;
}

int
comp(grade_record* a, grade_record* b, enum sort_key sort_by, enum sort_order sort_in) {
	switch (sort_by) {
		case SORT_BY_ID:
			return sort_in && strcmp(a->stu.stu_id, b->stu.stu_id) <= 0;
		case SORT_BY_NAME:
			return sort_in && strcmp(a->stu.stu_name, b->stu.stu_name) <= 0;
		case SORT_BY_TOTAL:
			return sort_in && a->total <= b->total;
		case SORT_BY_CHINESE:
			return sort_in && a->chinese <= b->chinese;
		case SORT_BY_MATH:
			return sort_in && a->math <= b->math;
		case SORT_BY_ENGLISH:
			return sort_in && a->english <= b->english;
		case SORT_BY_AVERAGE:
			return sort_in && a->average <= b->average;
	}	
	return 1;
}

void
quick_sort(grade_record* dest, size_t count, int (*comp)(grade_record*, grade_record*, enum sort_key, enum sort_order)) {
	if (count <= 1)
		return;
	int pivot = count / 2;
	grade_record rcd;
	copy_record(dest + pivot, &rcd);
	copy_record(dest, dest + pivot);
	int left = 0, right = count - 1;
	while (left < right) {
		while (left < right && comp(&rcd, dest + right, SORT_BY_TOTAL, SORT_ASC))
			right--;
		if (left < right)
			copy_record(dest + right, dest + left);
		while (left < right && comp(dest + left, &rcd, SORT_BY_TOTAL, SORT_ASC))
			left++;
		if (left < right)
			copy_record(dest + left, dest + right);
	}
	copy_record(&rcd, dest + left);
	quick_sort(dest, left, comp);
	quick_sort(dest + left + 1, count - left - 1, comp);
}

void
clear_records() {
	if (records) 
		free(records);
	records = NULL;
	record_count = 0;
	record_capacity = 0;
}

grade_record*
duplicate_records(size_t* size) {
	grade_record *ret = NULL;
	ret = malloc(sizeof(grade_record) * record_count);
	if (ret) {
		for (int i = 0; i < record_count; i++) {
			copy_record(records + i, ret + i);
		}
		*size = record_count;
	}
	return ret;
}

int
initial_records() {
	if ( records )
		clear_records();
	records = malloc(sizeof(grade_record) * INITIAL_CAPACITY);
	record_capacity = INITIAL_CAPACITY;
	record_count = 0;
	return records != NULL;
}

int
increase_capacity() {
	grade_record* ret = NULL;
	ret = realloc(records, sizeof(grade_record) * (record_capacity + REALLOC_INCREMENT));
	if (ret) {
		records = ret;
		record_capacity += REALLOC_INCREMENT;
	}
	return ret != NULL;
}

int
lack_capacity() {	
	return record_capacity - record_count < 5;
}

int
insert_record(grade_record *stu_grade) {
	if (lack_capacity()) {
		if (increase_capacity()) {
			return -1;
		}
	}
	int insert_location = record_count;
	for (int i = record_count - 1; i >= 0; i--) {
		if ( comp(stu_grade, records + i, SORT_BY_ID, SORT_ASC ) ) {
			copy_record(records + i, records + i + 1);
			insert_location = i;
		} else {
			break;
		}
	}
	copy_record(stu_grade, records + insert_location);
	record_count++;
	return insert_location;
}

int
modify_record(int location, grade_record *stu_grade) {
	if (location < 0 || location >= record_count)
		return 0;
	if (strcmp(records[location].stu.stu_id, stu_grade->stu.stu_id) == 0) {
		copy_record(stu_grade, records + location);
		return 1;
	}
	return 0;
}

int
get_record_by_index(int location, grade_record *stu_grade) {
	if (location < 0 || location >= record_count)
		return -1;
	copy_record(records + location, stu_grade);
	return 1;
}

int
delete_record(int location) {
	if (location >= 0 && location < record_count) {
		show_grade_title();
		show_record(location);
		if (!confirm("您正在删除上述学生的成绩记录！")) {
			return 0;
		}
		for (int i = location; i < record_count - 1; i++) {
			copy_record(records + i + 1, records + i);
		}
		record_count -= 1;
		return 1;
	}
	return 0;
}

void
show_records() {
	for (int i = 0; i < record_count; i++) {
		show_record(i);
	}
}

void show_record(int location) {
	if (location < 0 || location >= record_count)
		return;
	printf("%-*s\t%-*s\t%-*d\t%-*d\t%-*d\t%-*d\t%-.2f\n",
				MAX_STU_ID_LENGTH,records[location].stu.stu_id,
				MAX_STU_NAME_LENGTH, records[location].stu.stu_name,
				INTERVAL_LENGTH, records[location].chinese,
				INTERVAL_LENGTH, records[location].math,
				INTERVAL_LENGTH, records[location].english,
				INTERVAL_LENGTH, records[location].total,
				records[location].average);
}

void
read_record_from_input(grade_record *rcd) {
	char buffe[READ_LINE];
	printf("请输入学号：");
	get_line(buffer, );
}

void
save_to_file() {
	FILE *fp = fopen(filepath, "w");
	if (!fp) {
		printf("写入文件失败！\n");
		return;
	}
	for (int i = 0, ret = 0; i < record_count; i++) {
		ret = fprintf(fp, "%s %s %d %d %d %d %.2f\n", 
			records[i].stu.stu_id, records[i].stu.stu_name, records[i].chinese, 
			records[i].math, records[i].english, records[i].total, records[i].average);
		if (ret <= 0) {
			printf("文件写入出错！\n");
			fclose(fp);
			return;
		} 
	}
	fclose(fp);
}
