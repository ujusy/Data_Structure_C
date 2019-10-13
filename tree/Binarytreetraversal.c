#include<stdio.h>
#include <stdlib.h>
typedef struct node *tree_ptr;
typedef struct node{
    char data;
   tree_ptr  left,right;
    
}node;

tree_ptr makeNode(char data,tree_ptr leftnode,tree_ptr rightnode){
    tree_ptr ptr=(tree_ptr)malloc(sizeof(node));
    ptr->data=data;
    ptr->left=leftnode;
    ptr->right=rightnode;

    return ptr;

}
void postorder(tree_ptr ptr)
{
    if(ptr){
       postorder(ptr->left);
       postorder(ptr->right);
       printf("%c",ptr->data);
       
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
    
    printf("\npostorder : ");
    postorder(root);

    return 0;
}