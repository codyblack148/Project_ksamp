#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "ksamp.h"


int main(int argc, char *argv[]){

  bool lArg = false;
  bool sArg = false;

}

void usage(void){
  printf("Usage: ksamp [-s | -l samp duration]\n");
  printf("-s\t display kernal data\n");
  printf("-l\t display data, calculate avg load.\n");
}

void defaultUse(void){


}

void sInfo(void){

}

void lInfo(int sample, int length){

}
/*
* Return a subtring in fileName using locator.
*/
char *getSubStr(const char *fileName, const char *locator){
  FILE *fp;
  char *result = (char *)malloc(MAX_BUF_LEN);
  fp =fopen(fileName,"r");
  if(fp == NULL){
    perror("Error: ");
    exit(-1);
  }
/*
 * If locator is equal to NULL, return first line
 */
  if(locator == NULL){
    if (fgets(result,MAX_BUF_LEN,fp) != NULL) {
      fclose(fp);
      return result;
    }
  /*
   * Cycle through entire file. If the locator substring
   * is found in result, return that line.
   */
    while(fgets(result,MAX_BUF_LEN,fp) != NULL){
      if (strstr(result,locator) != NULL) {
        fclose(fp);
        return result;
      }
    }
  }

}
char *getEntry(int n, const char *str, const char *delims){

}
