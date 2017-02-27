//
//  main.c
//  Assign_2
//
//  Created by Greyson Wright on 1/31/17.
//  Copyright © 2017 Greyson Wright. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "scanner.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "bst.h"
#include "vbst.h"
#include "rbt.h"
#include "comparator.h"

typedef void (Insert)(void *, string *);
typedef void (Delete)(void *, string *);
typedef int (Find)(void *, string *);
typedef void (Statistics)(void *, FILE *);
typedef void (Display)(FILE *, void *);

void rbtStringDisplay(FILE *file, void *string) {
	rbtValue *stringVal = string;
	displayString(file, stringVal->value);
}

void rbtInsert(void *tree, string *value) {
	insertRBT(tree, value);
}

void rbtDelete(void *tree, string *value) {
	deleteRBT(tree, value);
}

int rbtFind(void *tree, string *value) {
	return findRBT(tree, value);
}

void rbtStatistics(void *tree, FILE *file) {
	statisticsRBT(tree, file);
}

void rbtDisplay(FILE *file, void *tree) {
	displayRBT(file, tree);
}

void vbstStringDisplay(FILE *file, void *string) {
	vbstValue *stringVal = string;
	displayString(file, stringVal->value);
}

void vbstInsert(void *tree, string *value) {
	(void)insertVBST(tree, value);
}

void vbstDelete(void *tree, string *value) {
	(void)deleteVBST(tree, value);
}

int vbstFind(void *tree, string *value) {
	return findVBST(tree, value);
}

void vbstStatistics(void *tree, FILE *file) {
	statisticsVBST(tree, file);
}

void vbstDisplay(FILE *file, void *tree) {
	displayVBST(file, tree);
}

string *scanString(FILE *file) {
	char *token = readToken(file);
	if (token == 0) {
		return 0;
	}
	string *newStr = newString(token);
	return newStr;
}

char *readWholeString(FILE *file) {
	char *token = readToken(file);
	long size = strlen(token);
	char *string = malloc(size);
	
	while (token[strlen(token) - 1] != '"') {
		strcat(string, token);
		strcat(string, " ");
		token = readToken(file);
		size += strlen(token) + 1;
		token = realloc(token, size);
	}
	strcat(string, token);
	return string;
}

char *processString(char *string) {
	long strLength = strlen(string);
	char *str = malloc(strLength);
	int count = 0;
	for (int i = 0; i < strLength; i++) {
		if (isalpha(string[i])) {
			str[count++] = tolower(string[i]);
		}
	}
	str = realloc(str, count + 1);
	str[count] = '\0';
	return str;
}

char *getInput(FILE *file) {
	char *token = readToken(file);
	if (token[0] == '"') {
		char *str = readWholeString(file);
		token = realloc(token, strlen(token) + strlen(str));
		strcat(token, str);
	}
	return processString(token);
}

void buildTree(FILE *file, void *tree, Insert *insert) {
	string *token = scanString(file);
	while (!feof(file)) {
		setString(token, processString(token->value));
		insert(tree, token);
		token = scanString(file);
	}
}

void interpretCommands(FILE *input, FILE *output, void *tree, Insert *insert, Delete *delete, Find *find, Statistics *statistics, Display *display) {
	char *token = readToken(input);
	processString(token);
	while (!feof(input)) {
		if (strcmp(token, "i") == 0) {
			token = getInput(input);
			insert(tree, newString(token));
		} else if (strcmp(token, "d") == 0) {
			token = getInput(input);
			delete(tree, newString(token));
		} else if (strcmp(token, "f") == 0) {
			token = getInput(input);
			find(tree, newString(token));
		} else if (strcmp(token, "s") == 0) {
			display(output, tree);
		} else {
			statistics(tree, output);
		}
		token = readToken(input);
	}
}

int main(int argc, const char * argv[]) {
	FILE *input = fopen(argv[2], "r");
	FILE *commands = fopen(argv[3], "r");
	FILE *output = stdout;
	Insert *insert = 0;
	Delete *delete = 0;
	Find *find = 0;
	Statistics *statistics = 0;
	Display *display = 0;
	Comparator *comparator = 0;
	void *tree = 0;
	
	if (argc > 5) {
		output = fopen(argv[4], "w");
	}
	
	switch (argv[1][1]) {
		case 'v':
			insert = vbstInsert;
			delete = vbstDelete;
			find = vbstFind;
			statistics = vbstStatistics;
			display = vbstDisplay;
			comparator = vbstStringComparator;
			tree = newVBST(rbtStringDisplay, comparator);
			break;
		case 'r':
			insert = rbtInsert;
			delete = rbtDelete;
			find = rbtFind;
			statistics = rbtStatistics;
			display = rbtDisplay;
			comparator = rbtStringComparator;
			tree = newRBT(rbtStringDisplay, comparator);
			break;
		default:
			fprintf(stdout, "unknown flag '%c', valid flags are -v and -r\n", argv[1][1]);
			exit(-2);
			break;
	}
	
	buildTree(input, tree, insert);
	fclose(input);
	interpretCommands(commands, output, tree, insert, delete, find, statistics, display);
	fclose(commands);
	return 0;
}
