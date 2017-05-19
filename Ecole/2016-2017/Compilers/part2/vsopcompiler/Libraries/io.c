#define _GNU_SOURCE
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
  size_t len;
  if(getline(&string, &len, stdin) == -1)
    printf("Error reading line");

  return string;
}

int inputInt32(){
  int i;
  while(scanf("%d", &i) <= 0)
    printf("Enter a correct integer please\n");
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
