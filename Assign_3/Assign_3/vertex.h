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
#include "binomial.h"

typedef struct Vertex {
	int name;
	int distance;
	struct Vertex *previous;
	int *adjacency;
	BinomialNode *binNode;
} Vertex;

Vertex *newVertex(int , int *);
int compareVertex(void *, void *);
void displayVertex(FILE *, void *);
void updateVertex(void * , BinomialNode *);
#endif /* Vertex_h */
