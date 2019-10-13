##  Threaded Binary Tree

> 바이너리 트리에 NULL링크가 많았는데 이러한 부분을 효율적으로 사용하기 위해 사용.
>
> 후속노드를 구하기위헤서 우측 포인터를 본다 f면 뒤에 child존재 
>
> 왼쪽 보니 true ->앞에 너무 포인터 ->후속노드 우측을 보면 true->NULL링크
>
> 중위 순회



>총 노드이 개수=n개
>
>총 링크의 개수=2n개
>
>NULL이 아닌 링트=n-1개
>
>NULL링크=n+1개



<img width="345" alt="image-20191013223719821" src="https://user-images.githubusercontent.com/49120090/66718073-9ea9cf80-ee1a-11e9-9e8f-cf40e158c0b0.png">



##### threaded node 구조체

~~~c
typedef struct threaded_tree *threaded_ptr;
typedef struct threaded_tree{
  short int left_thread;
  threaded_ptr left_child;
  char data;
  threaded_ptr right_child;
  short int right_thread;
}
~~~

<img width="276" alt="image-20191013223626444" src="https://user-images.githubusercontent.com/49120090/66718080-a9fcfb00-ee1a-11e9-8079-08794f71d8b0.png">



#####후속노드 찾는 코드

```c
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

```

삽입하고자 할때의 코드

```c
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

```

>전체 코드 구현 및 결과



~~~c

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treeNode{
    char data;
    struct treeNode *left;
    struct treeNode *right;
    int isThreadRight; //inorder 은 왼쪽 서브트리를 먼저 방문, 오른쪽 서브트리는 가장 나중에 방문하기 때문에 right만 고려
}treeNode; //0인면right는 inordersuccessor 1이면 오른쪽 자식노드

treeNode *makeNode(char data,treeNode *leftNode,treeNode *rightNode,int isThreadRight){

    treeNode *node=(treeNode *)malloc(sizeof(treeNode));
    node->data=data;
    node->left=leftNode;
    node->right=rightNode;
    node->isThreadRight=isThreadRight;

    return node;

}


treeNode *findThreadSuccessor(treeNode *p){
    treeNode *q=p->right;
    if(q==NULL) return q;
    if(p->isThreadRight==1) return q;
    while(q->left !=NULL) q=q->left;
    return q;
}
void threadInorder(treeNode *root){
    treeNode *q;
    q=root;
    while(q->left) q=q->left;
    do{
        printf("%3c",q->data);
        q=findThreadSuccessor(q);
    }while(q);
}
treeNode *findThreadPredecessor(treeNode *p){
    treeNode *q=p->left;
    if(q==NULL) return q;
    if(q->isThreadRight==1)return q;
    while(q->right !=NULL) q=q->right;

    return q;
}
void *insertLeft(treeNode *p,treeNode *r){
    treeNode *temp;
    r->left=p->left;
    r->right=p;
    r->isThreadRight=1;
    if(r->left !=NULL){
        temp=findThreadPredecessor(r);
        temp->right=r;
        temp->isThreadRight=1;

    }
    return NULL;

}
void *insertRight(treeNode *p,treeNode *r){

    treeNode *temp;
    r->right=p->right;
    r->isThreadRight=0;
    p->right=r;

    return NULL;

}
int main() {
	treeNode* n7 = makeNode('G', NULL, NULL, 0);
	treeNode* n6 = makeNode('F', NULL, NULL, 1);
	treeNode* n5 = makeNode('E', NULL, NULL, 1);
	treeNode* n4 = makeNode('D', NULL, NULL, 1);
	treeNode* n3 = makeNode('C', n6, n7, 0);
	treeNode* n2 = makeNode('B', n4, n5, 0);
	treeNode* n1 = makeNode('A', n2, n3, 0);

	n4->right = n2;
	n5->right = n1;
	n6->right = n3;

	printf("\n Inorder of a threaded binary tree: ");
	threadInorder(n1);

	treeNode* r1 = makeNode('H', NULL, NULL, 1);

	insertLeft(n2, r1);

	treeNode* r2 = makeNode('I', NULL, NULL, 1);

	insertRight(n3, r2);

	printf("\n Inorder of a threaded binary tree: ");
	threadInorder(n1);

	getchar();

    return 0;

}
~~~

<결과>

<img width="480" alt="image-20191014001612078" src="https://user-images.githubusercontent.com/49120090/66718085-b719ea00-ee1a-11e9-826c-41d813e21fe5.png">



