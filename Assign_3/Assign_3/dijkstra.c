//
//  main.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include "integer.h"
#include "binomial.h"
#include "graph.h"

int main(int argc, const char * argv[]) {
	Binomial *binHeap = newBinomial(displayInteger, compareInteger, 0);
	Graph *graph = newGraph(10, displayInteger);
//	insertGraph(graph, 9, 2, newInteger(10));
	for (int i = 0; i < sizeGraph(graph); i++) {
		for (int j = 0; j < sizeGraph(graph); j++) {
			insertGraph(graph, i, j, newInteger(i + j));
		}
	}
//
	insertGraph(graph, 10, 10, newInteger(4));
	displayGraph(stdout, graph);
	
//	for (int i = 0; i < capacityGraph(graph); i++) {
//		for (int j = 0; j < capacityGraph(graph); j++) {
//			insertBinomial(binHeap, newInteger(getGraph(graph, i, j)));
//		}
//	}
	
    return 0;
}
