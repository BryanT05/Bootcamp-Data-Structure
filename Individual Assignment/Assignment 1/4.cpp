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

void removeDuplicate(){
  Node *curr = head;
  Node *temp;
  Node *temp2;
  while(curr){
    if(curr == tail)break;
    if(curr->value == curr->next->value){
      temp = curr->next;
      while(curr->value == temp->value && temp){
        temp2 = temp;
        temp = temp->next;
        // free(temp2);
      }
      curr->next = temp;
    }
    curr = curr->next;
  }
}

int main(){
  pushTail(5);
  pushTail(10);
  pushTail(10);
  pushTail(10);
  pushTail(15);
  pushTail(15);
  pushTail(15);
  pushTail(15);
  pushTail(20);
  pushTail(20);
  pushTail(25);
  pushTail(30);
  pushTail(35);
  pushTail(40);

  printLinkedList();
  removeDuplicate();
  printLinkedList();
}