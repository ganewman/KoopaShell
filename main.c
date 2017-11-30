#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "command.h"

int runSequence(char *);

int main(){
  while(1){
    char s[256];
    printf("KoopaShell$ "); // FIXME: print command prompt instead
    fgets(s, sizeof(s), stdin);
 
    /* int i;
         for (i = 0; args[i]; i++){
      printf("%s\n", args[i]);
      }*/
    //    runSequence(s);
    char * stripped = stripSpaces(s);
    printf("%p\n", stripped);
    printf("[%s]\n", stripped);
  }
  return 0;
}



int runSequence(char * block){
  if (! block){
    return 0;
  }
  else {
    char * command = strsep(&block, ";");
    printf("successfully separated first command\n");
    printf("[%s]\n", command);
    char ** args = parseCommand(command);
    printf("running command...\n");
    runCommand(args);
    runSequence(block);
	 }
}
