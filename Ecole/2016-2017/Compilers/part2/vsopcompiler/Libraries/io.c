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

int inputInt32(){
  int i;
  scanf("%d", &i);
  return i;
}

short int inputBool(){
  short int i;
  scanf("%hd", &i);
  return i;
}

//TODO faire proprement en réalouant selon la taille de l'input.
char* inputLine(){
  char* string = malloc(sizeof(char)*1000);
  scanf("%s", string);
  return string;
}
