#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>

typedef char element;
typedef struct QNode{
    element data;
    struct  QNode *link;
}QNode;

typedef struct{
    QNode *front,*rear;

}LQueueType;

LQueueType *createLinkedQueue(){
    LQueueType *LQ;
    LQ=(LQueueType *)malloc(sizeof(LQueueType));
    LQ->front=NULL;
    LQ->rear=NULL;
    return LQ;
}

int isEmpty(LQueueType *LQ){
    if(LQ->front==NULL){
        printf("Linked Queue is empty!");
        return 1;
    }
    else return 0;
}

void enQueue(LQueueType *LQ,element item){
    QNode *node=(QNode *)malloc(sizeof(QNode));
    node->data=item;
    node->link=NULL;
    if(LQ->front==NULL){
        LQ->rear=node;
        LQ->front=node;
    }
   else {
    LQ->rear->link=node;

    LQ->rear=node;
   }
}

element deQueue(LQueueType *LQ){
    element item;
    QNode *old=LQ->front;
    
    if(isEmpty(LQ)) return 0;
    else{
        item=old->data;
        LQ->front=LQ->front->link;
        if(LQ->front==NULL){
            LQ->rear=NULL;
        }
        free(old);

        return item;

    }
}

void printLQ(LQueueType *LQ){
    QNode *temp=LQ->front;
    printf("Linked Queue :[ ");

    while(temp){
        printf("%3c",temp->data);
        temp=temp->link;
    }
    printf(" ] ");
}

int main(void){
    LQueueType *LQ=createLinkedQueue();
    element data;

    printf("\n ***** Queue ***** \n");
    printf("\n enqueue C >>");  enQueue(LQ,'C');    printLQ(LQ);
    printf("\n enqueue A >>");  enQueue(LQ,'A');    printLQ(LQ);
    printf("\n enqueue B >>");  enQueue(LQ,'B');    printLQ(LQ);
    printf("\n enqueue D >>");  enQueue(LQ,'D');    printLQ(LQ);
    printf("\n enqueue E >>");  enQueue(LQ,'E');    printLQ(LQ);

    printf("\n dequeue >>");    data=deQueue(LQ);   printLQ(LQ);
    printf("\t dequeued data: %C",data);
    printf("\n dequeue >>");    data=deQueue(LQ);   printLQ(LQ);
    printf("\t dequeued data: %C",data);
    printf("\n dequeue >>");    data=deQueue(LQ);   printLQ(LQ);
    printf("\t dequeued data: %C",data);
    printf("\n dequeue >>");    data=deQueue(LQ);   printLQ(LQ);
    printf("\t dequeued data: %C",data);
    printf("\n dequeue >>");    data=deQueue(LQ);   printLQ(LQ);
    printf("\t dequeued data: %C",data);

    getchar();

    return 0;
}