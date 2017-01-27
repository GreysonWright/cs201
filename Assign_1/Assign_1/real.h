//
//  real.h
//  Assign_1
//
//  Created by Greyson Wright on 1/27/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef __REAL_INCLUDED__
#define __REAL_INCLUDED__

#include <stdio.h>

typedef struct real
{
	double value;
} real;

real *newReal(double);
double getReal(real *);
double setReal(real *, double);
void displayReal(FILE *, void *);
int compareReal(void *, void *);
void freeReal(real *);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif

