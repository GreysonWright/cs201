//
//  comparator.h
//  Assign_1
//
//  Created by Greyson Wright on 2/7/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef comparator_h
#define comparator_h

#include <stdio.h>

typedef void (Printer)(FILE *, void *);
typedef int (Comparator)(void *, void *);

int vbstIntComparator(void *, void *);
int vbstRealComparator(void *, void *);
int vbstStringComparator(void *, void *);
int rbtIntComparator(void *, void *);
int rbtRealComparator(void *, void *);
int rbtStringComparator(void *, void *);
#endif /* comparator_h */
