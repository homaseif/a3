#include<stdbool.h>

int min(a, b){
        int res = a;
        if( b < a)
                res = b;
        return res;
}

int max(a, b){
        int res = a;
        if(b > a)
                res = b;
        return res;
}


bool overlapCheck(int x1, int y1, int x2, int y2, int w1, int z1, int w2, int z2){
        bool overlap = 0;
        int a1 = y2 - y1;
        int b1 = x1 - x2;
        int c1 = a1 * x1 + b1 * y1;\
        int a2 = z2 - z1;
        int b2 = w1 - w2;
        int c2 = a2 * w1 + b2 * z1;
        int slopesDif = a1 * b2 - a2 * b1;
        if(slopesDif == 0){
                if( (w1 >= min(x1,x2) && w1 <= max(x1,x2)) || (z1 >= min(y1,y2) && z1 <= max(y1,y2)) || (w2 >= min(x1,x2) && w2 <= max(x1,x2)) || (z2 >= min(y1,y2) && z2 <= max(y1,y2)) || (x1 >= min(w1,w2) && x1 <= max(w1,w2)) || (y1 >= min(z1,z2) && y1 <= max(z1,z2)) || (x2 >= min(w1,w2) && x2 <= max(w1,w2)) || (y2 >= min(z1,z2) && y2 <= max(z1,z2)) ){
                        if(x1 == x2 && x2 == w1 && w1 == w2){
				if( (z1 >= min(y1,y2) && z1 <= max(y1,y2)) || (z2 >= min(y1,y2) && z2 <= max(y1,y2)) || (y1 >= min(z1,z2) && y1 <= max(z1,z2)) || (y2 >= min(z1,z2) && y2 <= max(z1,z2)) )
					overlap = 1;
			}
			else if(y1 == y2 && y2 == z1 && z1 == z2){
				if( (w1 >= min(x1,x2) && w1 <= max(x1,x2)) || (w2 >= min(x1,x2) && w2 <= max(x1,x2)) || (x1 >= min(w1,w2) && x1 <= max(w1,w2)) || (x2 >= min(w1,w2) && x2 <= max(w1,w2)) )
					overlap = 1;
			}
			else{
				int a = z1 - y1 ;
                        	int b = x1 - w1;
                        	int c = a * x1 + b * y1;
                        	int slopesDifCheck = a1 * b - a * b1;
                        	if (slopesDifCheck == 0)
                                	overlap = 1;
			} 
                }
        }
        return overlap;
}


bool errorCheck(int i, int j, int x, int y, int **streets, int segmentsNumb){
	bool error = 0;
	//Check length zero segment
	if(j >=2){
		if(x == streets[i][j-2] && y == streets[i][j-1]){
			error = 1;
			return error;
		}
	}
	int p;
	int k;
	//Check overlap with the segments of the current street
	if(j >= 4){
		for(p = j-2; p >= 2; p -= 2){
			error = overlapCheck(streets[i][j-2], streets[i][j-1], x, y, streets[i][p-2], streets[i][p-1], streets[i][p], streets[i][p+1]);
			if(error == 1)
				return error;
		}
	}
	//Check overlap with the segments of the previous streets
	if(i >= 1){
		for(p = i-1; p >= 0; p--){
			for(k = ((2 * (segmentsNumb + 1)) - 2); k >= 2; k -= 2){
				error = overlapCheck(streets[i][j-2], streets[i][j-1], x, y, streets[p][k-2], streets[p][k-1], streets[p][k], streets[p][k+1]);
				if(error == 1)
					return error;
			}
		}
	}

	return error;
}

