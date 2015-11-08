#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "charToInt.h"
#include "extractVertexNumber.h"
#include "createMatrix.h"
#include "sourceDest.h"
#include "breadthFirstSearch.h" 

int main(int argc, char *argv[]){

	int vertex = -1;
	char tmp;
	int flag = 0;
	int **matrix;
	int len;
	char *text;
	char *tmptext;
	int count;
	int freeMatrix = 0;

	while ((tmp = getchar()) != EOF){
  		//Get input, Store in text
  		len = 900000000;
  		text = malloc(len * sizeof(char));
		if(!text){
			printf("Error: The input size is too large.\n");
			flag = 0;
			vertex = -1;
			continue;
		}
  		count = 0;
  		text[count] = tmp;
  		count++;
		text[count] = '\0';
  		while ((tmp = getchar()) != '\n'){
       			if (count >= len){
          			tmptext = realloc(text, (len += 10) * sizeof(*tmptext));
				if(!tmptext){
					printf("Error: The input size is too large.\n");
					flag = 0;
					vertex = -1;
					free(text);
					break;
				}
				text = tmptext;
			}
       			text[count] = tmp;
       			count++;
       			text[count] = '\0';
  		}
		if(!text){
			if(freeMatrix == 1){
				int z;
                		for(z = 0; z < vertex; z++)
                        		free(matrix[z]);
                		free(matrix);
			}
			continue;
		}
  		//V command
  		if(text[0] == 'V'){
  			int vcheck = extractVertexNumber(text, count);
			if(flag == 2 || flag == 3){
				freeMatrix = 0;
				//Free matrix
				int i;
				for(i = 0; i < vertex; i++)
					free(matrix[i]);
				free(matrix);
			}
			if(vcheck < 0){
                                printf("Error: Set of vertices can not be negative.\n");
                                flag = 0;
                                vertex = -1;
                                free(text);
				continue;
                        }
			vertex = vcheck;
			flag = 1;
			free(text);
  		}

  		//E command
  		else if(text[0] == 'E'){
			if(flag == 0 || flag == 3 || flag == 2){
				printf("Error: 'V' has to  be entered before 'E'.\n");
				free(text);
				flag = 0;
				vertex = -1;
				continue;
			}
			int err;
			//Matrix allocation
			matrix = (int **)malloc(vertex * sizeof(int*));
        		int i;
        		for (i = 0; i < vertex; i++)
        			matrix[i] = (int *)malloc(vertex * sizeof(int));
			freeMatrix = 1;
			//Create the adjacency matrix
  			err = createMatrix(text, count, vertex, matrix);
			if(err == 1){
				free(text);
				//free matrix
				int j;
                		for(j = 0; j < vertex; j++)
                      			free(matrix[j]);
                		free(matrix);
				freeMatrix = 0;
				flag = 0;
				vertex = -1;
				continue;
			}
			else{
				flag = 2;
				free(text);
  			}
		}

  		//S command
  		else if(text[0] == 's'){
			if(flag == 0 || flag == 1){
				printf("Error: The graph is not specified completely.\n");
				flag = 0;
				vertex = -1;
				free(text);
				continue;
			}
        		//Get Source & Destination Vertices
			int src;
			int dest;
        		sourceDest(text, &src, &dest);
			if(src < 0 || dest < 0){
				printf("Error: Specified vertices can not be negative.\n");
				free(text);
				continue;
			}
			if( src >= vertex || dest >= vertex){
				if(src >= vertex)
					printf("Error: Shortest path specified for vertex '%d' that does not exist.\n", src);
				if(dest >= vertex)
					printf("Error: Shortest path specified for vertex '%d' that does not exist.\n", dest);
				free(text);
				continue;
 			}
			//Find the shortest pasth between src and dest using breadth first search algorithm
			if(src == dest)
				printf("%d-%d\n", src, dest);
			else
				breadthFirstSearch(src, dest, matrix, vertex);
        		free(text);
  		}
	}
  	if(freeMatrix == 1){
  		int p;
  		for(p = 0; p < vertex; p++)
  			free(matrix[p]);
  		free(matrix);
  	}
  	return 0;
};
