#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int runCommand(char ** args){
  int status;
  /*  int i;
      for (i = 0; args[i]; i++){
      printf("[%s]\n", args[i]);
      }*/
  if (! strcmp(args[0], "cd")){

    chdir(args[1]); //FIXME: handle case with invalid user input
    return 0;
  }
  else if (! strcmp(args[0], "exit")){
    exit(0);
  }

  if (fork()){ // parent process
    //    printf("i'm the parent process\n");
    wait(&status);

  }
  else { // forked child process
    //    printf("i'm the child process\n");
    execvp(args[0], args);
    exit(0);
  }
}


