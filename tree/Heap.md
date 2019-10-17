# HEAP

>heap은 우선 순위에 자구 액세스하거나 우선 순위 중심으로 정렬된 시퀀스를 활용해야 할 때 유용한 자료구조
>
>heap의 속성
>
>>1.heap order property: 각 노드의 값은 자신의 자식노드가 가진 값보다 크거나 같다(max heap)
>>
>>​								각 노드의 값은 자신의 자식노드가 가진 값보다 작거나 같다(min heap).
>>
>>2.heap shape property: 모양은 ___완전 이진트리___이다. 즉 마지막 레벨의 모든 노드는 왼쪽에 쏠려있다.

<img width="733" alt="image-20191017145200564" src="https://user-images.githubusercontent.com/49120090/67003091-36a80180-f118-11e9-9f41-9e75374d8a74.png">

##### heap과 bst(Binary Search Tree)차이

>haep은 각 노드이값이 자식노드보다 큰 반면, BST 는 왼쪽 자식노드가 제일 작고 부모노드가 그 다음 크며 오른쪽 자식노드가 가장 큰 값을 가진다.
>
>->___heap은 우선순위 정렬에 bst는 탐색에 강점을 지닌 자료구조___



>Max tree : max heap->우선순위 큐
>
>min tree. : min heap
>
>-->arr 와 linkedlist표현 사용 가능한데 대체로 arr사용한다.
>
>완전 이진트리이기 때문에 arr사용했을 때 큰 낭비 없다.
>
>Heap 다루기 위해서 부모 노드를  알아야한다,
>
>level order-> 인덱스를 통해 좌노드와 우노드 확인

>
>
>max tree, min tree 기억하는것이 중요
>
>전제조건: 완전 이진트리 유지
>
>노드 삽입 및 삭제 원리
>
>그에 따른 시간복잡도는 삽입 삭제 모두 같아.
>
>여기서 시험문제나와.
>
>삽입해라 삭제해라
>
>임의의 heap값을 주고 3 5 7 9 를 주고 초기 힙 구성해보아라.
>
>min heap이면 3 5 7 9 

##### max heap

>좌노드가 우노드보다 크다.

<img width="298" alt="image-20191010165009804" src="https://user-images.githubusercontent.com/49120090/67003115-458eb400-f118-11e9-902a-9c4f31f9f838.png">\





###### min heap

 <img width="313" alt="image-20191010165032542" src="https://user-images.githubusercontent.com/49120090/67003128-4de6ef00-f118-11e9-87c1-e2ef72f31270.png">

>a^k-1=n //k가 depth



<img width="400" alt="image-20191010165325621" src="https://user-images.githubusercontent.com/49120090/67003172-60612880-f118-11e9-8056-9baa73b27741.png">



<img width="400" alt="image-20191010165621163" src="https://user-images.githubusercontent.com/49120090/67003186-6820cd00-f118-11e9-9b80-7ab3627e954c.png">

>heap: 구조체 및 생성 코드

~~~c
#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 100

typedef struct{
    int heap[MAX_ELEMENT]; //heap은 보통 배열로 표현
    int heap_size;
}heapType;

heapType * createHeap(){ //heap생성 코드
    heapType *h=(heapType *)malloc(sizeof(heapType));
    h->heap_size=0;
    return h;
}
~~~

>구현
>
>1.힙은 배열로 저장
>
>2.구현을 쉽게하기위해 첫 번째 인덱스인 0사용 안한다.
>
>3.heap에서 부모노드와 자식노드의 관계는
>
>-->왼쪽 자식의 인덱스=(부모의 인덱스)*2
>
>-->오른쪽 자식의 인덱스=(부모 인덱스 )*2+1

#### delete

> root와 가장 마지막 인덱스값 자리를 교환해준다,
>
> 그 다음부터 값 비교해주면서 switch해준다.
>
> delete는 root빼서 제일 하단에 있는 값 대입해준다.-->완전 이진트리 구성해주기 위해서
>
> 꺼내서 집어넣고 levelup비교하기때문에 depth만큼 비교한다.
>
> 따라서 시간 복잡도는 O(log2n)이다

```c
int deleteHeap(heapType *h){
    int parent,child;
    int item,temp;
    //max heap에서의 delete는 항상 root부터 시작
    item=h->heap[1];
    //heap 배열의 마지막 요소를 temp에 할당 후 힙 크기 1감소시킴
    temp=h->heap[h->heap_size];
    h->heap_size=h->heap_size-1;

    parent=1;
    child=2;

    while(child<= h->heap_size){
        if((child< h->heap_size)&&(h->heap[child])<h->heap[child+1])
            child++;
        
        if(temp>=h->heap[child]) break;

        else{
            h->heap[parent]=h->heap[child];

            parent=child;
            child=child*2;
        }
    }
    h->heap[parent]=temp;

    return item;
}
```



>전체 코드 및 결과

~~~c
#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 100

typedef struct{
    int heap[MAX_ELEMENT]; //heap은 보통 배열로 표현
    int heap_size;
}heapType;

heapType * createHeap(){ //heap생성 코드
    heapType *h=(heapType *)malloc(sizeof(heapType));
    h->heap_size=0;
    return h;
}

void printHeap(heapType *h){
    int i;
    printf("HEAP: ");
    for(i=1;i<=h->heap_size;i++){
        printf("[%d]",h->heap[i]);
    }
}
void insertHeap(heapType *h,int item){
    int i;
    h->heap_size=h->heap_size+1;
    i=h->heap_size;
//배열의 마지막 요소부터 부모 노드의 index와 비교
    while((i!=1)&&(item > h->heap[i/2])){
        h->heap[i]=h->heap[i/2];
        i/=2;
    }
    h->heap[i]=item;
}
int deleteHeap(heapType *h){
    int parent,child;
    int item,temp;
    //max heap에서의 delete는 항상 root부터 시작
    item=h->heap[1];
    //heap 배열의 마지막 요소를 temp에 할당 후 힙 크기 1감소시킴
    temp=h->heap[h->heap_size];
    h->heap_size=h->heap_size-1;

    parent=1;
    child=2;

    while(child<= h->heap_size){
        if((child< h->heap_size)&&(h->heap[child])<h->heap[child+1])
            child++;
        
        if(temp>=h->heap[child]) break;

        else{
            h->heap[parent]=h->heap[child];

            parent=child;
            child=child*2;
        }
    }
    h->heap[parent]=temp;

    return item;
}
int main(){
    int i,n,item;
    heapType *heap=createHeap();
    insertHeap(heap,10);
    insertHeap(heap,45);
    insertHeap(heap,19);
    insertHeap(heap,11);
    insertHeap(heap,96);
    
    printHeap(heap);

    n=heap->heap_size;

    for (i = 1; i <= n; i++) {
    item = deleteHeap(heap);
    printf("\n delete : [%d] --> ", item);
    printHeap(heap);
    }

    getchar();

    return 0;
}
~~~

<img width="429" alt="image-20191017145531723" src="https://user-images.githubusercontent.com/49120090/67003217-75d65280-f118-11e9-85af-5a6999883aae.png">

