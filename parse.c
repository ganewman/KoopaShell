#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"
#include "command.h"

/* ==== parseCommand ========
   Arguments: accepts a char pointer (string) 

   Returns: an array of char pointers which can be passed as command line arguments

   Counts the number of tokens within the string, then allocates the correct amount of memory. It then splits on the spaces between tokens, stripping execess spaces from the front and back of each token as it goes.
 
   ========================*/

char ** parseCommand(char * command){
  int i = 0;
  char space[] = " ";
  if (index(command, '|')){
    runPipe(command);
  }
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

/* ==== countArgs ========
   Arguments: accepts a char pointer (string) 

   Returns: the number of tokens seperated by spaces within the given string

   Returns the mimimum (oops!) number of tokens within the string.

   ========================*/

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

/* ====== stripSpaces =======
   Arguments: accepts a char pointer (string) 

   Returns: a pointer to the same string, with all preceding or terminating whitespace having been stripped. It also removes the final newline appended by fgets(), if present.

   Increments the char pointer to the first instance of a char != ' ', effectively removing the preceding spaces. It then iterates from the back of the string, setting the last instance of ' ' to null, effectively truncating the string.

   ========================*/

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



