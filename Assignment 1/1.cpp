#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
  int value;
  Node *next;
} *head[3], *tail[3];

Node *createNode(int value){
  Node *newnode = (Node*)malloc(sizeof(Node));
  newnode->value = value;
  newnode->next = NULL;
  return newnode;
}

void pushHead(int value, int index){
  Node *temp = createNode(value);
  if(!head[index]){
    head[index] = tail[index] = temp;
  }
  else{
    temp->next = head[index];
    head[index] = temp;
  }
}

void pushTail(int value, int index){
  Node *temp = createNode(value);
  if(!head[index]){
    head[index] = tail[index] = temp;
  }
  else{
    tail[index]->next = temp;
    tail[index] = temp;
  }
}

void printLinkedList(int index){
  Node *curr = head[index];
  while(curr){
    printf("%d ->",curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

void mergeLinkedList(){
  Node *curr1 = head[0];
  Node *curr2 = head[1];
  Node *temp;

  while(curr1 && curr2){
    if(curr1->value <= curr2->value){
      pushTail(curr1->value,2);
      temp = curr1;
      curr1 = curr1->next;
      free(temp);
    }else {
      pushTail(curr2->value,2);
      temp = curr2;
      curr2 = curr2->next;
      free(temp);
    }
  }
    while(curr1){
      pushTail(curr1->value,2);
      temp = curr1;
      curr1 = curr1->next;
      free(temp);
    }
    while(curr2){
      pushTail(curr2->value,2);
      temp = curr2;
      curr2 = curr2->next;
      free(temp);
    }
  }

int main(){
  pushTail(3,0);
  pushTail(5,0);
  pushTail(8,0);
  pushTail(9,0);

  pushTail(1,1);
  pushTail(2,1);
  pushTail(4,1);
  pushTail(6,1);

  mergeLinkedList();

  printLinkedList(2);
}