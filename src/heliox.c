#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HSH_RL_BUFSIZE 1024
#define HSH_TOK_BUFSIZE 64
#define HSH_TOK_DELIM " \t\r\n\a"

char cwd[1024];

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

char** hsh_split_line(char* line) {

	int bufsize = HSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;

	if (!tokens) {
		fprintf(stderr, "hsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, HSH_TOK_DELIM);
	while (token != NULL) {
	tokens[position] = token;
	position++;

	if (position >= bufsize) {
	  bufsize += HSH_TOK_BUFSIZE;
	  tokens_backup = tokens;
	  tokens = realloc(tokens, bufsize * sizeof(char*));
	  if (!tokens) {
		free(tokens_backup);
	    fprintf(stderr, "hsh: allocation error\n");
	    exit(EXIT_FAILURE);
	  }
	}

	token = strtok(NULL, HSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

char* hsh_read_line() {
	char *line = NULL;
	ssize_t bufsize = 0; 
 	getline(&line, &bufsize, stdin);
	return line;
}

void hsh_loop() {
	char *line;
	char **args;
	int status;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("HelioxSH... \n");

	do {
		printf("[%s]$ ",cwd);
		line = hsh_read_line();
		args = hsh_split_line(line);

		free(line);
		free(args);
	}
	while(status);

}

int main(int argc, char** argv) {

	clear();
	
	hsh_loop();
	return EXIT_SUCCESS;
}