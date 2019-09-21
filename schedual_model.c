/*
peter keres
sep 21 2019

 file for the schedualing modle
the schedualing model will handle any schedualing events that need
to happen in the csu batch system.

this once other classes send this the name of the batch job, it will go find it
put it in the queuw

also in chagre of changing the que order when a policiy change happens.

*/


#include <stdio.h>
#include <stdlib.h>
#include "schedual_model.h"



void test(void * num){
  puts("inside schedual model file");

  int *number = (int *) num;

  printf(" number passed is: %d\n", *number);


}
