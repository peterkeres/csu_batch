#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "jobQueue.c"
#include "commandline.c"


int main(){
	struct jobQ* jobQueue = buildJobQ(100);
	struct job test;
	/*
	int priority;
	int timeToComplete;
	int arrivalTime;
	char jobName[10];
	int turnAround;
	*/
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
