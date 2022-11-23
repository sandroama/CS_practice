//
// Created by Sandro Amaglobeli on 11/1/22.
//

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<cstdio>

using namespace std;

// order directions n, ne, e, se, s, sw, w, nw
const int8_t DX[] = {0,1,1,1,0,-1,-1,-1};
const int8_t DY[] = {-1,-1,0,1,1,1,0,-1};

// place these in your own file
unsigned int next_generation(bool* A, bool* B, int rows, int columns){
    int changes =0;
    for (int x = 0; x < columns; x++) {
        for (int y = 0; y < rows; ++y) {

            int alive=0;
            int cur = y*columns+x;
            for (int n = 0; n < 8; ++n) { // Checking for Neighbors
                int nx = x +DX[n];
                int ny = y +DX[n];
                if( A[ny*columns+nx]
                    && nx>=0 && nx<=columns
                    && ny>=0 && ny<rows)
                {
                    alive++;
                }
            }

            B[y*columns+x]=A[y*columns+x];//copying
            if(A[y*columns+x]==1 && alive!=2 & alive!=3){
                B[y*columns+x]=0;
                changes++;
            }
            else if(A[y*columns+x]==0 && alive ==3 ){
                B[y*columns+x]=1;
                changes++;
            }


//            // Template
//            if(x>0 && A[(y)*columns+(x-1)]==1) alive++;
//            // Left
//            if(x>0 && A[(y)*columns+(x-1)]==1) alive++;
//            // right

        }
    }
    return changes;
};


