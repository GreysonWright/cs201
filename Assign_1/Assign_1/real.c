//
//  real.c
//  Assign_1
//
//  Created by Greyson Wright on 1/27/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "real.h"

real *newReal(double rl) {
	real *newRl = malloc(sizeof *newReal);
	if (newRl == 0) {
		fprintf(stderr, "Out of memory.");
		exit(-1);
	}
	newRl->value = rl;
	return newRl;
}

double getReal(real *rl) {
	return rl->value;
}

double setReal(real *rl, double newVal) {
	double oldRl = rl->value;
	rl->value = newVal;
	return oldRl;
}

void displayReal(FILE *file, void *rl) {
	fprintf(file ,"%lf", getReal(rl));
}

int compareReal(void *left, void *right) {
	if (getReal(left) < getReal(right)) {
		return -1;
	}
	if (getReal(left) > getReal(right)) {
		return 1;
	}
	return 0;
}

void freeReal(real *rl) {
	rl->value = 0;
	free(rl);
}
