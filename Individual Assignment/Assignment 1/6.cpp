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

void reverseLinkedList(){

  if(!head)return;
  int i = 0;
  Node *temp = head;
  while(temp){
    temp = temp->next;
    i++;
  }
  if(i == 1)return;
  Node *index[i+1];
  temp = head;
  int x = 1;
  while(temp){
    index[x++] = temp;
    temp = temp->next;
  }
  head = index[i];
  tail = index[1];
  for(int j = i;j>=2;j--){
    index[j]->next = index[j-1];
  }index[1]->next = NULL;
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
  pushTail(5);
  pushTail(10);
  pushTail(15);
  pushTail(20);
  pushTail(25);
  pushTail(30);
  pushTail(35);
  pushTail(40);

  printLinkedList();
  reverseLinkedList();
  printLinkedList();
}