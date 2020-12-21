#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next;
} *head, *tail;

Node *createNode(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = NULL;
  return temp;
}

void pushHead(int value) {
  Node *temp = createNode(value);

  if(!head) {
    head = tail = temp;
  } else {
    temp->next = head;
    head = temp;
  }
}

void pushTail(int value) {
  Node *temp = createNode(value);

  if(!head) {
    head = tail = temp;
  } else {
    tail->next = temp;
    tail = temp;
  }
}

void printLinkedList(){
  Node *curr = head;
  while(curr){
    printf("%d ->",curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

int main(){
  pushHead(20);
  pushHead(30);
  printLinkedList();
}

