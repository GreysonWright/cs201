//
//  comparator.c
//  Assign_1
//
//  Created by Greyson Wright on 2/7/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "comparator.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "vbst.h"
#include "rbt.h"

int vbstIntComparator(void *left, void *right) {
	vbstValue *leftVal = left;
	vbstValue *rightVal = right;
	return compareInteger(leftVal->value, rightVal->value);
}

int vbstRealComparator(void *left, void *right) {
	vbstValue *leftVal = left;
	vbstValue *rightVal = right;
	return compareInteger(leftVal->value, rightVal->value);
}

int vbstStringComparator(void *left, void *right) {
	vbstValue *leftVal = left;
	vbstValue *rightVal = right;
	return compareInteger(leftVal->value, rightVal->value);
}

int rbtIntComparator(void *left, void *right) {
	rbtValue *leftVal = left;
	rbtValue *rightVal = right;
	return compareInteger(leftVal->value, rightVal->value);
}

int rbtRealComparator(void *left, void *right) {
	rbtValue *leftVal = left;
	rbtValue *rightVal = right;
	return compareInteger(leftVal->value, rightVal->value);
}

int rbtStringComparator(void *left, void *right) {
	rbtValue *leftVal = left;
	rbtValue *rightVal = right;
	return compareInteger(leftVal->value, rightVal->value);
}

