#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jobQueue.h"
#include "commandline.c"
#include "schedual_model.h"
#include "dispatching_model.h"
#include	<unistd.h>


/*
// i comment this out becuase i was going to work on threads and didnt want to mess up your work
// just comment out my main when you want to go back to your work
// maybe we should just renaim this file to be test lol

int main(){
	struct jobQ* jobQueue = buildJobQ(100);
	struct job test;
	/*
	int priority;
	int timeToComplete;
	int arrivalTime;
	char jobName[10];
	int turnAround;
	//
	test.priority = 1;
	test.timeToComplete = 5;
	test.arrivalTime = 10;
	test.jobName = "job 1";
	test.turnAround = 2;
	addJob(jobQueue, test);
	printQ(jobQueue);
	//printf("%i\n", test.priority);
	removeJob(jobQueue);
	printQ(jobQueue);
	//printQ(jobQueue);

	char *buffer;
        size_t bufsize = 64;

        buffer = (char*) malloc(bufsize * sizeof(char));
        if (buffer == NULL) {
 		perror("Unable to malloc buffer");
 		exit(1);
	}

    while (1) {
		printf("> [? for menu]: ");
		getline(&buffer, &bufsize, stdin);
		cmd_dispatch(buffer);
	}
        return 0;
}
*/



/*
here is my test envirment for getting 2 threads to work
each thread will cal a file: schedual and dispatching
they each will run some simple printjust to make sure this works
*/

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

	// creads the thread, calls the method test3 with that threads
	status_schedual = pthread_create(&thread_schedual, NULL, newJob, NULL);
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



/*
int main(){

	puts("hello, seeing if compile works!");

	// createing the 2 threads
	pthread_t thread_schedual, thread_dispatch;

	int status_schedual, status_dispatch;
	int num = 5;

	// creads the thread, calls the method stuff with that threads
	status_schedual = pthread_create(&thread_schedual, NULL, stuff, NULL);
	// makes sure the thread was created
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}

	//creates the thread, calls the method suff2 wih that thread
	status_dispatch = pthread_create(&thread_dispatch, NULL, stuff2, (void *) &num);
	// maes sure the thread was created
	if (status_dispatch != 0) {
		puts("dispatch failed on creation");
		exit(-1);
	}

	// ends the 2 threads
	pthread_join(thread_schedual,NULL);
	pthread_join(thread_dispatch, NULL);

	printf("status_schedual returns: %d\n",status_schedual );
	printf("status_dispatch returns: %d\n",status_dispatch );

	// creates a thread and calls a test function in another file, sends it a number
	puts("Calling method in other file with thread_schedual\n");
	status_schedual = pthread_create(&thread_schedual, NULL, test, (void *) &num);
	// makes sure the thread was created
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}

	// ends the thread
	pthread_join(thread_schedual,NULL);
	// this just calls the method in another file
	puts("calling method in other file wihtout thread\n");
	test((void*) &num);

	/*
	// the execv function runs another program
	puts("going to call the other program using execv, wish me luck\n");
	// this array of chars is what gets sent to the execv fucntion
	// first part of the array is the path to the file you want to run
	// last part of the array must end in NULL
	// nay part inbetween is used for if the program your callling needs inputs
	char *args[] = {"./example_batch", NULL};
	execv(args[0], args);


	// calling the example_batch file that is in this directory
	char *args[] = {"example_batch", NULL};
	puts("going to call the exexc within an another fiel using a thread. this would be great is worked!");
	// creat a new thread that calls the start fruntion of the dispatch file
	// we send it the args needed for the execv fution
	status_schedual = pthread_create(&thread_schedual, NULL, start, (void *) &args);
	// makes sure the thread was created
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}
	// ends the thread
	pthread_join(thread_schedual,NULL);

	puts("testing makeing a job que and running from job que\n");

	struct jobQ* jobQueue = buildJobQ(100);
	struct job test;

	test.jobName = "example_batch";

	addJob(jobQueue, test);
	printQ(jobQueue);

	char name[] = "hello";
	printf("%s\n",name);

	nextJob(jobQueue);

	puts("end of program, both threads joined");


	return 0;
}
*/
