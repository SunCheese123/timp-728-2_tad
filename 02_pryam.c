#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

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


typedef struct stack{
        int top;
        node *objs[STACK_SIZE];
}stack;

void push(stack *ms, node *obj){
   if(ms->top < STACK_SIZE-1){
       ms->objs[++(ms->top)] = obj;
   }
   else {
       printf("Stack is full\n");
   }
}

node * pop (stack *ms){
   if(ms->top > -1 ){
       return ms->objs[(ms->top)--];
   }
   else{
       printf("Stack is empty\n");
   }
}
node * peek(stack ms){
  if(ms.top < 0){
      printf("Stack empty\n");
      return 0;
   }
   return ms.objs[ms.top];
}
int isEmpty(stack ms){
   if(ms.top < 0) return 1;
   else return 0;
}


void straight (node* t) {
  stack ms;
    ms.top = -1;

    if(t == NULL) return ;

    node *bar = NULL;
    push(&ms,t);

    while(!isEmpty(ms)){
        bar = pop(&ms);
        printf("%d ", bar->value);
        if(bar->right){
            push(&ms, bar->right);
        }
        if(bar->left){
            push(&ms, bar->left);
        }
    }
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

straight (getRoot(&t));
printf("\n");


  return 0;


};
