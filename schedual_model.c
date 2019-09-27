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
#include <pthread.h>
#include "schedual_model.h"
#include "jobQueue.h"



void test3(){
  struct job test;
  struct job test2;

	test.jobName = "example_batch";
  test2.jobName = "example_batch";

  pthread_mutex_lock(&queMutex);

	addJob(jobQueue, test);
  for (size_t i = 0; i < 100; i++) {
    // just to make sure the mutext is working have it suck in this thread for a bit
  }
  addJob(jobQueue, test2);

  pthread_cond_signal(&queCond);

  pthread_mutex_unlock(&queMutex);

  pthread_exit(NULL);

}
