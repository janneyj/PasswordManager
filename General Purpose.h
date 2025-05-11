//
//  General Purpose.h
//  AES College
//
//  Created by Janney family on 4/20/23.
//

#ifndef General_Purpose_h
#define General_Purpose_h

#include <stdio.h>

int ChartLookNew(int *ptr_chart, int row, int column, int totalrow);

int Print (int *chart, int row, int column);

int Substitute(int Chart[16][16], int W_KE[4][4]);

void Addition(int *chr, int *pass);

void Shift(int *words, int rotate);

void MixColumns(int *words, int *mult);

void copy(int *orginal, int *copy, int length);

int Multiply(int *cptr, int *rptr);

#endif /* General_Purpose_h */
