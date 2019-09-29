/*
 * Ben Larsen
 * 20190928
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "jobQueue.h"

struct jobQ* buildJobQ(int capacity){
	struct jobQ* jobQueue = (struct jobQ*) malloc(sizeof(struct jobQ));
	jobQueue->numJobs = capacity;
	jobQueue->size = 0;
	jobQueue->first = 0;
	jobQueue->last = capacity - 1;
	jobQueue->schedPol = "fcfs";
	jobQueue->schedInt = 3;
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
		return;
	}
	jobQ->last = (jobQ->last + 1) % jobQ->numJobs;
	jobQ->jobs[jobQ->last] = job;
	jobQ->size++;
	if(jobQ->schedInt == 1){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 1);
	}else if(jobQ->schedInt == 2){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 2);
	}else if(jobQ->schedInt == 3){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 3);
	}
}

struct job removeJob(struct jobQ* jobQ){
	struct job job;
	if(isEmpty(jobQ)){
		printf("Job queue is emtpy.\n");
		exit(1);
	}
	job = jobQ->jobs[jobQ->first];
	jobQ->first = (jobQ->first + 1) % jobQ->numJobs;
	jobQ->size --;
	return job;

}
void printQ(struct jobQ* jobQ){
	if(isEmpty(jobQ)){
		printf("No jobs in the queue!\n");
	}else{
		struct job* jobs = jobQ->jobs;
		int i = 0;
		printf("Name\tCPU time\tPri\tArrival Time\tProgress\n");
		for(i = 0; i < jobQ->size; ++i){
			printf("%s\t  %i\t\t%i\t\t%i\t%i\n", jobQ->jobs[i].jobName, jobQ->jobs[i].timeToComplete, jobQ->jobs[i].priority, jobQ->jobs[i].arrivalTime, 
			jobQ->jobs[i].turnAround);
			
		}
	}
}
void swap(struct job* a, struct job* b) { 
    struct job t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (struct job arr[], int low, int high, int schedPol) { 
    struct job pivot = arr[high];
    int i = (low - 1);
	int j;
	if(schedPol == 1){
		for (j = low; j <= high- 1; j++) { 
        	if (arr[j].timeToComplete < pivot.timeToComplete) { 
            	i++;
            	swap(&arr[i], &arr[j]); 
        	} 
    	} 
	}else if(schedPol == 2){
		for (j = low; j <= high- 1; j++) { 
        	if (arr[j].priority < pivot.priority) { 
            	i++;
            	swap(&arr[i], &arr[j]); 
        	} 
    	} 
	}else if(schedPol == 3){
		for (j = low; j <= high- 1; j++) { 
        	if (arr[j].arrivalTime < pivot.arrivalTime) { 
            	i++;
            	swap(&arr[i], &arr[j]); 
        	} 
    	} 
	}
    
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(struct job arr[], int low, int high, int schedPol) { 
    if (low < high){ 
        int pi = partition(arr, low, high, schedPol); 
  
        quickSort(arr, low, pi - 1,schedPol); 
        quickSort(arr, pi + 1, high, schedPol); 
    } 
} 

