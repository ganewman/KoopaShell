#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "command.h"



int main(){
  while(1){
    char s[256];
    printf("Please type a command:\n"); // FIXME: print command prompt instead
    fgets(s, sizeof(s), stdin);
    char ** args = parseCommand(s);
    /* int i;
         for (i = 0; args[i]; i++){
      printf("%s\n", args[i]);
      }*/
    runCommand(args);
    
  }
  return 0;
}


