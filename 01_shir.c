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

typedef struct struct_obj {
    void* bruh;
    struct struct_obj* next;
} obj;

typedef struct struct_queue {
    obj* begin;
    obj* end;
}queue;

queue* create_queue() {
    queue* res = malloc(sizeof(queue));
    res->begin = NULL;
    res->end = NULL;
    return res;
}

void queue_push(queue* q, void* bruh) {
    obj* i = malloc(sizeof(obj));
    i->next = NULL;
    i->bruh = bruh;

    if (q->end == NULL) {
        q->begin = i;
        q->end = i;
    }
    else {
        q->end->next = i;
        q->end = i;
    }
}

void* queue_pop(queue* q) {
    if (q->begin == NULL) return NULL;
    obj* current = q->begin;
    q->begin = q->begin->next;
    if (q->begin == NULL) q->end = NULL;
    void* bruh = current->bruh;
    free(current);
    return bruh;
}

void firstWidth (node* root) {
  queue* q_current = NULL;
  queue* q_next = create_queue();
  queue_push(q_next, (void*)root);
  int isNotLast;
  do {
      free(q_current);
      q_current = q_next;
      q_next = create_queue();
      void* bruh;
      isNotLast = 0;
      while (q_current->begin != NULL) {
          bruh = queue_pop(q_current);
          if (bruh != NULL) {
              node* n = (node*)bruh;
              printf("%d ", n->value);
              queue_push(q_next, n->left);
              queue_push(q_next, n->right);
              isNotLast = isNotLast || n->left || n->right;
          }
          else {
              queue_push(q_next, NULL);
              queue_push(q_next, NULL);
          }
      }
  } while (isNotLast);
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

 firstWidth (getRoot(&t));
 printf("\n");

return 0;

};
