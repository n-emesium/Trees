#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef enum TYPE {
	CHAR,
	STRING,
	INT,
	FLOAT,
	DOUBLE,
} TYPE;

typedef struct tree{
	TYPE type;
	void *val;
	struct tree *left;
	struct tree *right;
} tree;	

typedef void (*print_functions)(tree *);

tree *create(TYPE); //TYPE is a custom enum we have defined to make management easier
void del(tree *); //if you call this on root it will completely free the tree
void add(tree *, void *, char *); //char * is the address we will put it to: for example llrl, 5 would branch to left->left->right->left and set that value to 5
void rmv(tree *, char *); //specify path, how else is the compiler supposed to know what you want to remove?
void set(tree *, void *, char *);
void cprint(tree *);
void strprint(tree *);
void iprint(tree *);
void flprint(tree *);
void dprint(tree *);
void stream(tree *); //generic print functions, calls one of print_table[]
bool equals(tree *, tree *);		     

extern print_functions print_table[];

#endif

