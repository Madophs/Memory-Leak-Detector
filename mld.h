#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_STRUCTURE_NAME_SIZE  128
#define MAX_FIELD_NAME_SIZE 128

typedef enum {
	UINT8,
	UINT32,
	INT32,
	CHAR,
	OBJ_PTR,
	VOID_PTR,
	FLOAT,
	DOUBLE,
	OBJ_STRUCT
} data_type_t;

struct field_info {
	char field_name[MAX_FIELD_NAME_SIZE];
	size_t field_size;
	size_t offset;
	data_type_t field_type;
	char nested_struct_name[MAX_STRUCTURE_NAME_SIZE];
};

struct struct_db_record {
	struct struct_db_record *next;
	char struct_name[MAX_STRUCTURE_NAME_SIZE];
	size_t struct_size;
	unsigned int struct_n_fields;
	struct field_info *fields_data;
};	

struct struct_db {
	struct struct_db_record *head;
	unsigned int items;
};

void print_struct_db_record(struct struct_db_record *);

void print_struct_db(struct struct_db *);

int add_structure_to_struct_db(struct struct_db *, struct struct_db_record *);

char * get_data_type(data_type_t type);

#define FIELD_INFO(st_name, st_field_name, st_field_type, st_nested_struct) \
	{#st_field_name, sizeof(((struct st_name*)0)->st_field_name), \
	offsetof(st_name,st_field_name), st_field_type, #st_nested_struct}

#define REG_STRUCT(struct_database, st_name, st_fields_arr) \
	{\
		struct struct_db_record *new_record = (struct struct_db_record *)calloc(1, sizeof(struct struct_db_record)); \
		strcpy(new_record->struct_name, #st_name); \
		new_record->struct_size = sizeof(st_name); \
		new_record->struct_n_fields = sizeof(st_fields_arr) / sizeof(struct field_info); \
		new_record->fields_data = st_fields_arr; \
		if(add_structure_to_struct_db(struct_database, new_record)){ \
			assert(0); \
		} \
	}

struct struct_db_record * struct_db_look_up(struct struct_db *, char *);
