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
	tree *bst = newTree(displayInteger, compareInteger);
	insertBST(bst, newInteger(0));
	insertBST(bst, newInteger(2));
	insertBST(bst, newInteger(1));
	
    return 0;
}
