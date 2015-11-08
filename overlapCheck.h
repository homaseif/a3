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
                if( (w1 >= min(x1,x2) && w1 <= max(x1,x2)) || (z1 >= min(y1,y2) && z1 <= max(y1,y2)) || (w2 >= min(x1,x2) && w2 <= max(x1,x2)) || (z2 >= min(y1,y2) && z2 <= max(y1,y2)) || (x1 >= min(w1,w2$
                        int a = z1 - y1 ;
                        int b = x1 - w1;
                        int c = a * x1 + b * y1;
                        int slopesDifCheck = a1 * b - a * b1;
                        if (slopesDifCheck == 0)
                                overlap = 1; 
                }
        }
        return overlap;
}

