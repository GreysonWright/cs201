//
//  rbt.h
//  Assign_2
//
//  Created by Greyson Wright on 2/24/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef rbt_h
#define rbt_h

#include <stdio.h>
#include "bst.h"

typedef struct rbtValue {
	void *value;
	int frequency;
	int color;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
} rbtValue;

typedef struct rbt {
	bst *tree;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
	int size;
	int words;
} rbt;

rbt *newRBT(void (*)(FILE *, void *), int (*)(void *, void *));
void insertRBT(rbt *, void *);
int findRBT(rbt *, void *);
void deleteRBT(rbt *, void *);
int sizeRBT(rbt *);
int wordsRBT(rbt *);
void statisticsRBT(rbt *, FILE *);
void displayRBT(FILE *, rbt *);
void checkRBT(rbt *);
#endif /* rbt_h */
