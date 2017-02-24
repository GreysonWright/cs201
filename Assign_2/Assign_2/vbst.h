//
//  vbst.h
//  Assign_2
//
//  Created by Greyson Wright on 2/22/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef vbst_h
#define vbst_h

#include <stdio.h>
#include "bst.h"

typedef struct vbstValue {
	void *value;
	int frequency;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
} vbstValue;

typedef struct vbst {
	bst *tree;
	void (*display)(FILE *, void *);
	int (*compare)(void *, void *);
	int size;
	int words;
}vbst;

vbst *newVBST(void (*)(FILE *, void *), int (*)(void *, void *));
bstNode *insertVBST(vbst *, void *);
bstNode *deleteVBST(vbst *, void *);
int findVBST(vbst *, void *);
void statisticsVBST(vbst *, FILE *);
void displayVBST(vbst *, FILE *);
#endif /* vbst_h */
