#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include "randGenerator.h"

int main(int argc, char *argv[]){

	int streetsNumb = 10;
	int lineSegmentsNumb = 5;
	int waitingTime = 5;
	int coordinatesRange = 20;

	int i;
	int j;
	int k;
	for(i = 1; i < argc; i += 2){
		if(strcmp(argv[i], "-s") == 0){
			streetsNumb = atoi(argv[i+1]);//lower bound: 2
		}
		else if(strcmp(argv[i], "-n") == 0) {
			lineSegmentsNumb = atoi(argv[i+1]);//lower bound: 1
		}
		else if(strcmp(argv[i], "-l") == 0){
			waitingTime = atoi(argv[i+1]);//lower bound: 5
		}
		else if(strcmp(argv[i], "-c") == 0){
			coordinatesRange = atoi(argv[i+1]);//lower bound: 1
		}
	}
	int attempts = 1;
	int *randNumb;
	while(1){
		char *streetsName;
		for(i = 0; i < streetsNumb; i++){
			randNumb = malloc(((lineSegmentsNumb+1)*2) * sizeof(int));
			for(j = 0; j < 2*(lineSegmentsNumb+1); j++){
				randNumb[j] = randGenerator(coordinatesRange);
			}
			printf("a \"%d\" ", i);
			k = 0;
			while(k < 2*(lineSegmentsNumb+1)){
				printf("(%d,", randNumb[k]);
				k++;
				printf("%d) ", randNumb[k]);
				k++;
			}
			printf("\n");
			free(randNumb);
		}
		sleep(waitingTime);
	}
	return 0;
}
