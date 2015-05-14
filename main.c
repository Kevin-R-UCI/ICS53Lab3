#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "csapp.h"
#include "memlib.h"
#include "mm.h"

/* TODO:
 * 1) Toggling between bestfit/firstfit
 * 2) Implementation of bestfit
 * 3) Code review
 */

int eval(char *buffer);

//Commands
void cmd_allocate(unsigned int size);
void cmd_free(unsigned int block_num);
void cmd_block_list();
void cmd_write_heap(unsigned int block_num, char to_write, unsigned int num_copies);
void cmd_print_heap(unsigned int block_num, unsigned int num_chars);

void init();

int main(int argc, char **argv) {
	//initializes memory
	init();

	char cmdline[MAXLINE];
	while(1) {
		printf("> ");
		Fgets(cmdline, MAXLINE, stdin);
		if(feof(stdin)) {
			exit(0);
		}

		eval(cmdline);
	}
	
	return 0;
}

char delim[] = " \n";
int get_uint_arg(unsigned int *arg) {
	char *tmp;
	if((tmp = strtok(NULL, delim)) == NULL) {
		printf("Not enough arguments!\n");
		return -1;
	}
	
	*arg = atoi(tmp);
	return 0;
}

int get_char_arg(char *arg) {
	char *tmp;
	if((tmp = strtok(NULL, delim)) == NULL) {
		printf("Not enough arguments!\n");
		return -1;
	}

	*arg = tmp[0];
	return 0;
}

int eval(char *buffer) {
	char delim[] = " \n";
	char *arg;
	char *cmd = strtok(buffer, delim);
	
	if(strcmp(cmd, "allocate") == 0) {
		unsigned int size;
		if(get_uint_arg(&size) < 0) {
			return 0;
		}
		cmd_allocate(size);
	} else if(strcmp(cmd, "free") == 0) {
		unsigned int block_num;
		if(get_uint_arg(&block_num) < 0) {
			return 0;
		}
		cmd_free(block_num);
	} else if(strcmp(cmd, "blocklist") == 0) {
		cmd_block_list();
	} else if(strcmp(cmd, "writeheap") == 0) {
		unsigned int block_num;
		char to_write;
		unsigned int num_copies;
		if(get_uint_arg(&block_num) < 0 || get_char_arg(&to_write) < 0 || get_uint_arg(&num_copies) < 0) {
			return 0;
		}
		cmd_write_heap(block_num, to_write, num_copies);
	} else if(strcmp(cmd, "printheap") == 0) {
		unsigned int block_num;
		unsigned int num_chars;
		if(get_uint_arg(&block_num) < 0 || get_uint_arg(&num_chars) < 0) {
			return 0;
		}
		cmd_print_heap(block_num, num_chars);
	} else if(strcmp(cmd, "bestfit") == 0) {
		change_fit(BEST_FIT);
		printf("using bestfit\n");
	} else if(strcmp(cmd, "firstfit") == 0) {
		change_fit(FIRST_FIT);
		printf("using firstfit\n");
	} else if(strcmp(cmd, "quit") == 0) {
		//TODO: cleanup?
		exit(0);
	} else {
		printf("Please enter a valid command.\n");
	}

	return 0;
}


/**Memory functions / commands**/
static void **block_num_to_addr;
static unsigned int block_nums_size = 0;
static unsigned int next_block_num = 0;

void init() {
	mem_init();
	mm_init();
	
	block_nums_size = 1;
	block_num_to_addr = Malloc(sizeof(void*) * block_nums_size);
}

void extend_block_nums() {
	block_nums_size *= 2;
	block_num_to_addr = Realloc(block_num_to_addr, sizeof(void*) * block_nums_size);
}

void cmd_allocate(unsigned int size) {
	if(block_nums_size <= next_block_num) {
		extend_block_nums();
	}

	block_num_to_addr[next_block_num++] = mm_malloc(size);
	printf("%d\n", next_block_num);
}

void cmd_free(unsigned int block_num) {
	--block_num;
	if(next_block_num <= block_num) {
		printf("Invalid block number!\n");
		return;
	}
	
	mm_free(block_num_to_addr[block_num]);
	block_num_to_addr[block_num] = NULL;
}

void cmd_block_list() {
	blocklist();
}

void cmd_write_heap(unsigned int block_num, char to_write, unsigned num_copies) {
	char *loc = (char*)(block_num_to_addr[--block_num]);
	for(unsigned int i = 0; i < num_copies; ++i) {
		loc[i] = to_write;
	}
}

void cmd_print_heap(unsigned int block_num, unsigned int num_chars) {
	char *loc = (char*)(block_num_to_addr[--block_num]);
	for(unsigned int i = 0; i < num_chars; ++i) {
		printf("%c", loc[i]);
	}
	printf("\n");
}
