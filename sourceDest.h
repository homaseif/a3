/* This function receives an array of characters and the address of source and destination variables to extract the source and destination from the string and store them in those addresses. The format of the array is: 's x y', where x is source node and y is the destination node. */

void sourceDest(char *txt, int *src, int *dst){

	char *enumber1 = malloc(4 * sizeof(char));
	char *enumber2 = malloc(4 * sizeof(char));
	int i = 2;
	int iter = 0;
	while(txt[i] != ' '){
		enumber1[iter] = txt[i];
		iter++;
		i++;
	}
	*src = charToInt(enumber1, iter);
	free(enumber1);
	iter=0;
	i++;
	while(txt[i] != '\0'){
		enumber2[iter] = txt[i];
		iter++;
		i++;
	}
	*dst = charToInt(enumber2,iter);
	free(enumber2);
};
