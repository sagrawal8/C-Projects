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
#define TIME_LIMIT 10 
//Forward method declaration
void interactive_mode();
void parse_arguments(char* line);
void shell_error();
int check_for_builtin(char** args);
int execute_shell_command(char** argv, char** argv_pipe);
void guessingGame();
void free_arg_arrays();
void alarm_handler(int);
void child_handler(int);
int fork_function(int in, int out, char** argv);
int timeout = 0;
int child_done = 0;

char error_message[30] = "An error has occurred\n";
int arg_position = 0;
int pipe_position;
char *path;
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
	path = strdup("/bin/");
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
			continue;
			
		}
		
		parse_arguments(line);
		if(pipeCheck == true && argv_pipe[0] == NULL) {
			free_arg_arrays();
			printf("mini-shell> ");
			continue;
		}
		if(argv[0] != NULL) 
		{	

			//printf("argv[0] is %s\n", argv[0]);
			//printf("pipe check is %d\n", pipeCheck);
			//if(argv_pipe != NULL){
			//	printf("argv_pipe[0] is %s\n",argv_pipe[0]);
			//	printf("argv_pipe[1] is %s ",argv_pipe[1]);
			//}
			if(strcmp(argv[0], "") == 0 ){
				continue;
			}
			if(check_for_builtin(argv) != 1){
				printf("Built-in command not found, executing shell command\n");
				execute_shell_command(argv, argv_pipe);
			}
		
			free_arg_arrays();

		}
		else{
			printf("here");
			continue;
		}		
	}
}

void parse_arguments(char* line){
	char *token;
	pipe_position = 0;
	arg_position = 0;
	if(strcmp(line, "\n") == 0)
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
		//printf("Freed argv array\n");
	}
	if(argv_pipe != NULL)
	{
		free(argv_pipe);
		argv_pipe = NULL;
		//printf("Freed pipe array\n");
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
		}
		
		char cwd[100];
        	if(getcwd(cwd, sizeof(cwd))!=NULL) {
                	printf("Previous directory was %s\n", cwd);
        	}

		
		if(chdir(strdup(argv[1])) == -1){
			printf("changing directories failed\n");
			printf("Directory is still %s\n", cwd);
		
		}
		
        	if(getcwd(cwd, sizeof(cwd))!=NULL) {
                	printf("Current directory is %s\n", cwd);
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

int execute_shell_command(char** argv, char** argv_pipe){

	char shell_command[BUFFER_SIZE];
	if(strcmp(argv[0], "./shell") == 0)
	{
		strcpy(shell_command, argv[0]);
	}
	else {
		strcpy(shell_command, path);
		strcat(shell_command, argv[0]);
	}
	if(argv_pipe != NULL) {
		printf("Argv_Pipe[0]: %s\n", argv_pipe[0]);
		printf("Argv_Pipe[1]: %s\n", argv_pipe[1]);
	}
	if(pipeCheck == false){
		printf("PIPE CHECK FALSE");
		pid_t pid = fork();
		if(pid == -1) 
		{
			perror("Fork Failed");
			exit(1);
		}
       		if(pid == 0){
			execve(shell_command, argv, NULL);
			printf("Child will never go here\n");
			exit(1);
		}else {
			signal(SIGALRM, alarm_handler);
			signal(SIGCHLD, child_handler);
			alarm(TIME_LIMIT);
			pause();

			if(timeout) {
				printf("alarm triggered\n");
				int result = waitpid(pid, NULL, WNOHANG);
				if(result == 0) {
					printf("Killing Child\n");
					kill(pid, 9);
					wait(NULL);
				}
				else {
					printf("alarm triggered but child finished normally\n");
				}
			}
			else if (child_done) {
				printf("child finished normally\n");
				wait(NULL);
			}
			
		}
	}
	else if(pipeCheck == true) 
	{
		int i;
		pid_t pid;
		int in, fd[2];

		in = 0;
		pipe(fd);
		fork_function(in, fd[1], argv);
		close(fd[1]);
		in = fd[0];

		if((pid = fork()) == 0)
		{
			if(in != 0)
			{
				dup2(in, 0);
			}
			return execvp(argv_pipe[0], argv_pipe);	
		}
		return pid;
	}
	return 0;
}

int fork_function(int in, int out, char** argv) {
	pid_t pid;
	if((pid = fork()) == 0)
	{
		if(in !=0)
		{
			dup2(in, 0);
			close(in);
		}
		if(out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		return execvp(argv[0], argv);
	}
	return pid;
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
