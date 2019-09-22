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

void * stuff ();
void * stuff2 (void * num);

int main(){

	puts("hello, seeing if compile works!");

	// createing the 2 threads
	pthread_t thread_schedual, thread_dispatch;

	int status_schedual, status_dispatch;
	int num = 5;

	status_schedual = pthread_create(&thread_schedual, NULL, stuff, NULL);
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}

	status_dispatch = pthread_create(&thread_dispatch, NULL, stuff2, (void *) &num);
	if (status_dispatch != 0) {
		puts("dispatch failed on creation");
		exit(-1);
	}


	pthread_join(thread_schedual,NULL);
	pthread_join(thread_dispatch, NULL);

	printf("status_schedual returns: %d\n",status_schedual );
	printf("status_dispatch returns: %d\n",status_dispatch );

	puts("Calling method in other file with thread_schedual\n");

	status_schedual = pthread_create(&thread_schedual, NULL, test, (void *) &num);
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}


	pthread_join(thread_schedual,NULL);
	puts("calling method in other file wihtout thread\n");
	test((void*) &num);

	/*
	puts("going to call the other program using execv, wish me luck\n");
	char *args[] = {"./example_batch", NULL};
	execv(args[0], args);
	*/

	char *args[] = {"./example_batch", NULL};
	puts("going to call the exexc within an another fiel using a thread. this would be great is worked!");
	status_schedual = pthread_create(&thread_schedual, NULL, start, (void *) &args);
	if (status_schedual != 0) {
		puts("schedual fialed on creation");
		exit(-1);
	}
	pthread_join(thread_schedual,NULL);


	puts("end of program, both threads joined");


	return 0;
}


// test methods for calling threads to make sure i got it right, delete later
void * stuff(){
	puts("method called by the first thread \n");
	pthread_exit(NULL);
}
// test methods for calling threads to make sure i got it right, delete later
void * stuff2(void * num){
	puts(" method called by the second thread \n");

	int* number = (int*) num;

	printf("number is : %d\n", *number);

	pthread_exit(NULL);

}
