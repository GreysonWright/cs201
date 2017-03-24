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

int getDistance(DArray *distances, int index) {
	integer *distance =  getDArray(distances, index);
	return distance->value;
}

DArray *initArray(int size) {
	DArray *darray = newDArray(displayInteger);
	for (int i = 0; i < size; i++) {
		insertDArray(darray, newInteger(-1));
	}
	return darray;
}

void initSingleSource(Graph *graph, Vertex *source) {
	for (int i = 0; i < sizeGraph(graph); i++) {
		
	}
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
	int source = 0;
//	Binomial *binHeap = dijkstra(graph, source);
//	displayBinomial(stdout, binHeap);
	
    return 0;
}
