#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
  int value;
  int flag;
  Node *next;
} *head[3], *tail[3];

Node *createNode(int value){
  Node *newnode = (Node*)malloc(sizeof(Node));
  newnode->value = value;
  newnode->flag = 0;
  newnode->next = NULL;
  return newnode;
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

void checkCycle(int index){
  Node *temp = head[index];
  int flagg = 0;
  while(temp){
    if(temp->flag == 1){
      flagg = 1;
      break;
    }
    temp->flag = 1;
    temp = temp->next;
  }
  if(flagg == 0)printf("Non Circular (does not have cycle)\n");
  else printf("Circular (does have cycle)\n");

  //reset flag
  temp = head[index];
  while(temp){
    if(temp->flag == 0)break;
    temp->flag = 0;
    temp = temp->next;
  }
  
}
int main(){
  //non circular (does not have cycle)
  pushTail(3,0);
  pushTail(5,0);
  pushTail(8,0);
  pushTail(9,0);
  pushTail(10,0);

  checkCycle(0);
  checkCycle(0);
  //circular (does have cycle)
  pushTail(1,1);
  pushTail(2,1);
  pushTail(4,1);
  pushTail(6,1);
  pushTail(10,1);
  tail[1]->next = head[1];

  checkCycle(1);
  checkCycle(1);

}