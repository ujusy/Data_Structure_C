#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode{
    int coef;
    int expon;
    struct ListNode* link;

}ListNode;

typedef struct ListHeader{
    int length;
    ListNode *head;
    ListNode *tail;

}ListHeader;

void init(ListHeader *plist){
    plist->length=0;
    plist->head=plist->tail=NULL;

}

void poly_print(ListHeader *plist){
    ListNode *p=plist->head;
    for(; p!=NULL; p=p->link){
        printf("%dx^%d",p->coef,p->expon);
        if(p->expon>0) printf(" +");
    }
    printf("\n");
}

void insert_node_last(ListHeader *plist,int coef,int expon){
    ListNode *node=(ListNode *)malloc(sizeof(ListNode));
    node->coef=coef;
    node->expon=expon;
    node->link=NULL;
    
    if(plist->tail==NULL){
        plist->head=node;
        plist->tail=node;
    }
    else{  
     plist->tail->link=node;
     plist->tail=node;
    }
    plist->length ++;
}

void poly_add(ListHeader *plist,ListHeader *plist2,ListHeader *plist3){
    ListNode *p=plist->head;
    ListNode *q=plist2->head;

    int sum=0;
    while(p&&q){
        if(p->expon==q->expon){
            sum=p->expon+q->expon;
            if(sum==0) continue;
            insert_node_last(plist3,sum,p->expon);
            p=p->link;
            q=q->link;
        }
        else if(p->expon>q->expon){
            insert_node_last(plist3,p->coef,p->expon);
            p=p->link;
        }
        else{
            insert_node_last(plist3,q->coef,q->expon);
            q=q->link;
        }
    }

    for(; p!=NULL; p=p->link)
        insert_node_last(plist3,p->coef,p->expon);
    for(; q!=NULL;q=q->link)
        insert_node_last(plist3,q->coef,q->expon);

}
int main(){
    ListHeader list1,list2,list3;
    init(&list1);
    init(&list2);
    init(&list3);

    insert_node_last(&list1,3,12); 
   insert_node_last(&list1,2,8);
   insert_node_last(&list1,1,0);

   insert_node_last(&list2,8,12);
   insert_node_last(&list2,-3,10);
   insert_node_last(&list2,10,6);

   poly_add(&list1,&list2,&list3);
   poly_print(&list3);

   return 0;


}