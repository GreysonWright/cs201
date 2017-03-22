//
//  graph.c
//  Assign_3
//
//  Created by Greyson Wright on 3/21/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include "graph.h"
#include "darray.h"
#include "integer.h"

typedef struct Graph {
	DArray *matrix;
	void (*display)(FILE *, void *);
} Graph;

int max(int a, int b) {
	return a > b ? a : b;
}

//int **initMatrix(int capacity) {
//	int **matrix = malloc((sizeof *matrix) * capacity);
//	for (int i = 0; i < capacity; i++) {
//		matrix[i] = malloc((sizeof **matrix) * capacity);
//	}
//	
//	for (int i = 0; i < capacity; i++) {
//		for (int j = 0; j < capacity; j++) {
//			matrix[i][j] = 0;
//		}
//	}
//	return matrix;
//}

//void growMatrix(int **matrix, int oldcapacity, int newcapacity) {
//	matrix = realloc(matrix, (sizeof *matrix) * newcapacity);
//	for (int i = 0; i < oldcapacity; i++) {
//		matrix[i] = realloc(matrix[i], (sizeof **matrix) * newcapacity);
//	}
//	
//	for (int i = oldcapacity; i < newcapacity; i++) {
//		matrix[i] = malloc((sizeof **matrix) * newcapacity);
//	}
//	
//	for (int i = oldcapacity; i < newcapacity; i++) {
//		for (int j = 0; j < newcapacity; j++) {
//			matrix[i][j] = 0;
//		}
//	}
//	
//	for (int i = 0; i < oldcapacity; i++) {
//		for (int j = oldcapacity; j < newcapacity; j++) {
//			matrix[i][j] = 0;
//		}
//	}
//}

Graph *newGraph(int size, void (*display)(FILE *, void *)) {
	Graph *graph = malloc(sizeof *graph);
	graph->display = display;
	graph->matrix = newDArray(display);//initMatrix(capacity);
	
	for (int i = 0; i < size; i++) {
		setDArray(graph->matrix, i, newDArray(display));
	}
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			setDArray(getDArray(graph->matrix, i), j, newInteger(0));
		}
	}
	return graph;
}

void insertGraph(Graph *graph, int e1, int e2, void *weight) {
//	int largestEdge = max(e1, e2);
//	if (largestEdge > graph->capacity) {
//		growMatrix(graph->matrix, graph->capacity, largestEdge * 2);
//		graph->capacity = largestEdge * 2;
//	}
//	graph->matrix[e1][e2] = weight;
	int oldSize = sizeDArray(graph->matrix);
	int size = max(e1, e2) + 1;
	if (size > oldSize) {
		for (int i = oldSize; i < size; i++) {
			setDArray(graph->matrix, i, newDArray(graph->display));
		}
		for (int i = oldSize; i < size; i++) {
			for (int j = 0; j < size; j++) {
				setDArray(getDArray(graph->matrix, i), j, newInteger(0));
			}
		}
	}
	setDArray(getDArray(graph->matrix, e1), e2, weight);
}

void *removeGraph(Graph* graph, int e1, int e2) {
	void *value = getDArray(getDArray(graph->matrix, e2), e1);
	setDArray(getDArray(graph->matrix, e1), e2, newInteger(0));
	return value;
//	int weight = graph->matrix[e1][e2];
//	graph->matrix[e1][e2] = 0;
//	return weight;
}

void *getGraph(Graph *graph, int e1, int e2) {
//	return graph->matrix[e1][e2];
	return getDArray(getDArray(graph->matrix, e1), e2);
}

int sizeGraph(Graph *graph) {
	return sizeDArray(graph->matrix);
}

void displayGraph(FILE *file, Graph *graph) {
	for (int i = 0; i < sizeDArray(graph->matrix); i++) {
			displayDArray(file, getDArray(graph->matrix, i));
		fprintf(file, "\n");
	}
}
