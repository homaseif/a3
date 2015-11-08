/* This is a function to convert an array of characters to an integer. The inputs are the array of characters and the size of the array. Characters has to be between '-9' and '9'.*/

int charToInt (char *number, int count){
	int multiple = 10;
	int result;
	int i;
	result = number[count - 1] - '0';
	for (i = count - 2; i >= 0; i--){
		result = result + ( number[i] - '0') * multiple;
		multiple = multiple * 10;
	}
	return result;
};

