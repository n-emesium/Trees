#include "tree.h"

print_functions print_table[] = {cprint, strprint, iprint, flprint, dprint};

tree *create(TYPE ty) {
	tree *t = malloc(sizeof(tree));
	t->left = NULL;
	t->right = NULL;
	t->val = NULL;
	t->type = ty;
	return t;
}

void del(tree *t) { //use recursion
	if (t == NULL) {
		return;
	}
	del(t->left);
	del(t->right);
	free(t);
}

void add(tree *t, void *elem, char *route) { //make it so that if the node does not exist, create a new one
	/*if ((t->left == NULL || t->right == NULL) && *route != '\0') { //handle the node not existing case here
		tree *new = create(t->type);
		new->val = elem;
		if (*route == 'l') {
			t->left = new;
		} else {
			t->right = new;
		}
		return;
	} else if (*route == '\0') {
		t->val = elem;
		return;
	} else if (*route == 'l') {
		add(t->left, elem, route + 1);
	} else  {
		add(t->right, elem, route + 1);
	}*/
	if (*route == '\0') { // End of route: set value
        t->val = elem;
        return;
    	}
    // Traverse left or right, creating nodes if missing
    if (*route == 'l') {
        if (!t->left) {
            t->left = create(t->type);
        }
        add(t->left, elem, route + 1);
    } else if (*route == 'r') {
        if (!t->right) {
            t->right = create(t->type);
        }
        add(t->right, elem, route + 1);
    }
}

void rmv(tree *t, char *c) { //c stands for route
	if (t == NULL) {
		return;
	}
	if (*(c + 1) == '\0') { //recurse back
		if (*c == 'l') { //delete left node
			t->left = NULL;
		} else { //delete right node
			t->right = NULL;
		}
		return; //explicitly return
	} else if (*c == 'l') { //go left
		rmv(t->left, c + 1); //increment pointer by 1 to point to the next character
	} else { //go right
		rmv(t->right, c + 1);
	}
}

void set(tree *t, void *elem, char *route) {
	//just call remove and add consequitvely
	rmv(t, route);
	add(t, elem, route);
}


void cprint(tree *t) {
	printf("%c ",*(char *)t->val);
}
void strprint(tree *t) {
	printf("%s ", (char *)t->val);
}
void iprint(tree *t) {
	printf("%d ", *(int *)t->val);
}
void flprint(tree *t) {
	printf("%.2f ", *(float *)t->val);
}
void dprint(tree *t) {
	printf("%lf ", *(double *)t->val);
}

void stream(tree *t) {
	/*if (t == NULL) {
		return;
	}
	if (t->val == NULL) {
		return;
	}
	print_table[t->type](t);
	printf("\n");
	stream(t->left);
	printf("\n");
	stream(t->right);
	printf("\n");*/
	 if (t == NULL) return;
    if (t->val != NULL) {
        print_table[t->type](t);
        printf("\n");
    }

    stream(t->left);
    stream(t->right);
}

bool equals(tree *t, tree *n) {
	if (t == NULL && n == NULL) {
		return true;
	}
	if (t == NULL || n == NULL) {
		return false;
	}
	 if (t->val == NULL || n->val == NULL) {
        	return (t->val == n->val) && equals(t->left, n->left) && equals(t->right, n->right); 
    	}
	switch (t->type) {
		case CHAR:
			return ( *(char *)(t->val) == *(char *)(n->val) && equals(t->left, n->left) && equals(t->right, n->right));
		case STRING:
			return (strcmp((char *)(t->val), (char *)(n->val)) == 0 && equals(t->left, n->left) && equals(t->right, n->right));

		case INT:
			return ( *(int *)(t->val) == *(int *)(n->val) && equals(t->left, n->left) && equals(t->right, n->right));
		case FLOAT:
			return ( *(float *)(t->val) == *(float *)(n->val) && equals(t->left, n->left) && equals(t->right, n->right));
		case DOUBLE:
			return ( *(double *)(t->val) == *(double *)(n->val) && equals(t->left, n->left) && equals(t->right, n->right));
		default: //this should never happen as the above snippets always give false in case of failure but for safety i guess
			return false; //exit code -1
	}
}
