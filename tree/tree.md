

# TREE



## binary tree

![image](https://user-images.githubusercontent.com/49120090/66663378-98361f00-ec85-11e9-8a21-063355d05ad4.png)



>binary tree는 배열로 나타낼 수 있다.
>
>배열로 나타낼 경우는 밑의 사진과 같다.

![image](https://user-images.githubusercontent.com/49120090/66663395-a2f0b400-ec85-11e9-9b0e-8f2a3a8387e4.png)

>배열로 나타낼 경우의 단점이 존재한다.
>
>1.비효율적인 저장 공간 이용 
>
>2.저장과 삭제의 어려움



>그렇다면 어떤 배열이 아닌 어떤 방식을 사용할까?
>
>--> **linked list** 방식을 사용하자!



## binary tree traversal

>크게 4가지 방식으로 소개할 수 있다.
>
>**1.inorder : LVR (Left Visit Right)** 
>
>**2.preorder: VLR(Visit Left Right)**
>
>**3.postorder: LVR(Left Rigt Visit)**
>
>**4.Level order traversal**



>1,2,3은 stack 가 사용되는 반면 4번은 queue 가 사용된다.

 ##### 1.inorder traversal

<img width="438" alt="image-20191007211910586" src="https://user-images.githubusercontent.com/49120090/67156999-c0e2a680-f360-11e9-8fc8-345d8e448d65.png">

~~~c
void inorder(tree_ptr ptr){
  if(ptr){
    inorder(ptr->left_child);
    printf("%d",ptr->data);
    inorder(ptr->right_child);
  }
}
~~~

>__output: A/B * C * D + E__

##### >recursive version

~~~c
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
void inorder(tree_ptr ptr)
{
    if(ptr){
        inorder(ptr->left);
        printf("%c",ptr->data);
        inorder(ptr->right);
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
    inorder(root);
    

    return 0;
}
~~~

<img width="192" alt="image-20191010152244984" src="https://user-images.githubusercontent.com/49120090/67157025-0f904080-f361-11e9-82f9-8d9245a44224.png">

#### preorder traversal

~~~c
void postorder(tree_ptr ptr){
  if(ptr){
    printf("%d",ptr->data);
    preorder(ptr->left_child);
    preorder(ptr->right_child);
  }
}
~~~

>__output: +**/ABCDE__

##### >recursive version

~~~c
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
void preorder(tree_ptr ptr)
{
    if(ptr){
       
       printf("%c",ptr->data);
       preorder(ptr->left);
       preorder(ptr->right);
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
    printf("\npreorder : ");
    preorder(root);
    

    return 0;
}
~~~



#### postorder traversal

~~~c
void postorder(tree_ptr ptr){
  if(ptr){
    postorder(ptr->left_child);
    postorder(ptr->right_child);
    printf("%d",ptr->data);
  }
}
~~~

>__output: AB/C * D * E + -__

##### >recusive version

~~~c
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
    root=makeNode('+',n2,n9); //root는 + root의 left는 n2 right는 n9
    
    printf("\npostorder : ");
    postorder(root);

    return 0;
}
~~~



#### >iterative traversal

> binary tree ->재귀 호출 사용->비효율적 
>
> iterative는 노드에 visited를 둔다.

##### node 구조체

~~~c
typedef struct node *tree_ptr;
typedef struct node{
    char data;
    tree_ptr left,right;
    int visited;
}node;
~~~

##### inorder: 좌->근->우

~~~c
void iter_inorder(tree_ptr node){ //root가 들어와.
    top=-1; 
    while(1){
        while(node){  //node가 null이 아니면 //NULL이면 pop!
            push(&top,node); //처음 노드 삽입.
            node=node->left; //계속 왼쪽으로 내려가
        }
        if(!isEmpty()){  //스택 안비었으면
            node=pop(&top); 
        }
        else break;
        printf("%c",node->data);//처음에 A ->pop하면 /
        node=node->right;//A의 right는 NULL->pop right는 B
    }
}
~~~

##### preorder:근->좌->우

~~~c
void iter_preorder(tree_ptr node){
    top=-1;
    while(1){
        while(node){ 
            printf("%c",node->data); //1.root data출력 2.* 3.* 4./ 5.A /B/C/D/E
            push(&top,node); //1..root노드 삽입.  2.*삽입 3.* 4./ 5.A
            node=node->left; //1.*가리켜 2.* 3./ 4.A 5.NULL
        }
        if(!isEmpty())
        {
            node=pop(&top);  //A //* //* //+
        }else break;
        node=node->right; //A->right=B //*->right=C //D //E
    }
}
~~~

##### postorder: 좌->우->근 

~~~c
void iter_postorder(tree_ptr node){ //root
    top=-1;
    push(&top,node); //root
    while(1){
        node=stack[top]; //stack노드를 가리켜 //* //* // / //A >POP>// / //*  //* //+ 
        if(node->left !=NULL && node->left->visited!=1){ 
            push(&top,node->left);//* //* // / //A 

        }
        else if(node->right !=NULL && node->right->visited !=1){
            push(&top,node->right); //B //C //D //E
        }
        else{
            printf("%c",node->data); //A //B // / //C //* //D //* //E //+
            node->visited=1;
            pop(&top);
        }
        if(isEmpty()){
            break;
        }
        
    }
}
~~~



>전체 코드 및 결과

~~~c
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
~~~

<img width="304" alt="image-20191013172506289" src="https://user-images.githubusercontent.com/49120090/66716097-36042800-ee05-11e9-9ba0-1125e69e633c.png">



#### Level order traversal :	Queue 이용

<img width="352" alt="image-20191013215656477" src="https://user-images.githubusercontent.com/49120090/67157006-d061ef80-f360-11e9-8dde-bed644409f43.png">

##### node 구조체 및 queue선언

~~~c
typedef struct node *tree_ptr;
typedef struct node{
    char data;
    tree_ptr left,right;
    int visited;
}node;
int front,rear=0;
tree_ptr queue[MAX_QUEUE_SIZE];
~~~

-traversal by using queue

~~~c
void level_order(tree_ptr node){ //root
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
~~~

>전체 코드 및 결과

~~~c
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
~~~

<결과>

<img width="206" alt="image-20191013183338657" src="https://user-images.githubusercontent.com/49120090/66716105-4d431580-ee05-11e9-808d-d4e922c91ae8.png">

