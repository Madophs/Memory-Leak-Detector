#include <stdio.h>
#include <memory.h>
#include "mld.h"

typedef struct emp_t {
    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_t *mgr;
    float salary;
} emp_t;

typedef struct student_t{
    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleage;
} student_t;


int main() {
	printf("Memory Link Detector is starting...\n");
	struct struct_db *db = (struct struct_db*)calloc(1, sizeof(struct struct_db));
	static struct field_info emp_fields[] = {
		FIELD_INFO(emp_t, emp_name, CHAR, 0),
		FIELD_INFO(emp_t, emp_id, UINT32, 0),
		FIELD_INFO(emp_t, age, UINT32, 0),
		FIELD_INFO(emp_t, mgr, OBJ_PTR, emp_t),
		FIELD_INFO(emp_t, salary, FLOAT, 0),
	};
	REG_STRUCT(db, emp_t, emp_fields);
	static struct field_info  student_fields[] = {
		FIELD_INFO(student_t, stud_name, CHAR, 0),
		FIELD_INFO(student_t, rollno, UINT32, 0),
		FIELD_INFO(student_t, age, UINT32, 0),
		FIELD_INFO(student_t, aggregate, FLOAT, 0),
		FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_)
	};
	REG_STRUCT(db, student_t, student_fields);
	print_struct_db(db);
	return 0;
}
