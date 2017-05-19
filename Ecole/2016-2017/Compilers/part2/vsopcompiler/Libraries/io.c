#include <stdio.h>
#include <stdlib.h>

void printInt32(int i){
  printf("%d", i);
}

void printBool(short int i){
  if(i)
    printf("true");
  else
    printf("false");
}

void print(char* string){
  printf("%s", string);
}

//TODO faire proprement en réalouant selon la taille de l'input.
char* inputLine(){
  char* string = NULL;
  int read;
  unsigned int len;
  if(getline(&string, &len, stdin) == -1)
    printf("Error reading line");

  for(int i = 0; i < len; i++)
    if(string[i] == '\n')
      string[i] = '\0';
  return string;
}

int inputInt32(){
  int i;
  scanf("%d", &i);
  char* flushing = inputLine();
  free(flushing);
  return i;
}

short int inputBool(){

  char *val = inputLine();
  if(val[0] == 't'){
    free(val);
    return 1;
  }
  free(val);
  return 0;
}
