//
//  Password.h
//  AES College
//
//  Created by Janney family on 4/20/23.
//

#ifndef Password_h
#define Password_h

#include <stdio.h>

int SpecialChr(char chr);

void GetPassword(char buffer[33]);
//Start here will commenting

int RotatePasscode(int PasscodeOld[4][4], int PasscodeNew[4][4]);

int KeyExpansion(void);

int SetBits(int x, int *y, int p, int n, int q);

int CreatePasscode(void);

#endif /* Password_h */
