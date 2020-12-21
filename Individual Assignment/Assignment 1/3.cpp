#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next;
  int index;
} *head, *tail;

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = NULL;
  return temp;
}

void pushTail(int value) {
  Node *temp = createNode(value);

  if(!head) {
    temp->index = 1;
    head = tail = temp;
  } else {
    tail->next = temp;
    temp->index = tail->index + 1;
    tail = temp;
  }
}

void printLinkedList(){
  Node *curr = head;
  while(curr){
    printf("%d ->",curr->index);
    curr = curr->next;
  }
  printf("NULL\n");
}

void printMid(){
  Node *curr = head;
  int mid = tail->index /2;
  while(curr){
    if(curr->index == mid){
      printf("Mid Value: %d\n",curr->value);
      printf("Mid Index: %d\n",mid);
      break;
    }
    curr = curr->next;
  }
}

int main(){
  pushTail(5);
  pushTail(10);
  pushTail(15);
  pushTail(20);
  pushTail(25);
  pushTail(30);
  pushTail(35);
  pushTail(40);

  printMid();
}