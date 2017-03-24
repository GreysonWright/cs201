//
//  graph.c
//  Assign_3
//
//  Created by Greyson Wright on 3/21/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "graph.h"

DArray *initDarray(int size, void (*display)(FILE *, void *)) {
	DArray *darray = newDArray(display);
	for (int i = 0; i < size; i++) {
		setDArray(darray, i, 0);
	}
	return darray;
}

Vertex *initVertex(int name, int vertex2, void *weight, Graph *graph) {
	DArray *adjacency = initDarray(sizeGraph(graph), graph->display);
	setDArray(adjacency, vertex2, weight);
	Vertex *vertex = newVertex(name, 0, adjacency, graph->display);
	return vertex;
}

Graph *newGraph(int size, void (*display)(FILE *, void *)) {
	Graph *graph = malloc(sizeof *graph);
	graph->display = display;
	graph->vertices = initDarray(size, display);
	
	return graph;
}

void insertGraph(Graph *graph, int v1, int v2, void *weight) {
	Vertex *vert1 = getGraph(graph, v1);
	Vertex *vert2 = getGraph(graph, v2);
	if (vert1) {
		setDArray(vert1->adjacency, v2, weight);
	} else {
		vert1 = initVertex(v1, v2, weight, graph);
		setDArray(graph->vertices, v1, vert1);
	}
	
	if (vert2) {
		setDArray(vert2->adjacency, v2, weight);
	} else {
		vert2 = initVertex(v2, v1, weight, graph);
		setDArray(graph->vertices, v2, vert2);
	}
}

Vertex *getGraph(Graph *graph, int vertex) {
	return getDArray(graph->vertices, vertex);
}

int sizeGraph(Graph *graph) {
	return sizeDArray(graph->vertices);
}

void displayGraph(FILE *file, Graph *graph) {
	for (int i = 0; i < sizeDArray(graph->vertices); i++) {
		displayVertex(file, getGraph(graph, i));
		fprintf(file, "\n");
	}
}
