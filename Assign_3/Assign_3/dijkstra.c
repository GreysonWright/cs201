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
	
	for (int i = 0; i < sizeGraph(graph); i++) {
		for (int j = 0; j < sizeGraph(graph); j++) {
			insertBinomial(binHeap, getGraph(graph, i, j));
		}
	}
	
    return 0;
}
