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

typedef struct Graph Graph;

Graph *newGraph(int, void (*)(FILE *, void *));
void insertGraph(Graph * ,int, int, void *);
void *removeGraph(Graph *, int, int);
void *getGraph(Graph *, int, int);
void displayGraph(FILE *, Graph *);
int sizeGraph(Graph *);
#endif /* graph_h */
