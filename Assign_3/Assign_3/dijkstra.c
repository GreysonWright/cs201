//
//  main.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include "integer.h"
#include "binomial.h"
#include "Vertex.h"
#include "scanner.h"
#include "queue.h"

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

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int **newGraph(int size) {
	int **graph = malloc((sizeof *graph) * size);
	for (int i = 0; i < size; i++) {
		graph = calloc(size, (sizeof *graph) * size);
	}
	return graph;
}

int *newVertArray(int size) {
	int *vertArray = calloc(size, (sizeof *vertArray) * size);
	return vertArray;
}

Vertex **newVertObjects(int size) {
	Vertex **vertObjects = calloc(size, (sizeof *vertObjects) * size);
	return vertObjects;
}

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

Binomial *initSingleSource(int **graph, Vertex ***vertObjects, int *vertices, int source, int size) {
	Binomial *binHeap = newBinomial(displayVertex, compareVertex, updateVertex);
	Vertex *vertex = 0;
	for (int i = 0; i < size; i++) {
		if (vertices[i]) {
			vertex = newVertex(i, graph[i]);
			if (i == source) {
				vertex->distance = 0;
			}
			insertBinomial(binHeap, vertex);
		}
	}
	return binHeap;
}

int getWeight(Vertex *previous, Vertex *current) {
	int weight = previous->adjacency[current->name];
	return weight;
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

DArray *dijkstra(int **graph, int *vertices, Vertex **vertObjects, int source, int size) {
	Binomial *binHeap = initSingleSource(graph, &vertObjects, vertices, source, size);
	DArray *shortestVerts = newDArray(displayVertex);
	Vertex *previous = 0;
	while (sizeBinomial(binHeap) > 0) {
		previous = extractBinomial(binHeap);
		insertDArray(shortestVerts, previous);
		for (int i = 0; i < size; i++) {
			relaxEdge(previous, vertObjects[previous->adjacency[i]]);
		}
	}
	return shortestVerts;
}

int main(int argc, const char *argv[]) {
	int maxSize = 0;
	int minSize = INT_MAX;
	FILE *file = fopen(argv[1], "r");
	queue *inputQueue = newQueue(0);
	
	int v1 = 0;
	int v2 = 0;
	int weight = 0;
	char *tmp = 0;
	while (1) {
		if (feof(file)) {
			break;
		}
		v1 = atoi(readToken(file));
		v2 = atoi(readToken(file));
		minSize = min(minSize, min(v1, v2));
		maxSize = max(maxSize, max(v1, v2));
		if (tmp[0] != ';') {
			weight = atoi(tmp);
			readToken(file);
		} else {
			weight = 1;
		}
		enqueue(inputQueue, newInteger(v1));
		enqueue(inputQueue, newInteger(v2));
		enqueue(inputQueue, newInteger(weight));
	}
	maxSize++;
	
	int **graph = newGraph(maxSize);
	int *vertices = newVertArray(maxSize);
	Vertex **vertObjects = newVertObjects(maxSize);
	integer *v1Integer = dequeue(inputQueue);
	integer *v2Integer = dequeue(inputQueue);
	integer *weightInteger = dequeue(inputQueue);
	
	while (sizeQueue(inputQueue) > 0) {
		graph[v1Integer->value][v2Integer->value] = weightInteger->value;
		graph[v2Integer->value][v1Integer->value] = weightInteger->value;
		vertices[v1Integer->value] = 1;
		vertices[v2Integer->value] = 1;
		v1Integer = dequeue(inputQueue);
		v2Integer = dequeue(inputQueue);
		weightInteger = dequeue(inputQueue);
	}
	
	Vertex *vert = 0;
	for (int i = 0; i < maxSize; i++) {
		if (vertices[i]) {
			vert = newVertex(i, graph[i]);
		}
	}
	
    return 0;
}
