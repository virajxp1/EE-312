// matrix-multiplication <Project2.cpp>
// EE 312 Project 2 submission by
// Viraj Parikh
// VHP286
// Slip days used: <0>
// Spring 2019

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MatrixMultiply.h"

void multiplyMatrices(double a[], const uint32_t a_rows, const uint32_t a_cols, double b[], const uint32_t b_cols, double c[]) {
    // https://en.wikipedia.org/wiki/Row-_and_column-major_order
    // Matrix A (MxN) Matrix B (NxK) Matrix C (MxK)
    // M = a_rows N = a_cols K = b_cols
    // C has dimensions ( a_rows x b_cols)

    uint32_t c_rows = a_rows;
    uint32_t c_cols = b_cols;
    uint32_t i,j,k;
    double temp_sum = 0;

    i = 0; //i is row
    while(i<c_rows) { 
    	j = 0; //j is column 
    	while(j<c_cols) {
    		k = 0;
    		while(k<a_cols) {
    			temp_sum +=(a[(a_cols * i) + k]) * (b[(k*b_cols)+j]);
    			k++;
    		}
			c[i * c_cols + j]=temp_sum;
			temp_sum =0;
    		j++;
    	}
    	i++;
   	}

}

double** multiplyMatricesPtr(double** a,const uint32_t a_rows,const uint32_t a_cols,double** b,const uint32_t b_cols) {

    uint32_t c_rows = a_rows;
    uint32_t c_cols = b_cols;
    uint32_t i,j,k;

    double** Result =(double**) calloc(c_rows, sizeof(double));
    i = 0; //i is row
    while(i<c_rows) {
        Result[i] = (double*) calloc(c_cols, sizeof(double));
        j = 0; //j is column
        while(j<c_cols) {
            k = 0;
            Result[i][j]=0;
            while(k<a_cols) {
                Result[i][j] +=(a[i][k] * b[k][j]);
                k++;
            }
            j++;
        }
        i++;
    }
    return Result;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(double** a, const uint32_t a_rows,const uint32_t a_cols) {
	int32_t Result_rows = a_cols;
	int32_t Result_cols = a_rows;
    double** Result =(double**) calloc(Result_rows, sizeof(double));
    int32_t i,j;

    for(i=0;i<Result_rows;i++) {
        Result[i] = (double*) calloc(Result_cols, sizeof(double));
        for(j=0;j<Result_cols;j++) {
           Result[i][j] = a[j][i]; //Transpose = flip rows anc columns
        }
    }
    return Result;
}
