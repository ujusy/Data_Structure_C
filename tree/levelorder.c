#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

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
int front,rear=0;
tree_ptr queue[MAX_QUEUE_SIZE];

int isEmptyQ(){
    return (front==rear);
}
int isFullQ(){
    return((rear+1)%MAX_QUEUE_SIZE ==front);
}
void addq(int *prear,tree_ptr node){
    if(isFullQ()){
        printf("Queue is full\n");
        return ;
    }
    *prear=(*prear+1)%MAX_QUEUE_SIZE;
    queue[*prear]=node;
    
}
tree_ptr deleteq(int *pfront){
    if(isEmptyQ()){
        printf("Queue is empty\n");
        return 0;
    }
    *pfront=(*pfront +1)%MAX_QUEUE_SIZE;
    return queue[*pfront];
}
void level_order(tree_ptr node){
    addq(&rear,node);
    while(1){
        node=deleteq(&front);
        if(node){
            printf("%c ",node->data);
            if(node->left){
                addq(&rear,node->left);
            }
            if(node->right){
                addq(&rear,node->right);
            }
        }
        if(isEmptyQ())  break;
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
    
    printf("level_order: ");
    level_order(root);

    return 0;
}