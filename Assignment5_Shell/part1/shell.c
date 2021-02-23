#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#define BUFFER_SIZE 80

//Forward method declaration
void interactive_mode();
void parse_arguments(char* line);
void shell_error();
int check_for_builtin(char* argc, char** args);
int execute_shell_command(char* argc, char** args);

char error_message[30] = "An error has occurred\n";
int arg_position = 0;
char *path;
int arg_bufsize = BUFFER_SIZE;
int path_bufsize = BUFFER_SIZE;
char** argv;
char* argc;
int argCount = 0;
pid_t pids[BUFFER_SIZE];
int pid_position;
char* builtin[4];
bool pipeCheck;
int main(){
	
	builtin[0] = "exit";
	builtin[1] = "cd";
	builtin[2] = "help";
	builtin[3] = "guessing game";
	path = strdup("/bin/");
	pid_position = 0;
	interactive_mode();
  	return 0;
}

void signal_handler(int sig){
	write(1,"\nmini-shell terminated\n",23);
	free(argc);
	free(argv);
	exit(0);
}

void interactive_mode(){

	signal(SIGINT, signal_handler);
	while(1){
		printf("mini-shell> ");
		pipeCheck = false;
		char* line = NULL;
		size_t bufsize = 0;
		argv = malloc(arg_bufsize*sizeof(char*));
		argc = malloc(arg_bufsize*sizeof(char*));
		if(!argv) {
			shell_error();
		}
		if(getline(&line, &bufsize, stdin) == -1) {
			shell_error();
		}
		parse_arguments(line);
		if(argc != NULL) {
			if(check_for_builtin(argc, argv) != 1){
				printf("builtin command not found,executing shell command\n");
				execute_shell_command(argc, argv);
			}
			
		}
		free(argc);
		free(argv);
	}
	free(argc);
	free(argv);
}

void parse_arguments(char* line){
	char *token;
	arg_position = 0;
	if(strcmp(line, "\n") == 0)
	{
		return;
	}
	token = strtok(line, " \t\n");
	argc = strdup(token);
	printf("%s", argc);
	token = strtok(NULL, " \t\n");
	while(token != NULL) {
		argv[arg_position] = strdup(token);
		if(strcmp(arg_position, "|") == 0) {
		pipeCheck = true;
		}	
		arg_position++;
		if(arg_position >= arg_bufsize) {
			arg_bufsize += BUFFER_SIZE;
			argv = realloc(argv, arg_bufsize * sizeof(char));
			if(!argv){
				shell_error();
			}
		}
		token = strtok(NULL, " \t\n");
	}
	argv[arg_position] = NULL;
	free(token);

}

void shell_error() {
	write(STDERR_FILENO, error_message, strlen(error_message));
	free(argc);
	free(argv);
}


int check_for_builtin(char* argc, char** argv){
	if(strcmp(argc, "exit") == 0) {
		
		if(arg_position != 0) {
			shell_error();
		}
		printf("Mini-shell exiting\n");
		free(argc);
		free(argv);
		exit(0);
	
	}else if(strcmp(argc, "cd") == 0) {
		
		if(arg_position != 1) {
			printf("path not specified\n");
		}
		
		char cwd[100];
        	if(getcwd(cwd, sizeof(cwd))!=NULL) {
                	printf("current directory is %s\n", cwd);
        	}

		
		if(chdir(strdup(argv[0])) == -1){
			printf("changing directories failed\n");
		}
		
        	if(getcwd(cwd, sizeof(cwd))!=NULL) {
                	printf("current directory is %s\n", cwd);
        	}	

		return 1;
		
	}else if(strcmp(argc, "help") == 0) {
			
		if(arg_position > 0) {
			printf("Too many Arguments for help");
		}
		int i;
		for(i = 0; i < 4; i++){
			printf("%d. %s\n", i+1, builtin[i]);
		}
		return 1;	
	}else if(strcmp(argc, "Guessing Game" == 0)) {
		guessingGame();
	else {
		return 0;
	}
	return 0;

}

int execute_shell_command(char* argc, char** argv){
	
	char shell_command[BUFFER_SIZE];
	strcpy(shell_command, path);
	strcat(shell_command, argc);
	printf("%s\n", shell_command);
	if(pipeCheck == false){
       		if(fork() == 0){
			execve(shell_command, argv, NULL);
			printf("Child will never go here\n");
			exit(1);
		}else {
			wait(NULL);
			printf("parent print\n");
		}
	else{
		return 0;
	}

	return 0;
}

void guessingGame(){
	int guesses[5];
	int counter = 0;
	srand(time(NULL));
	int correctAnswer = rand() % 10 + 1;
	printf("Game %d:\n", counter + 1);
	int userGuess;
	printf("Guess a number between 1 and 10\n");
	bool flag = false;
	while(flag == false){
		scanf("%d", &userGuess);
		if(userGuess == correctAnswer){
			printf("You guessed it right.\n");
			flag = true;
		}
		else if(userGuess > correctAnswer){
			printf("Your guess is higher than correct answer\n");
		}
		else{
			printf("Your guess is lower than correct answer");
		}
	}
}
