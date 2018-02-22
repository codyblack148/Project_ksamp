#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "ksamp.h"


int main(int argc, char *argv[]){
  int opt, sample, length;
 if(argc ==  1)
	defaultUse();
 else{
	 while ((opt = getopt(argc, argv, "sl:")) != -1) {
               switch (opt) {
               case 's':
                   if (argc != 2) {
                     usage();
                     exit(-2);
                   }
                   sInfo();
                   break;
               case 'l':
            		   if(argc != 4){
            		   	usage();
            			  exit(-2); //does not have 2 input numbers.
            		   }
            		   sample =atoi( argv[2]);
            		   length = atoi(argv[3]);
            		   lInfo(sample,length);
                   break;
               default:
		               usage();

}
}
}
return 0;
}
void usage(void){
  printf("\nUsage: ksamp [-s | -l samp duration]\n");
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
    printf("%s\n",processorType);
    printf("Kernel Information: %s\n",kerVersion);
    printf("Seconds since last reboot: %s\n",timeInSeconds);
    free(processorType);
    free(kerVersion);
    free(uptime);
    free(timeInSeconds);
}
/*
 * Show data from default. Also show time processor has been
 * in user mode, system mode, idle, number of disks
 */

void sInfo(void){
    char *cpuStat = getSubStr("/proc/stat","cpu");
    char *userMode = getEntry(3,cpuStat," \t");
    char *idleMode = getEntry(6,cpuStat," \t");
    char *sysMode = getEntry(5,cpuStat," \t");
    //All of these numbers are "jiffies"... need to be divided by 100 for Seconds
    char *diskStats = getSubStr("/proc/diskstats","mmcblk0");
    char *diskReads = getEntry(11,diskStats," \t");
    char *diskWrites = getEntry(15,diskStats," \t");
    /*
     * I am concerned about "sda". That is the format on my machine in Debian
     * but research has told me there are several different versions.
     * If you run this on a system with a different version for diskStats
     * It would not find the correct data.
     */

    defaultUse();
    printf("User mode: %d\n",atoi(userMode)/100);
    printf("Idle mode: %d\n",atoi(idleMode)/100);
    printf("System mode: %d\n",atoi(sysMode)/100);
    printf("Disk reads: %s\n",diskReads);
    printf("Disk writes: %s\n",diskWrites);

    free(cpuStat);
    free(userMode);
    free(idleMode);
    free(sysMode);
    free(diskStats);
    free(diskReads);
    free(diskWrites);
}
/*
 * Show both other outputs, plus amount of memory configured.
 *
 */
void lInfo(int sample, int length){
    char *totalMem = getSubStr("/proc/meminfo","MemTotal");
    char *freeMem = getSubStr("/proc/meminfo","MemFree");
    char *avg;
    sInfo();
    printf("%s\n", totalMem);
    printf("%s\n", freeMem);
    printf("\n1 minute, 5 minutes, 10 minutes, running processes / total processes, most recent proc PID\n");
    int cycles = length / sample;
      int i = 0;
      for(i; i < cycles; i++) {
          avg = getSubStr("/proc/loadavg", NULL);

          printf("%s", avg);

          free(avg);
          sleep(sample);
      }

}
/*
* Return a subtring in fileName using locator.
*/
char *getSubStr(const char *fileName, const char *locator){
  FILE *fp;
  char *result;
  	if((result = (char *)malloc(MAX_BUF_LEN))==NULL){
		printf("Error with memory allocation.");
		exit(-1);
	}
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
      if(result == NULL){
      	printf("%s\n","NULL read from file.");
	free(result);
	exit(-3);//NULL file read
      }
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
		 if(result == NULL){
      		 printf("%s\n","NULL read from file.");
		 free(result);
		 exit(-3);//NULL file read
      		 }

	      return result;
      }
    }
  }


char *getEntry(int n, const char *str, const char *delims){
	int i = 1;
	char *result = NULL;
        char firstTempValue[MAX_BUF_LEN] = {'\0'};
	char *temp[MAX_BUF_LEN] = {'\0'};
	strcpy(firstTempValue,str);
	temp[0]= firstTempValue;
	char *token = strsep(temp,delims);

       	if((result = (char *)malloc(MAX_BUF_LEN)) == NULL){
      		printf("Issue with allocating memory.");
		exit(-4); //issue with memory allocation code.
      }
      

	while(n>1){
		token = strsep(temp,delims);
		n--;
	}
	strcpy(result,token);
	if(result == NULL){
		printf("NULL entry returned, error.");
		exit(-3);
	}
	return result;
}
