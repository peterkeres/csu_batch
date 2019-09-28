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


// this will creat the jobs that go into the jobQueue
// testing: as of right now, the jobs are hardcoded in, later we will grab from user
void newJob(){

  // create 2 jobs
  struct job test;
  struct job test2;

  // give each job a file path to an exe
	test.jobName = "example_batch";
  test2.jobName = "example_batch2";

  pthread_mutex_lock(&queMutex);// locks the other thread from messing with the jobQueue

  // this to stop from adding to the jobQueue if the job queue is currently full
  while ( isFull(jobQueue) ){
    // wait unitll the jobQueue is not full anymore, open spot
    pthread_cond_wait(&queNotFull, &queMutex);
  }

	addJob(jobQueue, test);// add a job to the job queue
  for (size_t i = 0; i < 100; i++) {
    // just to make sure the mutext is working have it suck in this thread for a bit
  }
  addJob(jobQueue, test2);// add job2 to the jobQueue

  pthread_cond_signal(&jobsInQue);// let the other thread know there are jobs in the jobQueue now

  pthread_mutex_unlock(&queMutex);  // unlocks the other thread, it can now mess with the jobQueue


  // testing: becuase only doing 2 hard coded jobs, we can just kill this thread now
  pthread_exit(NULL);

}
