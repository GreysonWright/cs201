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
#include "string.h"
#include "bst.h"
#include "vbst.h"
#include "rbt.h"

typedef int (Comparator)(void *, void *);
typedef void (Insert)(void *, string *);
typedef void (Delete)(void *, string *);
typedef int (Find)(void *, string *);
typedef void (Statistics)(void *, FILE *);
typedef void (Display)(FILE *, void *);

static void rbtInsert(void *tree, string *value) {
	insertRBT(tree, value);
}

static void rbtDelete(void *tree, string *value) {
	deleteRBT(tree, value);
}

static int rbtFind(void *tree, string *value) {
	return findRBT(tree, value);
}

static void rbtStatistics(void *tree, FILE *file) {
	statisticsRBT(tree, file);
}

static void rbtDisplay(FILE *file, void *tree) {
	displayRBT(file, tree);
}

static void vbstInsert(void *tree, string *value) {
	(void)insertVBST(tree, value);
}

static void vbstDelete(void *tree, string *value) {
	(void)deleteVBST(tree, value);
}

static int vbstFind(void *tree, string *value) {
	return findVBST(tree, value);
}

static void vbstStatistics(void *tree, FILE *file) {
	statisticsVBST(tree, file);
}

static void vbstDisplay(FILE *file, void *tree) {
	displayVBST(file, tree);
}

char *readInput(FILE *file) {
	if (stringPending(file)) {
		return readString(file);
	}
	return readToken(file);
}

void cleanString(char *string) {
	long strLength = strlen(string);
	int count = 0;
	for (int i = 0; i <= strLength; i++) {
		if (isalpha(string[i]) || string[i] == '\0') {
			string[count++] = tolower(string[i]);
		} else if (isspace(string[i])) {
			if (count == 0 || (count != 0 && !isspace(string[count - 1]))) {
				string[count++] = ' ';
			}
		}
	}
}

void buildTree(FILE *file, void *tree, Insert *insert) {
	char *token = readInput(file);
	while (!feof(file)) {
		if (strlen(token) > 0) {
			cleanString(token);
			if (token && strlen(token) > 0) {
				insert(tree, newString(token));
			}
		}
		token = readInput(file);
	}
}

void interpretCommands(FILE *input, FILE *output, void *tree, Insert *insert, Delete *delete, Find *find, Statistics *statistics, Display *display) {
	char *token = readToken(input);
	while (!feof(input)) {
		cleanString(token);
		if (strcmp(token, "i") == 0) {
			token = readInput(input);
			cleanString(token);
			if (token && strlen(token) > 0) {
				insert(tree, newString(token));
			}
		} else if (strcmp(token, "d") == 0) {
			token = readInput(input);
			cleanString(token);
			if (token && strlen(token) > 0) {
				delete(tree, newString(token));
			}
		} else if (strcmp(token, "f") == 0) {
			token = readInput(input);
			cleanString(token);
			if (token && strlen(token) > 0) {
				int frequency = find(tree, newString(token));
				fprintf(output, "Frequency of \"%s\": %d\n", token, frequency);
			}
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
	
	if (argc > 4) {
		output = fopen(argv[4], "w");
	}
	
	switch (argv[1][1]) {
		case 'v':
			insert = vbstInsert;
			delete = vbstDelete;
			find = vbstFind;
			statistics = vbstStatistics;
			display = vbstDisplay;
			comparator = compareString;
			tree = newVBST(displayString, comparator);
			break;
		case 'r':
			insert = rbtInsert;
			delete = rbtDelete;
			find = rbtFind;
			statistics = rbtStatistics;
			display = rbtDisplay;
			comparator = compareString;
			tree = newRBT(displayString, comparator);
			break;
		default:
			fprintf(stderr, "unknown flag '%c', valid flags are -v and -r\n", argv[1][1]);
			exit(-2);
			break;
	}

//	char *token = readInput(stdin);
//	while (!feof(stdin)) {
//		cleanString(token);
//		printf("'%s'\n", token);
//		token = readInput(stdin);
//	}
	
	buildTree(input, tree, insert);
	fclose(input);
	interpretCommands(commands, output, tree, insert, delete, find, statistics, display);
	fclose(commands);
	return 0;
}
