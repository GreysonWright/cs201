//
//  string.h
//  Assign_1
//
//  Created by Greyson Wright on 1/27/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

#include <stdio.h>

typedef struct string
{
	char *value;
} string;

string *newString(char *);
char *getString(string *);
char *setString(string *, char *);
void displayString(FILE *, void *);
int compareString(void *, void *);
void freeString(string *);

#endif
