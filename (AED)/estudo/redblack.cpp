/* red-black tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

/* typedef int T; */                 /* type of item to be stored */
#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

/* Red-Black tree description */
typedef enum { BLACK, RED } nodeColor;

typedef struct Node_ {
    struct Node_ *left;         /* left child */
    struct Node_ *right;        /* right child */
    struct Node_ *parent;       /* parent */
    nodeColor color;            /* node color (BLACK, RED) */
    int data;                     /* data stored in node */
} Node;

#define NIL &sentinel           /* all leafs are sentinels */
Node sentinel = { NIL, NIL, 0, BLACK, 0};

Node *root = NIL;               /* root of Red-Black tree */

void rotateLeft(Node *x) {

   /**************************
    *  rotate node x to left *
    **************************/

    Node *y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        root = y;
    }

    /* link x and y */
    y->left = x;
    if (x != NIL) x->parent = y;
}

void rotateRight(Node *x) {

   /****************************
    *  rotate node x to right  *
    ****************************/

    Node *y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        root = y;
    }

    /* link x and y */
    y->right = x;
    if (x != NIL) x->parent = y;
}

void insertFixup(Node *x) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after inserting node x           *
    *************************************/

    /* check Red-Black properties */
    while (x != root && x->parent->color == RED) {
        /* we have a violation */
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                /* uncle is BLACK */
                if (x == x->parent->right) {
                    /* make x a left child */
                    x = x->parent;
                    rotateLeft(x);
                }

                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent);
            }
        } else {

            /* mirror image of above code */
            Node *y = x->parent->parent->left;
            if (y->color == RED) {

                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {

                /* uncle is BLACK */
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

Node *insertNode(int data) {
    Node *current, *parent, *x;

   /***********************************************
    *  allocate node for data and insert in tree  *
    ***********************************************/

    /* find where node belongs */
    current = root;
    parent = 0;
    while (current != NIL) {
        if (compEQ(data, current->data)) return (current);
        parent = current;
        current = compLT(data, current->data) ?
            current->left : current->right;
    }

    /* setup new node */
    if ((x = (Node*) malloc (sizeof(*x))) == 0) {
        printf ("insufficient memory (insertNode)\n");
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    /* insert node in tree */
    if(parent) {
        if(compLT(data, parent->data))
            parent->left = x;
        else
            parent->right = x;
    } else {
        root = x;
    }

    insertFixup(x);
    return(x);
}

void deleteFixup(Node *x) {

   /*************************************
    *  maintain Red-Black tree balance  *
    *  after deleting node x            *
    *************************************/

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft (x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight (w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft (x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight (x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft (w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight (x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}








void deleteNode(Node *z) {
    Node *x, *y;
    if (!z || z == NIL) return;

    if (z->left == NIL || z->right == NIL) {
        /* y has a NIL node as a child */
        y = z;
    } else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y->left != NIL) y = y->left;
    }

    /* x is y's only child */
    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root = x;

    if (y != z) z->data = y->data;


    if (y->color == BLACK)
        deleteFixup (x);

    free (y);
}






Node *findNode(int data) {
    Node *current = root;
    while(current != NIL)
        if(compEQ(data, current->data))
            return (current);
        else
            current = compLT (data, current->data) ?
                current->left : current->right;
    return(0);
}





void show_rb_tree(Node *x, int i)
	/* Turn the rb-tree T to 90' in counter-clockwise
	   and show it*/
{
	int j;

	if (x != NIL)
	{
		show_rb_tree(x->right, i + 1);

		for(j = 0 ; j < i ; j++)
			printf("     ");
		if (x->color == BLACK)
			printf("%4db\n", x->data);
		else
			printf("%4dR\n", x->data);

		show_rb_tree(x->left, i + 1);
	}
	else
	{
		for(j = 0 ; j < i ; j++)
			printf("     ");
		if (x->color == BLACK)
			printf("    b\n");
		else
			printf("    R\n");
	}
}

void load_file(char* filename)
{       
    int del_ins = 0; // -1:delete, 1:insert
    int sign = 1; // -1:neg, 1:pos
    int is_first = 1; // 1:true, 0:false
    int temp, i, h;
	/* char filename[20]; */
	Node* t;
            
    FILE* fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Cannot open file\n");
        exit(0);
    }
    //cbuf = new char[10];
    h = 0;  
    while (1) {
        if (del_ins != 0) {
            sign = 1;
            temp = 0;
            while (1) {
                i = fgetc(fp);
                if (i == 45) {
                    sign = -1;
                } else if (i > 47 && i < 58) {
                    i -= 48;
                    temp = temp * 10 + i;
                } else {
                    if (sign == -1) temp *= -1;
                    //printf("temp=%d\n", temp);
                    if (del_ins == 1) {
						if ((t = findNode(temp)) == NULL) 
							insertNode(temp);
					} else if (del_ins == -1) {
						//printf("exec rb_delete\n");
						if ((t = findNode(temp)) != NULL) {
							deleteNode(t);
						}
					}
					break;
				}
			}
		}
		i = fgetc(fp);
		if (i == -1) {
			break;
		} else if (i == 68) {
			del_ins = -1;
		} else if (i == 73) {
			del_ins = 1;
		}
		//System.out.print(i + " ");
	}

}

int main(int argc, char **argv){
	
	clock_t start, finish;
	double duration;
	char filename[20];
	int temp;
	Node* t;

	while (1) {
		int instruction = 0;
		printf("1: load from file\n");
		printf("2: insert from stdin\n");
		printf("3: delete from stdin\n");
		printf("4: exit\n");
		scanf("%d", &instruction);
		
		if (instruction == 4) {
			break;
		} else if (instruction == 1) {
			printf("insert the filename: ");
			scanf("%s", filename);
			printf("\n");
			start = clock();
			load_file(filename);
			show_rb_tree(root, 2);
			finish = clock();
			duration = (double)(finish - start);
			printf("%f clock ticks\n", duration);
		
		    
		} else if (instruction == 2) {
			printf("node to insert:\n");
			scanf("%d", &temp);
			start = clock();
			if ((t = findNode(temp)) == NULL) 
				insertNode(temp);
			show_rb_tree(root, 2);
			finish = clock();
			duration = (double)(finish - start);
			printf("%f clock ticks\n", duration);
		} else if (instruction == 3) {
			printf("node to delete:\n");
			scanf("%d", &temp);
			start = clock();
			if ((t = findNode(temp)) != NULL) {
				deleteNode(t);
			}
			show_rb_tree(root, 2);
			finish = clock();
			duration = (double)(finish - start);
			printf("%f clock ticks\n", duration);


		} else {
			continue;
		}
	}
}
