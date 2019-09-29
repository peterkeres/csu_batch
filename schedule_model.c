/*
peter keres
sep 21 2019
(modified by Ben Larsen, Sep. 28, 2019)

 file for the scheduling modle
the scheduling model will handle any scheduling events that need
to happen in the csu batch system.

this once other classes send this the name of the batch job, it will go find it
put it in the queue

also in chagre of changing the queue order when a policiy change happens.

*/




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "jobQueue.h"
#include "schedule_model.h"


void schedule_start(){

	// display some menu

	while (1){


		// gets area ready for user input
		char *input_str;
		int input_size = 64;
		input_str = (char*) malloc(input_size * sizeof(char));
		if (input_str == NULL) {
				perror("Unable to malloc buffer");
				exit(1);
		}
		printf(">");

		// watis for user to hit enter and grabs what they have
		getline(&input_str, &input_size, stdin);

		// lock mutext once we get input from readline
		pthread_mutex_lock(&queMutex);

		// send it to cmd dispatch
		cmd_dispatch(input_str, jobQueue);

		// unlock the mutext
		pthread_mutex_unlock(&queMutex);


	}




}





// this will creat the jobs that go into the jobQueue
// testing: as of right now, the jobs are hardcoded in, later we will grab from user
void scheduleJob(struct jobQ* jobQueue, struct job newJob){

	// create 2 jobs
	//struct job test;
	//struct job test2;

	// give each job a file path to an exe
	//test.jobName = "example_batch";
	//test2.jobName = "example_batch";


	//pthread_mutex_lock(&queMutex);// locks the other thread from messing with the jobQueue

	//addJob(jobQueue, test);// add a job to the job queue
	//for (size_t i = 0; i < 100; i++) {
		// just to make sure the mutext is working have it suck in this thread for a bit
	//}
	//addJob(jobQueue, test2);// add job2 to the jobQueue
	puts("about to add job\n");
	addJob(jobQueue, newJob);
	puts("job was added \n");
	pthread_cond_signal(&jobsInQue);// let the other thread know there are jobs in the jobQueue now

	//pthread_mutex_unlock(&queMutex);  // unlocks the other thread, it can now mess with the jobQueue


	// testing: becuase only doing 2 hard coded jobs, we can just kill this thread now
	//pthread_exit(NULL);

}
/*void scheduleJob(){

	// create 2 jobs
	struct job test;
	struct job test2;

	// give each job a file path to an exe
	test.jobName = "example_batch";
	test2.jobName = "example_batch";

	pthread_mutex_lock(&queMutex);// locks the other thread from messing with the jobQueue

	addJob(jobQueue, test);// add a job to the job queue
	for (size_t i = 0; i < 100; i++) {
		// just to make sure the mutext is working have it suck in this thread for a bit
	}
	addJob(jobQueue, test2);// add job2 to the jobQueue

	pthread_cond_signal(&jobsInQue);// let the other thread know there are jobs in the jobQueue now

	pthread_mutex_unlock(&queMutex);  // unlocks the other thread, it can now mess with the jobQueue


	// testing: becuase only doing 2 hard coded jobs, we can just kill this thread now
	pthread_exit(NULL);

}*/
