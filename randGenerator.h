int randGenerator(int bound){
	signed int seed;	
	FILE *f;
	f = fopen("/dev/urandom", "r");
	if(f == NULL){
		printf("Error: Can not open /dev/urandom.\n");
		return 1;
	}
	fread(&seed, sizeof(seed), 1, f);
	fclose(f);
	srand(seed);
	int randNumb = (rand() % (2*bound+1)) - bound;
	return randNumb;
}
