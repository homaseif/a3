#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "randGenerator.h"
#include "errorCheck.h"

int main(int argc, char *argv[]){
	int flag = 0;
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
	int attempts = 0;//for unseccssful tries
	int attemptsBound = 25;
	int xtmp;
	int ytmp;
	while(1){
		if(flag == 1){
			for(i = 0; i < streetsNumb; i++)
                        	printf("r \"%d\"\n", i);
		}
		flag = 1;
		int **streets;
		streets = (int **)malloc(streetsNumb * sizeof(int *));
		for(i = 0; i < streetsNumb; i++)
			streets[i] = (int *)malloc((2*(lineSegmentsNumb+1)) * sizeof(int));

		for(i = 0; i < streetsNumb; i++){
			for(j = 0; j < 2*(lineSegmentsNumb+1); j += 2){
				bool err = 0;
				do{
					attempts++;
					xtmp = randGenerator(coordinatesRange);//check error
					ytmp = randGenerator(coordinatesRange);
					err = errorCheck(i, j, xtmp, ytmp, streets, lineSegmentsNumb);
				} while(err == 1 && attempts < attemptsBound);
				if(err == 0){
					streets[i][j] = xtmp;//add temp to streets if there is no error
					streets[i][j+1] = ytmp;
				}
				else if(err == 1){
					fprintf(stderr, "Error: failed to generate valid input for %d simultaneous attempts.\n", attemptsBound);
					int K;
					for(k = 0; k < streetsNumb; k++)
						free(streets[k]);
					free(streets);
					return 1;

				}
			}
		}

		for(i = 0; i < streetsNumb; i++){
			printf("a \"%d\" ", i);
			j = 0;
			while(j < 2*(lineSegmentsNumb+1)){
				printf("(%d,", streets[i][j]);
				j++;
				printf("%d) ", streets[i][j]);
				j++;
                        }
			printf("\n");
                }
		printf("g\n");

		for(i = 0; i < streetsNumb; i++)
  			free(streets[i]);
  		free(streets);

		sleep(waitingTime);


	}
	return 0;
}
