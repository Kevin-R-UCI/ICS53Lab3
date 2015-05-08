#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "csapp.h"

/** TODO
 * 1) check to make sure enough arguments exist before converting.
 * 2) 

int eval(char *buffer);

//Commands
void cmd_allocate(unsigned int size);
void cmd_free(unsigned int block_num);
void cmd_block_list();
void cmd_write_heap(unsigned int block_num, char to_write, unsigned int num_copies);
void cmd_print_heap(unsigned int block_num, unsigned int num_chars);

int main(int argc, char **argv) {
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

int eval(char *buffer) {
	char delim[] = " \n";
	char *cmd = strtok(buffer, delim);
	//NOTE: perhaps check to make sure strtok doesn't return NULL.
	if(strcmp(cmd, "allocate") == 0) {
		unsigned int size = atoi(strtok(NULL, delim));
		cmd_allocate(size);
	} else if(strcmp(cmd, "free") == 0) {
		unsigned int block_num = atoi(strtok(NULL, delim));
		cmd_free(block_num);
	} else if(strcmp(cmd, "blocklist") == 0) {
		cmd_block_list();
	} else if(strcmp(cmd, "writeheap") == 0) {
		unsigned int block_num = atoi(strtok(NULL, delim));
		char to_write = strtok(NULL, delim)[0];
		unsigned int num_copies = atoi(strtok(NULL, delim));
		cmd_write_heap(block_num, to_write, num_copies);
	} else if(strcmp(cmd, "printheap") == 0) {
		unsigned int block_num = atoi(strtok(NULL, delim));
		unsigned int num_chars = atoi(strtok(NULL, delim));
		cmd_print_heap(block_num, num_chars);
	} else if(strcmp(cmd, "bestfit") == 0) {
		printf("using bestfit\n");
	} else if(strcmp(cmd, "firstfit") == 0) {
		printf("using firstfit\n");
	} else if(strcmp(cmd, "quit") == 0) {
		//NOTE: cleanup?
		exit(0);
	} else {
		printf("Please enter a valid command.\n");
	}

	return 0;
}


void cmd_allocate(unsigned int size) {
	printf("allocating block of size %d\n", size);
}

void cmd_free(unsigned int block_num) {
	printf("freeing block %d\n", block_num);
}

void cmd_block_list() {
	printf("printing all blocks\n");
}

void cmd_write_heap(unsigned int block_num, char to_write, unsigned num_copies) {
	printf("printing %c to block %d %d times\n", to_write, block_num, num_copies);
}

void cmd_print_heap(unsigned int block_num, unsigned int num_chars) {
	printf("printing %d bytes of block %d\n", num_chars, block_num);
}
