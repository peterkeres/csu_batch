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

	// adds a job to the job que
	addJob(jobQueue, newJob);
	pthread_cond_signal(&jobsInQue);// let the other thread know there are jobs in the jobQueue now

}
