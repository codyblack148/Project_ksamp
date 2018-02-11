#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "ksamp.h"


int main(int argc, char *argv[]){
  int opt, sample, length;
  int lArg, sArg = 0;
 if(argc ==  1)
	defaultUse();
 else{
	 while ((opt = getopt(argc, argv, "sl:")) != -1) {
               switch (opt) {
               case 's':
                   sArg = TRUE;
                   break;
               case 'l':
		   if(argc != 4){
		   	usage();
			exit(-2); //does not have 2 input numbers.
		   }
		   sample =atoi( argv[2]);
		   length = atoi(argv[3]);
		   lArg = TRUE;
                   break;
               default:
		   usage();
                   	
}
}
}
}
void usage(void){
  printf("Usage: ksamp [-s | -l samp duration]\n");
  printf("-s\t display kernal data\n");
  printf("-l\t display data, calculate avg load.\n");
}

/*
 * show the processor type, kernel version, time since last reboot.
 * No command line parameters
 */

void defaultUse(void){
    char *processorType = getSubStr("/proc/cpuinfo", "model name");
    char *kerVersion = getSubStr("/proc/version","Linux version");
    char *uptime = getSubStr("/proc/uptime",NULL);
    char *timeInSeconds = getEntry(1,uptime," \t");
    printf("Processor Type: %s\n",processorType);
    printf("Kernel Information: %s\n",kerVersion);
    printf("Seconds since last reboot: %s\n",timeInSeconds);
    free(processorType);
    free(kerVersion);
    free(uptime);
    free(timeInSeconds);
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


char *getEntry(int n, const char *str, const char *delims){
	int i = 1;
	char *result = (char *)malloc(MAX_BUF_LEN);
	char temp[MAX_BUF_LEN];

	strcpy(temp,str);
	
	char *token = strtok(temp,delims);
	
	for(i;i<n;i++)
		token = strtok(NULL,delims);
	strcpy(result,token);
	return result;
}


