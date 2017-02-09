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

typedef int (Comparator)(void *, void *);

int intComparator(void *, void *);
int realComparator(void *, void *);
int stringComparator(void *, void *);

#endif /* comparator_h */
