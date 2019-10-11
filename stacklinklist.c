/*
------------Description-------------

linked list를 이용하여 stack 구현하기!!

-------------------------------------
*/

#include <stdio.h>

typedef struct Stack Node; //Stack을 Node 라고 정의 
typedef int element;
struct Stack{ 
    element data;
    struct Stack *link; //자기참조 구조체로 노드를 정의해준다 
};
Node *top=NULL; //top을 널값으로 초기화

void push(element data){ //stack에 data집어 넣기 
    Node *ptr=(Node*)malloc(sizeof(Node)); //노드 동적 할당 

    ptr->data=data; //입력받은 data을 할당되어진 노드 data영역에 넣는다. 
    ptr->link=top; //기존 헤더의 주소를 할당되어진 노드 link에 넣는다. 
    top=ptr; //top이 가리키는 주소가 최근 추가된 노드의 주소 갖는다.  
}
element pop(){ //stack에서 data 빼기
    Node *ptr; 
    element dat;
    ptr=top; //top에 저장된 주소를 ptr로 옮긴다.
    top=ptr->link; //빼려는 노드의 link가 밑의 노드 가리키는주소 갖는다
                    //그 주소를 top에 넣어준다.
    dat=ptr->data;
    free(ptr); //빼진 노드에 할당된 동적 메모리 해제 
    return dat; 
}

int main(void){
    

    push(10);
    push(20);
    push(30);

    pop();
     
     while(top!=NULL){
        printf("%d \n",top->data);
        top=top->link;
        
    }


}
