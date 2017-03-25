//
//  darray.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "darray.h"

struct DArray {
	void **array; //an array of void pointers
	int capacity; //total number of slots
	int size; //number of filled slots
	void (*display)(FILE *, void *);
};

DArray *newDArray(void (*display)(FILE *file, void *value)) {
	DArray *darray = malloc(sizeof *darray);
	darray->array = malloc(sizeof *(darray->array));
	darray->array[0] = 0;
	darray->capacity = 1;
	darray->size = 0;
	darray->display = display;
	return darray;
}

void insertDArray(DArray *darray, void *value) {
	if (darray->size == darray->capacity) {
		darray->capacity *= 2;
		darray->array = realloc(darray->array, sizeof *(darray->array) * darray->capacity);
	}
	darray->array[darray->size++] = value;
}

void *removeDArray(DArray *darray) {
	void *value = getDArray(darray, darray->size - 1);
	
	if (darray->size == 0) {
		return 0;
	}
	
	if (darray->capacity * 0.25 > darray->size) {
		darray->capacity /= 2;
		darray->array = realloc(darray->array, sizeof *(darray->array) * darray->capacity);
	}
	
	setDArray(darray, darray->size - 1, 0);
	darray->size--;
	
	return value;
}

void *getDArray(DArray *darray, int index) {
	if (index >= darray->size || index < 0) {
//		fprintf(stderr, "Index out of bounds.");
		return 0;
	}
	return darray->array[index];
}

void setDArray(DArray *darray, int index, void *value) {
	if (index > darray->size || index < 0) {
//		fprintf(stderr, "Index out of bounds.");
		return;
	}
	
	if (index == darray->size) {
		insertDArray(darray, value);
	} else {
		darray->array[index] = value;
	}
}

int sizeDArray(DArray *darray) {
	return darray->size;
}

void displayDArray(FILE *file, DArray *darray) {
	fprintf(file, "[");
	for (int i = 0; i < darray->size; i++) {
		if (darray->array[i] != 0) {
			darray->display(file, darray->array[i]);	
		}
		if (i < darray->size - 1) {
			fprintf(file, ",");
		}
	}
	fprintf(file, "]");
}

