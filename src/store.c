#include "store.h"
#include "grade.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

char filepath[FILEPATH_LENGTH] = DEFAULT_FILEPATH;

int file_exists(const char* path) {
	return access(path, F_OK) == 0;
}

int change_data_source(const char* path) {
	if (!file_exists(path)) {
		FILE* fp = fopen(path, "w");
		if (fp)
			fclose(fp);
		else {
			return 0;
		}
	}
	snprintf(filepath, FILEPATH_LENGTH, "%s",  path);
	return 1;
}

int load_data_file(const char* path) {
	if (!change_data_source(path))
		return 0;
	FILE* fp = fopen(path, "r");
	if (!fp)
		return 0;
	if (!initial_records())
		return 0;
	grade_record rcd;
	while(fscanf(fp, "%s %s %d %d %d %d %lf",	\
		rcd.stu.stu_id, rcd.stu.stu_name, 	\
		&rcd.chinese, &rcd.math, &rcd.english, 	\
		&rcd.total, &rcd.average) != EOF) {
		if (insert_record(&rcd) == -1)
			return 0;

	}
	fclose(fp);

	return 1;
}

int
write_to_file(grade_record *rcd) {
	FILE *fp = fopen(filepath, "a+");
	if (!fp) {
		printf("打开文件出错！\n");
		return 0;
	}
	int ret = fprintf(fp, "%s %s %d %d %d %d %.2f\n", 
		rcd->stu.stu_id, rcd->stu.stu_name, rcd->chinese, 
		rcd->math, rcd->english, rcd->total, rcd->average);
	if (ret <= 0) {
		printf("文件写入出错！\n");
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}


