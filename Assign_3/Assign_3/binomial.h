//
//  binomial.h
//  Assign_3
//
//  Created by Greyson Wright on 3/19/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef binomial_h
#define binomial_h

#include <stdio.h>
#include "darray.h"

typedef struct BinomialNode BinomialNode;

BinomialNode *newBinomialNode(void (*)(FILE *, void *), void *);
void displayBinomialNode(FILE *, void *);

typedef struct Binomial Binomial;

Binomial *newBinomial(void (*)(FILE *, void *), int (*)(void *,void *), void (*)(void *, BinomialNode *));
BinomialNode *insertBinomial(Binomial *, void *);
int sizeBinomial(Binomial *);
void deleteBinomial(Binomial *, BinomialNode *);
void decreaseKeyBinomial(Binomial *, BinomialNode *, void *);
void *extractBinomial(Binomial *);
void displayBinomial(FILE *, Binomial *);
#endif /* binomial_h */
