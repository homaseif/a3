/* This function extract the number of vertices from an array of characters like: 'V x'. 'x' can be any number. The function receives the array and its size as inputs and return an integer.*/
 
int extractVertexNumber(char *txt, int size){
	int vertex;
	char *vnumber = malloc( (size-2) * sizeof(char) );
	int i;
	for (i = 2; i < size; i++)
		vnumber[i-2] = txt[i];
	vertex = charToInt(vnumber, size-2);
	free(vnumber);
	return vertex;
};
