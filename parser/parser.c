#define _POSIX_C_SOURCE 200809L
#include "parser.h"

char* sh_read_line(FILE* f){
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, f) == -1) {
		if (feof(f)) {
			return NULL; 
		} 
		else{
			perror("420sh: getline\n");
			exit(EXIT_FAILURE);
		}
	}

	return line;
}

