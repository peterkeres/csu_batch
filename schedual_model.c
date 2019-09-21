#include <stdio.h>
#include <stdlib.h>
#include "schedual_model.h"



void test(void * num){
  puts("inside schedual model file");

  int *number = (int *) num;

  printf(" number passed is: %d\n", *number);


}
