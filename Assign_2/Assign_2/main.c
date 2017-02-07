//
//  main.c
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include "tree.h"
#include "integer.h"
#include "real.h"
#include "string.h"

int main(int argc, const char * argv[]) {
//	tree *bst = newTree(displayInteger, compareInteger);
//	insertBST(bst, newInteger(10));
//	insertBST(bst, newInteger(10));
//	insertBST(bst, newInteger(5));
//	insertBST(bst, newInteger(20));
//	insertBST(bst, newInteger(2));
//	insertBST(bst, newInteger(17));
//	insertBST(bst, newInteger(9));
//	removeBST(bst, newInteger(10));
//	removeBST(bst, newInteger(10));
//	removeBST(bst, newInteger(9));
//	removeBST(bst, newInteger(2));
//	displayTree(stdout, bst);
	
	tree *rbt = newTree(displayInteger, compareInteger);
	insertRBT(rbt, newInteger(10));
	insertRBT(rbt, newInteger(9));
	insertRBT(rbt, newInteger(8));
	displayTree(stdout, rbt);
    return 0;
}
