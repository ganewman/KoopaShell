#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "command.h"


int main(){
  while(1){
    char s[256];
    char path[256];
    printf("%s$ ", getcwd(path, 256));
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

