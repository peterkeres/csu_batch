/*
 * peter keres Ben Larsen
 * sep 28 2019
 *
 * this is the main for the CSU Batch processing system
*/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jobQueue.h"
#include "commandline.h"
#include "schedule_model.h"
#include "dispatching_model.h"
#include	<unistd.h>



// ALL GLOBAL VERALBES
pthread_t thread_schedual, thread_dispatch;// the 2 threads we will be using
pthread_mutex_t queMutex;// the mutex that will stop other threads from messing with the jobQueue
pthread_cond_t jobsInQue;// a singal to let other thread know there are jobs in the que
pthread_cond_t queNotFull;// a singal to let other threads know there is room in the job que
int status_schedual, status_dispatch; // ids of the threads
struct jobQ* jobQueue;// the jobQueue data structre that holds all the jobs

int main(){

	puts("SYSTEM START UP\n");

	// createing the jobQueue and the mutex and the signal verable
	jobQueue = buildJobQ(100);
	pthread_mutex_init(&queMutex,NULL);
	pthread_cond_init(&jobsInQue,NULL);
	pthread_cond_init(&queNotFull,NULL);

	// welcome message
	puts("Welcome to the CSU batch processing system v1.0");
	puts("type in \'help\' to find out more about the CSU Batch commands");

	// creads the thread, calls the method test3 with that threads
	status_schedual = pthread_create(&thread_schedual, NULL, schedule_start, NULL);
	// makes sure the thread was created
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}


	//creates the thread, calls the method nextJob wih that thread
	status_dispatch = pthread_create(&thread_dispatch, NULL, nextJob, NULL);
	// makes sure the thread was created
	if (status_dispatch != 0) {
		puts("dispatch failed on creation");
		exit(-1);
	}


	// ends the 2 threads
	pthread_join(thread_schedual,NULL);
	pthread_join(thread_dispatch, NULL);


	puts("\nEND OF PROGRAM\n");
	return 0;
}
