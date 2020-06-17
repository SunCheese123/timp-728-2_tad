#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;          
    struct node* left;  
    struct node* right;
    struct node* parent;  
} node;


typedef struct tree {
    struct node* root;  
    int amount;
} tree;


void init(tree* t) {
    t->root = NULL;
    t->amount = 0;
}

int insert(tree* t, int value) {
    node *prev = t->root, *next = NULL;
    node *bar = malloc(sizeof(node));
    bar->value = value;
    if (t->root == NULL) {
        bar->parent = NULL;
        bar->left = NULL;
        bar->right = NULL;
        t->root = bar;
        t->amount = 1;
        return 0;
    }
    while (prev != NULL) {
        next = prev;
        if (value == prev->value) {
            return 1;
        }
        if (value < prev->value) {
            prev = prev->left;
        }
        else {
        prev = prev->right;
        }
    }
    bar->parent = next;
    bar->left = NULL;
    bar->right = NULL;
    if (value < next->value) {
        next->left = bar;
        t->amount++;
        return 0;
    }
    if (value > next->value) {
        next->right = bar;
        t->amount++;
        return 0;
    }
}


node* getRoot(tree* t)
{
    return t->root;
}


void revert (node* t) {

  if (t== NULL)
  return;
revert(t->left);
revert(t->right);
printf("%d ", t->value);
}


int main() {
    int n, a;
    tree t;
    init(&t);
    for (int i=0; i < 7; ++i)
    {
        (void) scanf("%d", &a);
        insert(&t, a);
    }

 revert (getRoot(&t));

  return 0;


};
