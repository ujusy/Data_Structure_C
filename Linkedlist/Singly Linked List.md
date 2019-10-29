# Singly Linked Lists



<img width="665" alt="image-20191020161912272" src="https://user-images.githubusercontent.com/49120090/67621500-1a5c4100-f84b-11e9-9be4-a08c62a57b01.png">





<구조체>

~~~c
typedef struct list_node *list_ptr;
typedef struct list_node{
  char data[4];
  list_ptr link;
};
list_ptr ptr=NULL;
~~~



<노드 생성>

~~~c
ptr=(list_node)malloc(sizeof(list_node));
strcpy(ptr->data,"bat");
ptr->link=NULL;
~~~





<img width="377" alt="image-20191020162426217" src="https://user-images.githubusercontent.com/49120090/67621510-22b47c00-f84b-11e9-8cb7-7953e0056eff.png">



<노드 삽입>

~~~c
void insert(list_ptr *pptr,list_ptr node){
  list_ptr temp;
  temp=(list_ptr)malloc(sizeof(list_node));
  if(IS_FULL(temp)){
    fprintf(stderr,"the memory is full\n");
    exit(1);
  }
  temp->data=50;
  if(*pptr){ //삽입되는 경우
    temp->link=node->link; // 삽입되는 노드의 링크에 원래 다음 노드 가리키게 
    node->link=temp; //삽입되는 전 노드가 삽입되는 노드 가리키게 해준다.
  }
  else{ //처음으로 삽입되는 경우
    temp->link=NULL;
    *pptr=temp;
  }
}
~~~



##### 노드 삭제

<img width="685" alt="image-20191020162854786" src="https://user-images.githubusercontent.com/49120090/67621518-2942f380-f84b-11e9-9092-73da05d0d36c.png">

>2가지 경우가 존재
>
>1.맨 앞의 노드를 삭제할 때
>
>2. 중간에 있는 노드 삭제

~~~c
void delete(list_ptr *pptr,list_ptr trail,list_ptr node){
  if(trail)
    trail->link=node->link;
  else
    *pptr=(*pptr)->link;
  free(node);
}
~~~

 <리스트 프린트하기>

~~~c
void print_list(list_ptr ptr){
  printf("the list contains : ");
  for(;ptr;ptr=ptr->link)
    printf("%4d",ptr->data);
  printf("\n");
}
~~~



