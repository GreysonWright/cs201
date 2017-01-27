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

real *newReal(float rl) {
	real *newRl = malloc(sizeof *newReal);
	if (newRl == 0) {
		fprintf(stderr, "Out of memory.");
		exit(-1);
	}
	newRl->value = rl;
	return newRl;
}

float getReal(real *rl) {
	return rl->value;
}

float setReal(real *rl, float newVal) {
	float oldRl = rl->value;
	rl->value = newVal;
	return oldRl;
}

void displayReal(FILE *file, void *rl) {
	fprintf(file ,"%.1lf", getReal(rl));
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
	free(rl);
}
