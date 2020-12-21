#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
  int value; // store node's value
  Node *next; // node's next pointer
} *head, *tail; // global head, tail, and current

Node *createNode(int value) {
  // allocate memory with size of node to temp
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = NULL; // next pointer is NULL by default
  return temp;
}

void pushHead(int value) {
  // create a new node
  Node *temp = createNode(value);

  if(!head) { // if there's no head (0 node)
    head = tail = temp;
  } else { // >= 1 node
    temp->next = head; // node points to head
    head = temp; // node becomes head
  }
}

void pushTail(int value) {
  // create a new node
  Node *temp = createNode(value);

  if(!head) { // if there's no head (0 node)
    head = tail = temp;
  } else { // >= 1 node
    tail->next = temp; // tail points to node
    tail = temp; // node becomes tail
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

// void printLinkedList() {
//   Node *curr = head;
//   while(curr) {
//     printf("%d -> ", curr->value);
//     curr = curr->next;
//   }
//   printf("NULL\n");
// }

int main(){
  pushHead(20);
  pushHead(30);
  printLinkedList();
  // printf("%d\n",head->value);
}

