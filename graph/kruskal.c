#include <stdio.h>

#define MAX_VERTEX 100
#define MAX_ELEMEMT 100

int parent[MAX_VERTEX];
int num[MAX_VERTEX];

typedef struct{
    int v;
    int u;
    int key;
}Element;

typedef struct{
    Element heap[MAX_ELEMEMT];
    int heap_size;
}HeapType;

void  InitHeap(HeapType *h){
    h->heap_size=0;
}
void InsertHeap(HeapType *h,Element item){
    int i;
    i = ++(h->heap_size);

    while((i!=1) && (item.key<h->heap[i/2].key)){
        h->heap[i]=h->heap[i/2];
        i/=2;

    }
    h->heap[i]=item;
}
void InitUF(void){
    int i;
    for(i=0; i<MAX_VERTEX;i++){
        parent[i]=-1;
        num[i]=1;
    }
}

void InsertHeapEdge(HeapType *h,int v,int u,int weight){
    Element node;
    node.v=v;
    node.u=u;
    node.key=weight;

    InsertHeap(h,node);
}
Element DeleteHeap(HeapType  *h){
    int parent=1,child=2;
    Element data,temp;
    
    data=h->heap[parent];
    temp=h->heap[(h->heap_size)--];

    
    
    while(child<= h->heap_size){
        if((child< h->heap_size)&&(h->heap[child].key)>h->heap[child+1].key)
            child++;
        
        if(temp.key<=h->heap[child].key) break;


            h->heap[parent]=h->heap[child];
            parent=child;
            child *=2;
        
    }
    h->heap[parent]=temp;

    return data;

}
int SetFind(int v){
    int i,p,temp=-1;

    for(i=v;(p = parent[i]) >=0;i=p);


    temp=i;
    
    for(i=v;(p=parent[i])>=0;i=p){
        parent[i]=temp;
    }
    return temp;

}
void SetUnion(int v1,int v2){
    if(num[v1]<num[v2]){
        parent[v1]=v2;
        num[v1]+=num[v2];
    }
    else{
        parent[v2]=v1;
        num[v2]+=num[v1];
    }
}
int kruskal(int n){
    Element e;
    HeapType h;
    int uSet,vSet, edgeCount=0,sum=0;

    InitHeap(&h);
    InitUF();

    InsertHeapEdge(&h,1,7,12);
    InsertHeapEdge(&h,1,4,28);
    InsertHeapEdge(&h,1,2,67);
    InsertHeapEdge(&h,1,5,17);
    InsertHeapEdge(&h,2,4,24);
    InsertHeapEdge(&h,2,5,62);
    InsertHeapEdge(&h,3,5,20);
    InsertHeapEdge(&h,3,6,37);
    InsertHeapEdge(&h,4,7,13);
    InsertHeapEdge(&h,5,6,45);
    InsertHeapEdge(&h,5,7,73);

    while(edgeCount < (n-1)){
        e=DeleteHeap(&h);

        uSet=SetFind(e.u);
        vSet=SetFind(e.v);

        if(uSet != vSet){
            printf("(%d, %d) %d \n",e.u,e.v,e.key);
            sum += e.key;
            
            SetUnion(uSet,vSet);
            printf("total weight : %d \n",sum);
        }
        edgeCount++;
    }
    return 0;

}
int main(){
    kruskal(11);
    return 0;
}