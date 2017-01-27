//
//  string.c
//  Assign_1
//
//  Created by Greyson Wright on 1/27/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"

string *newString(char *str) {
	if (str == 0) {
		return 0;
	}
	string *newStr = malloc(sizeof *newString);
	if (newStr == 0) {
		fprintf(stderr, "out of memory");
		exit(1);
	}
	newStr->value = malloc(strlen(str));
	strcpy(newStr->value, str);
	return newStr;
}

char *getString(string *str) {
	return str->value;
}

char *setString(string *stringItem, char *str) {
	char *oldStr = malloc(strlen(stringItem->value));
	strcpy(oldStr, stringItem->value);
	
	stringItem->value = malloc(strlen(str));
	stringItem->value = str;
	return oldStr;
}

void displayString(FILE *file, void *str) {
	fprintf(file, "\"%s\"", getString(str));
}

int compareString(void *left, void *right) {
	return strcmp(getString(left), getString(right));
}

void freeString(string *str) {
	free(str);
}
