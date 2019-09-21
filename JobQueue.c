#include <stdio.h>
#include <stdlib.h>
#include "jobQueue.h"

struct jobQ* buildJobQ(int capacity){
	struct jobQ* jobQueue = (struct jobQ*) malloc(sizeof(struct jobQ));
	jobQueue->numJobs = capacity;
	jobQueue->size = 0;
	jobQueue->first = 0;
	jobQueue->last = capacity - 1;
	jobQueue->jobs = (struct job*) malloc(sizeof(struct job) * jobQueue->numJobs);
	return jobQueue;
}

int isFull(struct jobQ* jobQ){
	return (jobQ->size == jobQ->numJobs);
}

int isEmpty(struct jobQ* jobQ){
	return (jobQ->size == 0);
}

void addJob(struct jobQ* jobQ, struct job job){
	if(isFull(jobQ)){
		printf("The job queue is full.");
	}
	jobQ->last = (jobQ->last + 1) % jobQ->numJobs;
	jobQ->jobs[jobQ->last] = job;
	jobQ->size++;
}

struct job removeJob(struct jobQ* jobQ){
	if(isEmpty(jobQ)){
		printf("Job queue is emtpy.\n");
		// need to have somthing return, get compile error
		//return;
	}
	struct job job = jobQ->jobs[jobQ->first];
	jobQ->first = (jobQ->first + 1) % jobQ->numJobs;
	jobQ->size --;
	return job;

}
void printQ(struct jobQ* jobQ){
	if(isEmpty(jobQ)){
		printf("No jobs in the queue!\n");
		return;
	}
	struct job* jobs = jobQ->jobs;
	int i = 0;

	for(i = 0; i < jobQ->size; ++i){
		printf("Job name: %s\n", jobQ->jobs[i].jobName);
	}
}
