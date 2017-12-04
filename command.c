#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "command.h"

int runCommand(char ** args){
  int i;
  
  if (hasRedir(args)){
    runRedir(args);
  }

  else if  (hasPipe(args)){
    runPipe(args);
  }
  
  else if (! strcmp(args[0], "cd")){

    chdir(args[1]); //FIXME: handle case with invalid user input
    return 0;
  }
  else if (! strcmp(args[0], "exit")){
    exit(0);
  }

  else {
    forkRun(args);
  }
}

int runSequence(char * block){
  if (! block){
    return 0;
  }
  else {
    char * command = strsep(&block, ";");
    char ** args = parseCommand(command);
    runCommand(args);
    runSequence(block);
  }
}


int runRedir(char ** args){
  int i = hasRedir(args);
  int n;
  if (! strcmp(args[i], ">")){
    for (n = 0; args[n]; n++){
      printf("[%s]\n", args[n]);
    }
    args[i] = 0;
    int fd = dup(STDOUT_FILENO);
    int fd2 = creat(args[i + 1], 00664);
    dup2(fd2, STDOUT_FILENO);
    forkRun(&args[i + 1]);
    dup2(fd, STDOUT_FILENO);
  }
  return 0;
}


int runPipe(char ** args){



}

int hasRedir(char ** s){
  int i;
  for(i = 0; s[i]; i++){
    if (! strcmp(s[i],">") || ! strcmp(s[i], "<")){
      return i;
    }
  }
  return 0;
}


int hasPipe(char ** s){
  int i;
  for(i = 0; s[i]; i++){
    if (! strcmp(s[i], "|")){
      return i;
    }
    return 0;
  }
}

int forkRun(char ** args){

  int status;

  if (fork()){ // parent process
    wait(&status);
    return status;
  }
  else { // forked child process
    execvp(args[0], args);
    exit(0);
  }

}
