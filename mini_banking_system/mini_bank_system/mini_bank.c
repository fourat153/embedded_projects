#include "mini_bank.h"

static struct customer add_info();
std_return_t add_custumar(struct customer **head) {
  struct customer *node;
  node = (customer_t *)malloc(sizeof(customer_t));

  printf("enter your age ");
  int a = 0;
  scanf("%d", &a);
  node->age = a;
  if (*head == NULL) {
    (*head) = node;
    (*head)->ptr_next = NULL;

  } else {
    node->ptr_next = (*head);
    (*head) = node;
  }
}
std_return_t delet_custumar(struct customer *custumer_id);
std_return_t show_customers_data(struct customer *custumor);
std_return_t menu();

static struct customer add_info() {
  struct customer node;
  printf("enter your age ");
  scanf("%d", &(node.age));

  return node;
}