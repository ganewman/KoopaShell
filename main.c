#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char * argv[]){
  while(1){
    char s[256];
    printf("Please type a command:\n"); // FIXME: print command prompt instead
    fgets(s, sizeof(s), stdin);
    // printf("%s\n", s);

  }
  return 0;
}


