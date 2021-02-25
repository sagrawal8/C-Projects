#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#define BUFFER_SIZE 80
#define TIME_LIMIT 50 
//Forward method declaration
void interactive_mode();
void parse_arguments(char* line);
void shell_error();
int check_for_builtin(char** args);
void execute_shell_command(char** argv, char** argv_pipe);
void guessingGame();
void free_arg_arrays();
void alarm_handler(int);
void child_handler(int);
int timeout = 0;
int child_done = 0;

char error_message[30] = "An error has occurred\n";
int arg_position = 0;
int pipe_position;
int arg_bufsize = BUFFER_SIZE;
int path_bufsize = BUFFER_SIZE;
char** argv;
char** argv_pipe;
char* builtin[4];
bool pipeCheck;
int main(){
	
	builtin[0] = "exit";
	builtin[1] = "cd";
	builtin[2] = "help";
	builtin[3] = "GuessingGame";
	argv = NULL;
	argv_pipe = NULL;
	interactive_mode();
  	return 0;
}

void signal_handler(int sig){
	write(1,"\nmini-shell terminated\n",23);
	free_arg_arrays();
	exit(0);
}

void interactive_mode(){

	signal(SIGINT, signal_handler);
	while(1)
	{
		pipeCheck = false;
		char* line = NULL;
		size_t bufsize = 0;
		argv = malloc(arg_bufsize*sizeof(char*));
		
		if(!argv) {
			printf("argv error\n");
			shell_error();
		}
		
		printf("mini-shell>> ");
		
		if(getline(&line, &bufsize, stdin) == -1) {
			printf("getline error\n");
			shell_error();
		}
		
		parse_arguments(line);

		if(argv[0] != NULL) {
			if(strcmp(argv[0], "") == 0 ){
				continue;
			}
			
			if(check_for_builtin(argv) != 1){
				execute_shell_command(argv, argv_pipe);
			}
		}
		
		free_arg_arrays();
		free(line);		
	}
}

void parse_arguments(char* line){
	char *token;
	pipe_position = 0;
	arg_position = 0;
	
	if(strcmp(line, "\n") == 0 || strcmp(line, "") == 0)
	{
		return;
	}
	
	token = strtok(line, " \t\n");
	while(token != NULL) {
		if(strcmp(token, "|") == 0) {
			argv_pipe = malloc(arg_bufsize*sizeof(char*)); 
			pipeCheck = true;
			token = strtok(NULL, " \t\n");
			continue;
		}
		if(pipeCheck == true)
		{
			argv_pipe[pipe_position] = strdup(token);
			pipe_position++;
			if(pipe_position >= arg_bufsize) 
			{
                        	arg_bufsize += BUFFER_SIZE;
                        	argv_pipe = realloc(argv_pipe, arg_bufsize * sizeof(char));
                        	if(!argv_pipe)
				{
                                	shell_error();
                        	}	
				continue;
                	}
		}
		else
		{	
			argv[arg_position] = strdup(token);
			arg_position++;
			if(arg_position >= arg_bufsize) {
				arg_bufsize += BUFFER_SIZE;
				argv = realloc(argv, arg_bufsize * sizeof(char));
				if(!argv){
					shell_error();
				}
			}
		}
		token = strtok(NULL, " \t\n");
	}
	argv[arg_position] = NULL;
	if(pipeCheck == true){
		argv_pipe[pipe_position] = NULL;
	}
	free(token);

}

void shell_error() {
	write(STDERR_FILENO, error_message, strlen(error_message));
	free_arg_arrays();	
}

void free_arg_arrays() {
	if(argv != NULL)
	{
		free(argv);
		argv = NULL;
	}
	if(argv_pipe != NULL)
	{
		free(argv_pipe);
		argv_pipe = NULL;
	}
}

int check_for_builtin(char** argv){
	if(strcmp(argv[0], "exit") == 0) {
		
		if(arg_position != 1) {
			shell_error();
		}
		printf("Mini-shell exiting\n");
		free_arg_arrays();
		exit(0);
	
	}else if(strcmp(argv[0], "cd") == 0) {
		
		if(arg_position != 2) {
			printf("path not specified\n");
			return 1;
		}
		
		char cwd[500];
        			
		if(chdir(strdup(argv[1])) == -1){
			printf("changing directories failed\n");
			printf("Directory is still %s\n", cwd);
		
		}
		return 1;
		
	}else if(strcmp(argv[0], "help") == 0) {
			
		if(arg_position > 1) {
			printf("Too many Arguments for help");
		}
		int i;
		for(i = 0; i < 4; i++){
			printf("%d. %s\n", i+1, builtin[i]);
		}
		return 1;	
	
	}else if(strcmp(argv[0], "GuessingGame") == 0) {
		
		guessingGame();
		return 1;
	
	}
	return 0;

}

void execute_shell_command(char** argv, char** argv_pipe){

	if(pipeCheck == false){
		
		pid_t pid = fork();
		if(pid == -1) 
		{
			perror("Fork Failed");
			exit(1);
		}
       		if(pid == 0){
			execvp(argv[0], argv);
			exit(1);
		}else {
			signal(SIGALRM, alarm_handler);
			signal(SIGCHLD, child_handler);
			alarm(TIME_LIMIT);
			pause();
			if(timeout) {
				int result = waitpid(pid, NULL, WNOHANG);
				if(result == 0) {
					kill(pid, 9);
					wait(NULL);
				}
			}
			else if (child_done) {
				wait(NULL);
			}	
	}
}
	else if(pipeCheck == true) 
	{
		pid_t pid1, pid2;
		int fd[2];
		int child_status;
		pipe(fd);
		pid1 = fork();
		if(pid1 == 0)
		{
			close(STDOUT_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			execvp(argv[0], argv);
			exit(1);
		}

		else if((pid2 = fork()) == 0 && pid1 != 0)
		{	
			close(STDIN_FILENO);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);			
			execvp(argv_pipe[0], argv_pipe);
			exit(1);	
		}
		else if(pid1 != 0 && pid2 != 0) {
			close(fd[0]);
			close(fd[1]);
			waitpid(pid1, &child_status, child_status);
			waitpid(pid2, &child_status, child_status);
			return;	
		}
		
	}

}
void child_handler(int sig) {
	child_done = 1;
}

void alarm_handler(int sig){
	timeout = 1;
}

void guessingGame(){
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
			printf("Your guess is lower than correct answer\n");
		}
	}
}
