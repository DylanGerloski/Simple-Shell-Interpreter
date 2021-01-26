#include <stdio.h>
#include "shell.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

//Dylan Gerloski- Operating systems miniProject-2

void execute(char* const args[])
{

  //string that will contain the path of the command to be executed
  char path[100];
  int i;
  printf("*** Entered:");
  for (i = 0; args[i] != NULL; i++){
    printf(" %s", args[i]);
  }
  printf(" (%d words)\n", i);
  strcpy(path, "/bin/");
  strcat(path, args[0]); 
  pid_t pid, wpid;

  //create a new proces
  pid = fork();

  //use exec to start new process in the newly created child process
  // exec returns a negative number if specified  path is not found, so print an error and exit if this is the case
  if (pid == 0){
	if(execvp(path, args) < 0){
		perror("command not found\n");
	}
	exit(1);
  //a pid that is negative means the fork failed, so print the error and use the exit command
  }else if(pid < 0) {
	perror("fork failed");
	exit(2);
  }
  else {
	//uses waitpid to check to see if the specified process is still running 
	//WIFEXITED evalautes to  true if child process exited sucessfuly  or called the exit() function
	int status;
	wpid = waitpid(pid, &status,0);
	if(WIFEXITED(status))
		//if exit status code == 0, then  process exited successfuly
		if(WEXITSTATUS(status) == 0)
			printf("Command exited sucsessfuly\n");
		else
			printf("Program  terminated with exit status %d\n",WEXITSTATUS(status));
	else
	 	printf("child %d terminated abnormally\n" , wpid);
  }

}

