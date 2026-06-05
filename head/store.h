#ifndef HEAD_STORE
#define HEAD_STORE

#include "constants.h"
#include "grade.h"

extern char filepath[FILEPATH_LENGTH];

int file_exists(const char* path);
int change_data_source(const char* path);
int load_data_file(const char* path);
int write_to_file(grade_record *rcd);


#endif
