#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10

typedef struct node *tree_ptr;
typedef struct node{
    char data;
    tree_ptr left,right;
    int visited;
}node;

tree_ptr makeNode(char value,tree_ptr leftnode,tree_ptr rightnode){
    tree_ptr ptr=(tree_ptr)malloc(sizeof(node));
    ptr->data=value;
    ptr->left=leftnode;
    ptr->right=rightnode;
    
    return ptr;
}

int top=-1;
tree_ptr stack[MAX_STACK_SIZE];

int isEmpty(){
    return(top<0);
}

int isFull(){
    return(top>=MAX_STACK_SIZE-1);
}
void push(int *ptop,tree_ptr item){
    if(isFull()){
        printf("Stack is Full");
        return;
    }
    stack[++*ptop]=item;
}
tree_ptr pop(int *ptop){
    return stack[(*ptop)--];
}
void printStack(){
    if(!isEmpty()){
        for(int i=0;i<top+1;i++){
            printf("%c",stack[i]->data);
        }
    }
}
void iter_inorder(tree_ptr node){
    top=-1;
    while(1){
        while(node){
            push(&top,node);
            node=node->left;
        }
        if(!isEmpty()){
            node=pop(&top);
        }
        else break;
        printf("%c",node->data);
        node=node->right;
    }
}
void iter_preorder(tree_ptr node){
    top=-1;
    while(1){
        while(node){
            printf("%c",node->data);
            push(&top,node);
            node=node->left;
        }
        if(!isEmpty())
        {
            node=pop(&top);
        }else break;
        node=node->right;
    }
}
void iter_postorder(tree_ptr node){
    top=-1;
    push(&top,node);
    while(1){
        node=stack[top];
        if(node->left !=NULL && node->left->visited!=1){
            push(&top,node->left);

        }
        else if(node->right !=NULL && node->right->visited !=1){
            push(&top,node->right);
        }
        else{
            printf("%c",node->data);
            node->visited=1;
            pop(&top);
        }
        if(isEmpty()){
            break;
        }
        
    }
}
int main(){
    tree_ptr root,n2,n3,n4,n5,n6,n7,n8,n9;
    n9=makeNode('E',NULL,NULL);
    n8=makeNode('D',NULL,NULL);
    n7=makeNode('C',NULL,NULL);
    n6=makeNode('B',NULL,NULL);
    n5=makeNode('A',NULL,NULL);
    n4=makeNode('/',n5,n6);
    n3=makeNode('*',n4,n7);
    n2=makeNode('*',n3,n8);
    root=makeNode('+',n2,n9);
    
    printf("\ninorder : ");
    iter_inorder(root);
    printf("\npreorder : ");
    iter_preorder(root);
    printf("\npostorder : ");
    iter_postorder(root);

    return 0;
}