#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
  int val;
  Node *next;
} *head[2], *tail[2];

Node *createNode(int val){
  Node *newnode = (Node*)malloc(sizeof(Node));
  newnode->val = val;
  newnode->next = NULL;
  return newnode;
}

void pushHead(int val, int index){
  Node *temp = createNode(val);
  if(!head[index]){
    head[index] = tail[index] = temp;
  }
  else{
    temp->next = head[index];
    head[index] = temp;
  }
}

void printLinkedList(int index){
  Node *curr = head[index];
  while(curr){
    printf("%d ->",curr->val);
    curr = curr->next;
  }
  printf("NULL\n");
}

int main(){
  pushHead(20,1);
  pushHead(30,0);
  printLinkedList(1);

  // printf("halo\n");
}