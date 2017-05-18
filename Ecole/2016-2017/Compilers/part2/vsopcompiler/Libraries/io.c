#include <stdio.h>
#include <stdlib.h>

void printInt32(int i){
  printf("printInt32: %d", i);
}

void printBool(short int i){
  printf("printBool: %hd", i);
}

void print(char* string){
  printf("print: %s", string);
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
