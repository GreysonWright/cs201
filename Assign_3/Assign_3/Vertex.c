//
//  Vertex.c
//  Assign_3
//
//  Created by Greyson Wright on 3/23/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "Vertex.h"

Vertex *newVertex(int name, int distance, DArray *adjacency) {
	Vertex *vertex = malloc(sizeof *vertex);
	vertex->name = name;
	vertex->distance = 0;
	vertex->adjacency = newDArray(displayInteger);
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
//
//int getDistanceVertex(void *vertex) {
//	return ((Vertex *)vertex)->distance;
//}
//
//Vertex *getPreviousVertex(Vertex *vertex) {
//	return vertex->previous;
//}

//void addNeighborVertex(Vertex *vertex, integer *neighbor) {
//	setDArray(vertex->neighbors, sizeDArray(vertex->neighbors), neighbor);
//}
//
//DArray *getNeighborsVertex(Vertex *vertex) {
//	return vertex->neighbors;
//}
//
//void addEdgeWeightsVertex(Vertex *vertex, integer *weight) {
//	insertDArray(vertex->edgeWeights, weight);
//}
//
//DArray *getEdgeWeightsVertex(Vertex *vertex) {
//	return vertex->edgeWeights;
//}

void displayVertex(FILE *file, void *vertex) {
	fprintf(file, "%d", getNameVertex(vertex));
}
