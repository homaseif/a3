/* This function receives an array of characters which specify a set of edges in the format: 'E {<x1,y1>,...,<xn,yn>}', the size of array, the number of vertices and a pointer to a 2 dimensional matrix. The outcome of this function is the adjacency matrix of the specified graph.  */

int createMatrix(char *txt, int size, int vertex, int **mat){
	//Initialize matrix 
	int err = 0;
	int i;
	int j;
	for (i = 0; i < vertex; i++){
		for (j = 0; j < vertex; j++){
			if (i == j)
				mat[i][j] = 1;
			else
            			mat[i][j] = 0;
		}
	}
	//Retouch the matrix to build the adjacency matrix of the graph
	int n = 3;
	while (n < size){
		char *node1 = malloc(5 * sizeof(char));
		char *node2 = malloc(5 * sizeof(char));
		if (txt[n] == '<'){
			int counter1 = 0;
			n++;
			while (txt[n] != ','){
				node1[counter1] = txt[n];
				counter1++;
				n++;
			}
			int a;
			a = charToInt(node1,counter1);
			free(node1);
			if (a < 0){
				printf("Error: Vertex identifier can not be negative.\n");
				err = 1;
				break;
			}
			if (a >= vertex){
				printf("Error: An edge specified for Vertex '%d' that does not exist.\n", a);
				err = 1;
				break;
			}
			n++;
			int counter2 = 0;
			while (txt[n] != '>'){
				node2[counter2] = txt[n];
				counter2++;
				n++;
			}
			int b;
			b = charToInt(node2,counter2);
			free(node2);
			if (b < 0){
				printf("Error: Vertex identifier can not be negative.\n");
				err = 1;
				break;
			}
			if (b >= vertex){
				printf("Error: An edge specified for Vertex '%d' that  does not exist.\n", b);
				err = 1;
				break;
			}
			mat[a][b] = 1;
			mat[b][a] = 1;
			n = n + 2;
		}
		else
			return err;
	}
	return err;
};
