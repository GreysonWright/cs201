//
//  Vertex.c
//  Assign_3
//
//  Created by Greyson Wright on 3/23/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "Vertex.h"

Vertex *newVertex(int name, int distance, DArray *adjacency, void (*display)(FILE *, void *)) {
	Vertex *vertex = malloc(sizeof *vertex);
	vertex->name = name;
	vertex->distance = 0;
	vertex->adjacency = newDArray(display);
	return vertex;
}

int compareVertex(void *left, void *right) {
	Vertex *leftVert = left;
	Vertex *rightVert = right;
	int difference = leftVert->distance - rightVert->distance;
	if (difference == 0) {
		difference = leftVert->name - rightVert->name;
	}
	return difference;
}

int getNameVertex(void *vertex) {
	return ((Vertex *)vertex)->name;
}

void displayVertex(FILE *file, void *vertex) {
	Vertex *vert = vertex;
	if (vert) {
		fprintf(file, "Vertex { name = %d, distance = %d, adjacency = ", vert->name, vert->distance);
		displayDArray(file, vert->adjacency);
		fprintf(file, " }");
	} else {
		fprintf(file, "Vertex { NULL }");
	}
}
