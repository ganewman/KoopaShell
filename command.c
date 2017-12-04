#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "command.h"
#include "parse.h"

/* ==== runCommand =========
   Arguments: accepts an array char pointers (strings)

   Returns: an int indicating exit status

   Accepts an array of command line arguments, which it will fork and execute as necessary.

   ========================*/

int runCommand(char ** args){
  int i;
  
  if (hasRedir(args)){
    runRedir(args);
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

/* ==== runSequence =========
   Arguments: accepts a char pointer (string) 

   Returns: an int indicating exit status

   Accepts command line input in the form of a string. It will split on the first semicolon (if any), parse and run the preceding command, and continue recursively in this manner until all commands have been executed.

   ========================*/

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

/* ==== runRedir ===========
   Arguments: accepts an array of char pointers (strings), one of which is either "<" or ">". 

   Returns: an int indicating exit status

   Handles command execution in the event redirection is required. It will redirect either STDIN or STDOUT to the desired file as necessary, then fork and execute the given command. 

   ========================*/

int runRedir(char ** args){
  int i = hasRedir(args);
  int n;
  if (! strcmp(args[i], ">")){
    args[i] = 0;
    int fd = dup(STDOUT_FILENO);
    int fd2 = creat(args[i + 1], 00664);
    dup2(fd2, STDOUT_FILENO);
    forkRun(args);
    dup2(fd, STDOUT_FILENO);
  }
  else {
    args[i] = 0;
    int fd = dup(STDIN_FILENO);
    int fd2 = open(args[i + 1], O_RDONLY);
    dup2(fd2, STDIN_FILENO);
    forkRun(args);
    dup2(fd, STDIN_FILENO);

  }
  return 0;
}

/* ==== runPipe ===========
   Arguments: accepts a char pointer (string) containing at least one pipe.

   Returns: an int indicating exit status

   Accepts command line input in the form of a stirng, and handles execution in the event piping is required. It splits on the pipe, then use popen to read the output of the first command and write the resulting buffer to the second.
 
   ========================*/

int runPipe(char * command){
  FILE * fp_r;
  FILE * fp_w;
  char * buf[512];
  char * i = index(command, '|');
  *i = 0;
  fp_r = popen(command, "r");
  fp_w = popen(i + 1, "w");
  
  int fd_r = fileno(fp_r);
  int fd_w = fileno(fp_r);
  read(fd_r, buf, sizeof(buf));
  write(fd_w, buf, sizeof(buf));
  pclose(fp_r);
  pclose(fp_w);
  close(fd_r);
  close(fd_w);
  return 0;
}

/* ==== hasRedir ===========
   Arguments: accepts an array of char pointers (strings)

   Returns: the array index at which the first instance of ">" or "<" was found. If none exists, returns 0.

   Checks whether the given array of command line arguments contains at least one redirection, and returns the index of the first instance. Returns 0 if none is found.
 
   ========================*/


int hasRedir(char ** s){
  int i;
  for(i = 0; s[i]; i++){
    if (! strcmp(s[i],">") || ! strcmp(s[i], "<")){
      return i;
    }
  }
  return 0;
}

/* ==== forkRun ===========
   Arguments: accepts an array of char pointers (strings)

   Returns: an int indicating exit status

   Will fork, and then execute the given array of commands using execvp within the child process.
 
   ========================*/

int forkRun(char ** args){

  int status;

  if (fork()){ // parent process
    wait(&status);
    return status;
  }
  else { // forked child process
    execvp(args[0], args);
    free(args);
    exit(0);
  }

}
