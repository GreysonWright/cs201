//
//  darray.c
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include "darray.h"

void **array; //an array of void pointers
int capacity; //total number of slots
int size; //number of filled slots
void (*display)(FILE *,void *);
