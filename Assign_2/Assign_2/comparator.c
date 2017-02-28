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

int intComparator(void *left, void *right) {
	return compareInteger(left, right);
}

int realComparator(void *left, void *right) {
	return compareReal(left, right);
}

int stringComparator(void *left, void *right) {
	return compareString(left, right);
}
