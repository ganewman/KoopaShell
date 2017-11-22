#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int countArgs(char *);
char ** parseCommand(char *);

int main(){
  while(1){
    char s[256];
    printf("Please type a command:\n"); // FIXME: print command prompt instead
    fgets(s, sizeof(s), stdin);
    char ** args = parseCommand(s);
    /*   int i;
    for (i = 0; args[i]; i++){
      printf("%s\n", args[i]);
      }*/
  }
  return 0;
}


char ** parseCommand(char * command){
  int i = 0;
  char space[] = " ";
  int num_args = countArgs(command);
  char ** args = calloc(num_args + 1, sizeof(char *));
  //  printf("%s\n", command);
  while(command){
    args[i] = strsep(&command, space);
    i++;
  }
  args[num_args] = 0;
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
