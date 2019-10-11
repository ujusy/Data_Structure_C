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

![image-20191007211910586](/Users/uju_sy/Library/Application Support/typora-user-images/image-20191007211910586.png)

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

![image-20191010152244984](/Users/uju_sy/Library/Application Support/typora-user-images/image-20191010152244984.png)

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



#### >iterative inorder traversal

> binary tree ->재귀 호출 사용->비효율적 
>
> Threaded binary tree 는 n+1개의 null링크에서 inorder순회시 선행노드,후속노드를 저장하는 tree



~~~c
void iter_inorder(tree_ptr node){
  int top=-1;
  tree_ptr stack[MAX_STACK_SIZE];
  while(1){
    while(node){
      push(&top,node);
      node=node->left_child;
    }
    node=pop(&top);
    if(!node) break;
    printf("%d",node->data);
    node=node->right_child;
  }
}
~~~



#### Level order traversal

-traversal by using queue

~~~c
void level_order(tree_ptr ptr){
  int front= rear = 0;
  tree_ptr queue[MAX_QUEUE_SIZE];
 	if(!ptr) return ;
  while(1){
    ptr=deleteq(&front,rear);
    if(ptr){
      printf("%d",ptr->data);
      if(ptr->left_child)
        addq(front,&rear,ptr->left_child);
     	if(ptr->right_child)
        addq(front,&rear,ptr->right_child);
    }
    else break;
  }
}
~~~

## Threaded Binary Tree

>바이너리 트리에 NULL링크가 많았는데 이러한 부분을 효율적으로 사용하기 위해 사용.
>
>후속노드를 구하기위헤서 우측 포인터를 본다 f면 뒤에 child존재 
>
>왼쪽 보니 true ->앞에 너무 포인터 ->후속노드 우측을 보면 true->NULL링크
>
>중위 순회



후속노드 찾는 프로그램

~~~c
threaded_ptr insucc(threaded_ptr tree) {
threaded_ptr temp;
temp = tree->right_child;
if (!tree->right_thread)
while (!temp->left_thread)
temp = temp->left_child;
return temp;
}

void tinorder(threaded_ptr tree) {
threaded_ptr temp = tree;
for (;;) {
 temp = insucc(temp);
 if (temp = tree) break;
 printf(“%3c”, temp->data);
}
}

~~~

삽입하고자 할때의 코드

~~~c
void insert_right(threaded_ptr parent,threaded_ptr child) {
threaded_ptr temp;
child->right_child=parent->right_child;
child->right_thread=parent->right_thread;
child->left_child=parent;
child->left_thread=TRUE;
parent->right_child=child;
parent->right_thread=FALSE;
if(!child->right_thread) {
temp=insucc(child);
temp->left_child=child;
}
}

~~~

