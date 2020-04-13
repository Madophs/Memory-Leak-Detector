#include "mld.h"
#include <stdio.h>
#include <string.h>

void print_struct_db_record(struct struct_db_record *record) {
	if(!record) {
		printf("Error: struct_db_record is null pointer\n");
		return;
	}
	const int TEMP_MAX_SIZE = 113;
	char line[TEMP_MAX_SIZE];
	for(unsigned int i = 0; i < TEMP_MAX_SIZE-1; line[i++] = '-');
	line[TEMP_MAX_SIZE-1] = '\0';
	printf("%s\n|%-30s | %-10s | %-10s|%53s|\n",line, "Struct", "Size", "No Fields","");
	printf("%s\n|%-30s | %-10lu | %-10u|%53s|\n", line, record->struct_name, record->struct_size, record->struct_n_fields,"");
	struct field_info *row = record->fields_data;
	printf("%s\n", line);
	printf("%s\n|%31s| %-22s | %10s | %6s | %6s | %20s |\n", line, "", "nth Field name", 
		"Datatype",
		"Size", "offset",
		"Nested struct");
	printf("%s\n", line);
	for(unsigned int i = 0; i < record->struct_n_fields; ++i) {
		printf("|%31s| %u %-20s | %10s | %6lu | %6lu | %20s |\n", "", i, row[i].field_name, 
				get_data_type(row[i].field_type),
				row[i].field_size, row[i].offset,
				row[i].nested_struct_name);
	}
	printf("%s\n\n<%s>\n\n", line, line+2);
}

void print_struct_db(struct struct_db *db) {
	if(!db) {
		printf("Error: strut_db is null\n");
		return;
	}
	printf("Printing the structure database\n");
	printf("Number of structures %d\n", db->items);
	struct struct_db_record *node = db->head;
	while(node) {
		print_struct_db_record(node);
		node = node->next;
	}
}

int add_structure_to_struct_db(struct struct_db *db, struct struct_db_record *record) {
	if(db == NULL || record == NULL) {
		printf("Unable to add structure to structure_database\n");
		return -1;
	}
	if(db->head) {
		record->next = db->head;
		db->head = record;	
	} else {
		db->head = record;
	}
	++db->items;
	return 0;
}

char * get_data_type(data_type_t type) {
	if(type == UINT8) {
		return "UNIT8";
	} else if(type == UINT32) {
		return "UINT32";
	} else if(type == INT32) {
		return "INT32";
	} else if(type == CHAR) {
		return "CHAR";
	} else if(type == OBJ_PTR) {
		return "OBT_PTR";
	} else if(type == FLOAT ) {
		return "FLOAT";
	}
	return "HELLO";
}

struct struct_db_record * struct_db_look_up(struct struct_db *db, char *struct_name) {
	struct struct_db_record *st_pointer = db->head;
	while(st_pointer) {
		if(strcmp(st_pointer->struct_name, struct_name) == 0) {
		       return st_pointer;
		}
		st_pointer = st_pointer->next;
	}		
	return NULL;
}



