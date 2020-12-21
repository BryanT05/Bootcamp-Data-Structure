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

void printFromBack(int N){
  Node *curr = head;
  int loc = tail->index - N +1;
  while(curr){
    if(curr->index == loc){
      printf("N-Node From Back Value: %d\n",curr->value);
      printf("N-Node From Back Index: %d\n",loc);
      break;
    }
    curr = curr->next;
  }
  printf("\n");
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
  
  printFromBack(1);
  printFromBack(2);
  printFromBack(3);
  printFromBack(4);
  printFromBack(5);
  printFromBack(6);
  printFromBack(7);
  printFromBack(8);
}

