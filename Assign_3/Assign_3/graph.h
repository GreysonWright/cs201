//
//  graph.h
//  Assign_3
//
//  Created by Greyson Wright on 3/21/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//
//	The graph class is simply an adjacency matrix
//	representation of an undirected graph.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include "darray.h"
#include "Vertex.h"

typedef struct Graph {
	DArray *vertices;
	void (*display)(FILE *, void *);
} Graph;

DArray *initDarray(int size, void (*display)(FILE *, void *));
Graph *newGraph(int size, void (*display)(FILE *, void *));
void insertGraph(Graph *graph, int v1, int v2, void *weight);
Vertex *getGraph(Graph *graph, int vertex);
int sizeGraph(Graph *graph);
void displayGraph(FILE *file, Graph *graph);
#endif /* graph_h */
