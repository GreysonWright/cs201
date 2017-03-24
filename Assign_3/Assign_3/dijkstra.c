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

//DArray *buildVertices(Graph *graph, int distance) {
//	int graphSize = sizeGraph(graph);
//	DArray *vertices = newDArray(displayVertex);
//	for (int i = 0; i < graphSize; i++) {
//		setDArray(vertices, i, newVertex(i, distance, getAdjacencyGraph(graph, i)));
//	}
//	return vertices;
//}

Binomial *initBinHeap(Graph *graph, DArray *vertices) {
	Binomial *binHeap = newBinomial(displayVertex, binHeapComparator, 0);
//	DArray *vertices = buildVertices(graph, 0);
	for (int i = 0; i < sizeGraph(graph); i++) {
		insertBinomial(binHeap, getDArray(vertices, i));
	}
	return binHeap;
}

DArray *initSingleSource(Graph *graph, Vertex *source) {
	int graphSize = sizeGraph(graph);
	DArray *vertices = newDArray(displayVertex);
	integer *vertex = 0;
	for (int i = 0; i < graphSize; i++) {
		for (int j = 0; j < graphSize; j++) {
			vertex = getGraph(graph, i, j);
			if (vertex->value != 0) {
				setDArray(vertices, i, newVertex(i, INT_MAX, getAdjacencyGraph(graph, i)));
				break;
			}
			
		}
	}
//	DArray *vertices = buildVertices(graph, INT_MAX);
	source->distance = 0;
	return vertices;
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
	DArray *vertices = initSingleSource(graph, newVertex(source, 0, getAdjacencyGraph(graph, 0)));
	DArray *shortestVerts = newDArray(displayVertex);
	Binomial *binHeap = initBinHeap(graph, vertices);
	Vertex *previous = 0;
	while (sizeBinomial(binHeap)) {
		previous = extractBinomial(binHeap);
		insertDArray(shortestVerts, previous);
		for (int i = 0; i < sizeDArray(vertices); i++) {
			relaxEdge(previous, getDArray(vertices, i));
		}
	}
	return shortestVerts;
}

//Binomial *dijkstra(Graph *graph, int source) {
//	Binomial *binHeap = newBinomial(displayVertex, compareVertex, 0);
//	DArray *distance = initArray(sizeGraph(graph));
//	DArray *previous = initArray(sizeGraph(graph));
//	Vertex *bestVert = 0;
//	DArray *bestNeighbors = 0;
//	int neighborName = 0;
//	int alt = 0;
//	
//	setDArray(distance, source, newInteger(0));
//	
//	int graphSize = sizeGraph(graph);
//	for (int i = 0; i < graphSize; i++) {
//		for (int j = 0; j < graphSize; i++) {
//			if (getGraph(graph, i, j)->value != 0) {
//				if (i != source) {
//					setDArray(distance, j, newInteger(INT_MAX));
//					setDArray(previous, j, newInteger(-1));
//				}
//				Vertex *vert = newVertex(j, getDistance(distance, j));
////				addNeighbor(vert, <#Vertex *#>)
//				insertBinomial(binHeap, vert);
//			}
//		}
//	}
//	
//	while (sizeBinomial(binHeap)) {
//		bestVert = extractBinomial(binHeap);
//		bestNeighbors = getNeighborsVertex(bestVert);
//		
//		for (int i = 0; i < sizeDArray(bestNeighbors); i++) {
//			alt = getDistance(distance, i) + getNeighborWeight(bestVert, i);
//			neighborName = getNeighborName(bestVert, i);
//			if (alt < getDistance(distance, neighborName)) {
//				setDArray(distance, neighborName, newInteger(alt));
//				setDArray(previous, getNameVertex(bestVert), newInteger(alt));
//				
//			}
//		}
//	}
//	
//	return binHeap;
//}

int main(int argc, const char * argv[]) {
	Graph *graph = newGraph(10, displayInteger);
	insertGraph(graph, 1, 2, newInteger(1));
	insertGraph(graph, 2, 3, newInteger(2));
	insertGraph(graph, 3, 1, newInteger(3));
	int source = 1;
	DArray *st00f = dijkstra(graph, source);
	displayDArray(stdout, st00f);
//	Binomial *binHeap = dijkstra(graph, source);
//	displayBinomial(stdout, binHeap);
    return 0;
}
