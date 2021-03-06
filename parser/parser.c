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
#define SH_TOK_BUFSIZE 64
#define SH_TOK_DELIM " \t\r\n\a"

char** sh_split_line(char *line){

	int bufsize = SH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;

	if (!tokens) {
		fprintf(stderr, "420sh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, SH_TOK_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += SH_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				free(tokens_backup);
				fprintf(stderr, "420sh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, SH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}
