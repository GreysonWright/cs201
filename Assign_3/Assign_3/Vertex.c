//
//  Vertex.c
//  Assign_3
//
//  Created by Greyson Wright on 3/23/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include <limits.h>
#include "Vertex.h"

Vertex *newVertex(int name, int *adjacency) {
	Vertex *vertex = malloc(sizeof *vertex);
	vertex->name = name;
	vertex->distance = INT_MAX;
	vertex->adjacency = 0;
	vertex->binNode = 0;
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
	fprintf(file, "%d", vert->distance);
}

void updateVertex(void *value , BinomialNode *node) {
	Vertex *vertex = value;
	vertex->binNode = node;
}
