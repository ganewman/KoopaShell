#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"

char ** parseCommand(char * command){
  int i = 0;
  char space[] = " ";
  int num_args = countArgs(command);
  char ** args = calloc(num_args + 1, sizeof(char *));
  command = stripSpaces(command);
  while(command){
    args[i] = strsep(&command, " ");
    command = stripSpaces(command);
    i++;
  }
  return args;
}


int countArgs(char * i){
  if (*i == '\n'){ // if the inputted string is null
    return 0;
  }
  int num_args;
  for (num_args = 1; *i; i++){
    if (*i == ' '){
      num_args ++;
    }
  }
  return num_args;

}

char * stripSpaces(char * s){
  if (!s){
    return s;
  }
  s = strsep(&s, "\n");
  for(s; *s == ' '; s++); // remove spaces from front by returning a pointer to the first index without a space
  int size = strlen(s);
  char * end;
  for(end = s + size - 1; *end == ' '; end--);
  // start at index before terminating null (size - 2) and move backward until spaces end
  *(end + 1) = 0;
  return s;

}



