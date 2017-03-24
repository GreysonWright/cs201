//
//  main.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include "integer.h"
#include "binomial.h"
#include "graph.h"
#include "Vertex.h"

//int getNeighborWeight(Vertex *vertex, int index) {
//	DArray *weights = getEdgeWeightsVertex(vertex);
//	integer *weight = getDArray(weights, index);
//	return weight->value;
//}
//
//int getNeighborName(Vertex *vertex, int index) {
//	DArray *neighbors = getNeighborsVertex(vertex);
//	integer *neighbor = getDArray(neighbors, index);
//	return neighbor->value;
//}

//int getDistance(DArray *distances, int index) {
//	integer *distance =  getDArray(distances, index);
//	return distance->value;
//}

int binHeapComparator(void *left, void *right) {
	if (left == 0 && right == 0) {
		return 0;
	}
	
	if (left == 0) {
		return -1;
	}
	
	if (right == 0) {
		return 1;
	}
	
	return compareVertex(left, right);
}

DArray *initArray(int size) {
	DArray *darray = newDArray(displayInteger);
	for (int i = 0; i < size; i++) {
		insertDArray(darray, newInteger(-1));
	}
	return darray;
}

Binomial *initBinHeap(Graph *graph) {
	Binomial *binHeap = newBinomial(displayVertex, binHeapComparator, 0);
	Vertex *vertex = 0;
	for (int i = 0; i < sizeGraph(graph); i++) {
		vertex = getGraph(graph, i);
		if (vertex) {
			insertBinomial(binHeap, vertex);
		}
	}
	return binHeap;
}

void initSingleSource(Graph *graph, Vertex *source) {
	int graphSize = sizeGraph(graph);
	Vertex *vertex = 0;
	for (int i = 0; i < graphSize; i++) {
		vertex = getGraph(graph, i);
		if (vertex) {
			vertex->distance = INT_MAX;
			vertex->previous = 0;
		}
	}
	source->distance = 0;
}

int getWeight(Vertex *previous, Vertex *current) {
	integer *weight = getDArray(previous->adjacency, current->name);
	return weight->value;
}

void relaxEdge(Vertex *previous, Vertex *current) {
	int totalDist = 0;
	if (previous != 0) {
		totalDist = getWeight(previous, current) + previous->distance;
	}
	if (current->distance > totalDist) {
		current->distance = totalDist;
		current->previous = previous;
	}
}

DArray *dijkstra(Graph *graph, int source) {
	initSingleSource(graph, getGraph(graph, source));
	DArray *shortestVerts = newDArray(displayVertex);
	Binomial *binHeap = initBinHeap(graph);
	Vertex *previous = 0;
	while (sizeBinomial(binHeap) > 0) {
		previous = extractBinomial(binHeap);
		insertDArray(shortestVerts, previous);
		for (int i = 0; i < sizeDArray(previous->adjacency); i++) {
			relaxEdge(previous, getDArray(previous->adjacency, i));
		}
	}
	return shortestVerts;
}

int main(int argc, const char * argv[]) {
	Graph *graph = newGraph(10, displayInteger);
	insertGraph(graph, 1, 2, newInteger(1));
	insertGraph(graph, 2, 3, newInteger(2));
	insertGraph(graph, 3, 1, newInteger(3));
	displayGraph(stdout, graph);
//	int source = 1;
//	DArray *st00f = dijkstra(graph, source);
//	displayDArray(stdout, st00f);
    return 0;
}
