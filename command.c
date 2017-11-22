#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int runCommand(char ** args){
  int status;
  /*  int i;
    for (i = 0; args[i]; i++){
      printf("[%s]\n", args[i]);
      }*/
  if (fork()){
    //    printf("i'm the parent process\n");
    wait(&status);

  }
  else {
    //    printf("i'm the child process\n");
    execvp(args[0], args);
    exit(0);
  }
}


