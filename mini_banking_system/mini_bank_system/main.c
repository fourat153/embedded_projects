#include "mini_bank.h"
#include <stdio.h>

int main() {

  struct customer *head = NULL;

  add_custumar(&head);
  printf("%d\n", head->age);
  printf("%d\n", head->ptr_next);
  add_custumar(&head);
  printf("%d\n", head->age);
  printf("%d\n", head->ptr_next);
  add_custumar(&head);
  printf("%d\n", head->age);
  printf("%d\n", head->ptr_next);
  add_custumar(&head);
  printf("%d\n", head->age);
  printf("%d\n", head->ptr_next);
  add_custumar(&head);
  printf("%d\n", head->age);
  printf("%d\n", head->ptr_next);
  add_custumar(&head);
  printf("%d\n", head->age);
  printf("%d\n", head->ptr_next);

  struct customer * temp = head ;

  while (temp != NULL)
  {
    printf("%d\n" , temp->age); 
    temp = temp->ptr_next;
  }
 
  
  return 0;
}