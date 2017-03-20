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

int main(int argc, const char * argv[]) {
	Binomial *binHeap = newBinomial(displayInteger, compareInteger, 0);
	insertBinomial(binHeap, newInteger(4));
	insertBinomial(binHeap, newInteger(8));
	insertBinomial(binHeap, newInteger(16));
	insertBinomial(binHeap, newInteger(5));
	insertBinomial(binHeap, newInteger(1));
	displayBinomial(stdout, binHeap);
	
    return 0;
}
