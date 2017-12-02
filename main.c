#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "command.h"

int runSequence(char *);

int main(){
  while(1){
    char s[256];
    printf("KoopaShell$ ");
    fgets(s, sizeof(s), stdin);
 
    /* int i;
       for (i = 0; args[i]; i++){
       printf("%s\n", args[i]);
       }*/
    char * stripped = stripSpaces(s);
    runSequence(stripped);
  }
  return 0;
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
