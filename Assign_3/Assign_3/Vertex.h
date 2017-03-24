//
//  Vertex.h
//  Assign_3
//
//  Created by Greyson Wright on 3/23/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#include <stdio.h>
#include "darray.h"

typedef struct Vertex {
	int name;
	int distance;
	struct Vertex *previous;
	DArray *adjacency;
} Vertex;

Vertex *newVertex(int name, int distance, DArray *adjacency, void (*)(FILE *, void *));
int getNameVertex(void *);
//int getDistanceVertex(void *);
//void addNeighborVertex(Vertex *, integer *);
//DArray *getNeighborsVertex(Vertex *);
//void addEdgeWeightsVertex(Vertex *, integer *);
//DArray *getEdgeWeightsVertex(Vertex *);
int compareVertex(void *, void *);
void displayVertex(FILE *, void *);
#endif /* Vertex_h */