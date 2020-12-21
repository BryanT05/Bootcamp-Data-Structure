d printLinkedList() {
  Node *curr = head;
                                          
  while(curr) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}