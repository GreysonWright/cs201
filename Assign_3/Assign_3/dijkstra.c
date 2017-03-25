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
		graph[i] = calloc(size, (sizeof **graph) * size);
	}
	return graph;
}

int *newVertArray(int size) {
	int *vertArray = calloc(size, (sizeof *vertArray) * size);
	return vertArray;
}

Vertex **newVertObjects(int size) {
	Vertex **vertObjects = calloc(size, (sizeof **vertObjects) * size);
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

Binomial *initSingleSource(int **graph, Vertex **vertObjects, int *vertices, int source, int size) {
	Binomial *binHeap = newBinomial(displayVertex, binHeapComparator, updateVertex);
	for (int i = 0; i < size; i++) {
		if (vertices[i]) {
			BinomialNode *node = insertBinomial(binHeap, vertObjects[i]);
			vertObjects[i]->binNode = node;
		}
	}
	return binHeap;
}

int getWeight(Vertex *current, Vertex *next) {
	int weight = current->adjacency[next->name];
	return weight;
}

void relaxEdge(Vertex *current, Vertex *next) {
	if (current->distance == INT_MAX) {
		current->distance = 0;
	}
	
	int totalDist = getWeight(current, next) + current->distance;
	
	if (next->distance > totalDist) {
		next->distance = totalDist;
		next->previous = current;
	}
}

DArray *dijkstra(int **graph, int *vertices, Vertex **vertObjects, int source, int size) {
	Binomial *binHeap = initSingleSource(graph, vertObjects, vertices, source, size);
	DArray *shortestVerts = newDArray(displayVertex);
	Vertex *current = 0;
	
	while (sizeBinomial(binHeap) > 0) {
		current = extractBinomial(binHeap);
		insertDArray(shortestVerts, current);
		for (int i = 0; i < size; i++) {
			if (vertObjects[i] && current->adjacency[i]) {
				relaxEdge(current, vertObjects[i]);
				if (vertObjects[i]->binNode) {
					decreaseKeyBinomial(binHeap, vertObjects[i]->binNode, vertObjects[i]);
				}
			}
		}
	}
	return shortestVerts;
}

//static void enqueueList(queue *items, Vertex **vertObjects, int *list, int size) {
//	Vertex *vertex = 0;
//	for (int i = 0; i < size; i++) {
//		if (vertObjects[i] && list[i]) {
//			vertex = vertObjects[i];
//		}
//		if (vertex) {
//			enqueue(items, vertex);
//		}
//	}
//}

void printBreadthFirst(FILE *file, DArray *minPath, Vertex **vertObjects) {
	int minPathSize = sizeDArray(minPath);
	int count = 0;
	
	Vertex *vertex = 0;
	Vertex *current = 0;
	
	queue *forrest = newQueue(0);
	queue *items = newQueue(0);
	
	for (int i = 0; i < minPathSize; i++) {
		current = getDArray(minPath, i);
		if (current->previous == 0) {
			enqueue(forrest, current);
		}
	}
	
	if (sizeDArray(minPath) == 0) {
		fprintf(file, "0:\n----");
	}
	
	fprintf(file, "%d: ", count++);
	while (sizeQueue(forrest) > 0) {
		enqueue(items, dequeue(forrest));
		enqueue(items, 0);
		while (sizeQueue(items) > 1) {
			vertex = dequeue(items);
			
			if (vertex == 0) {
				vertex = dequeue(items);
				fprintf(file, "\n");
				fprintf(file, "%d: ", count++);
				enqueue(items, 0);
			}
			
			if (vertex) {
				displayVertex(file, vertex);
				
				if (peekQueue(items) != 0) {
					fprintf(file, " ");
				}
				
				for (int i = 0; i < minPathSize; i++) {
					current = getDArray(minPath, i);
					if (current->previous == vertex) {
						enqueue(items, current);
					}
				}
			}
		}
		count = 0;
		fprintf(file, "\n----");
	}
	fprintf(file, "\n");
}


int main(int argc, const char *argv[]) {
	int maxSize = 0;
	int minSize = INT_MAX;
	FILE *file = fopen(argv[1], "r");
	queue *inputQueue = newQueue(displayInteger);
	
	int v1 = 0;
	int v2 = 0;
	int weight = 0;
	char *tmp = 0;
	while (1) {
		v1 = readInt(file);
		v2 = readInt(file);
		tmp = readToken(file);
		
		if (feof(file)) {
			break;
		}
		
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
	fclose(file);
	
	int **graph = newGraph(maxSize);
	int *vertices = newVertArray(maxSize);
	Vertex **vertObjects = newVertObjects(maxSize);
	integer *v1Integer = 0;
	integer *v2Integer = 0;
	integer *weightInteger = 0;
	
	while (sizeQueue(inputQueue) > 0) {
		v1Integer = dequeue(inputQueue);
		v2Integer = dequeue(inputQueue);
		weightInteger = dequeue(inputQueue);
		graph[v1Integer->value][v2Integer->value] = weightInteger->value;
		graph[v2Integer->value][v1Integer->value] = weightInteger->value;
		vertices[v1Integer->value] = 1;
		vertices[v2Integer->value] = 1;
	}
	
	Vertex *vert = 0;
	for (int i = 0; i < maxSize; i++) {
		if (vertices[i]) {
			vert = newVertex(i, graph[i]);
			if (i == minSize) {
				vert->distance = 0;
			}
			vertObjects[i] = vert;
		}
	}
	
	DArray *minPath = dijkstra(graph, vertices, vertObjects, minSize, maxSize);
	printBreadthFirst(stdout, minPath, vertObjects);
	
    return 0;
}
