/* This function prints out the shortest path between the source and destination vertices using the adjacency matrix and the number of vertices. It uses breadth first search algorithm. */

void breadthFirstSearch(int src, int dst, int **matrix, int vertex){
	//Node structure
	struct node{
		char color;
		int distance;
		int parent;
	};

	struct node graphNode[vertex];

	//Initialization
	int i;
	int flag = 0;
	for(i = 0; i < vertex; i++){
		if(i != src){
			graphNode[i].color = 'w';
			graphNode[i].distance = 2500000000;
			graphNode[i].parent = '\0';
		}
	}

	//Assign root properties
	graphNode[src].color = 'g';
	graphNode[src].distance = 0;
	graphNode[src].parent = '\0';

	//Define a queue
	int *queue = malloc(vertex * sizeof(int));
	queue[0] = src;
	queue[1] = '\0';

	int pointer = 0;
	int counter = 1;
	int u;

	//Running algorithm
	while(pointer < counter){
		u = queue[pointer];
		for(i = 0; i < vertex; i++){
			if( matrix[u][i] == 1 && graphNode[i].color == 'w' && u != i){
				graphNode[i].color = 'g';
				graphNode[i].distance = graphNode[u].distance + 1;
				graphNode[i].parent = u;
				queue[counter] = i;
				counter++;
				queue[counter] = '\0';
			}
		} 
		graphNode[u].color = 'b';
		if(u == dst){
			flag = 1;
			break;
		}
		pointer++;
	}

	free(queue);

	if(flag == 1){
		int *result = malloc(vertex * sizeof(int));
		counter = 0;
		u = dst;
		result[counter] = dst;
		counter++;
		result[counter] = '\0';
		while(u != src){
			result[counter] = graphNode[u].parent;
			counter++;
			result[counter] = '\0';
			u = graphNode[u].parent;
		}

		//Print the result
		for(i = counter-1; i > 0; i--)
			printf("%d-", result[i]);
		printf("%d\n", result[0]);
		free(result);
	}
	else
		printf("Error: There is no path between %d and %d vertices.\n", src, dst);

};
