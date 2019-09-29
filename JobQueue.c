/*
 * Ben Larsen
 * 20190928
 * data structure for storing, maintaining and sorting a job queue
 */



#include <stdio.h>
#include <stdlib.h>
#include "jobQueue.h"
/*
 * Creates a job queue and retruns a pointer to the queue
 */
struct jobQ* buildJobQ(int capacity){
	struct jobQ* jobQueue = (struct jobQ*) malloc(sizeof(struct jobQ));
	jobQueue->numJobs = capacity;// sets the max number of jobs
	jobQueue->size = 0;// initializes the size, etc..
	jobQueue->first = 0;
	jobQueue->last = capacity - 1;
	jobQueue->schedPol = "fcfs";
	jobQueue->schedInt = 3;
	jobQueue->jobs = (struct job*) malloc(sizeof(struct job) * jobQueue->numJobs);// an array for holding the job structs
	return jobQueue;
}

/*
 *returns whether the queue is full or not
 */
int isFull(struct jobQ* jobQ){
	return (jobQ->size == jobQ->numJobs);
}
/*
 *Returns 0 if the queue is empty
 */
int isEmpty(struct jobQ* jobQ){
	return (jobQ->size == 0);
}
/*
 *Adds a job to the job queue
 */
void addJob(struct jobQ* jobQ, struct job job){
	if(isFull(jobQ)){
		printf("The job queue is full.");
	}
	jobQ->last = (jobQ->last + 1) % jobQ->numJobs;
	jobQ->jobs[jobQ->last] = job;
	jobQ->size++;
	//This block sorts the queue according to the current scheduling policy after the job is added
	//this allows the order of the job queue to comply with the current scheduling policy
	if(jobQ->schedInt == 1){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 1);
	}else if(jobQ->schedInt == 2){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 2);
	}else if(jobQ->schedInt == 3){
		quickSort(jobQ->jobs, 0, jobQ->size - 1, 3);
	}
}
/*
 *Removes the first job from the queue
 */
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

/*
 *Function for displaying the job queue
 */
void printQ(struct jobQ* jobQ){
	if(isEmpty(jobQ)){
		printf("No jobs in the queue!\n");
	}else{
		struct job* jobs = jobQ->jobs;
		int i = 0;
		printf("Name\tCPU time\tPri\tArrival Time\tProgress\n");
		for(i = 0; i < jobQ->size; ++i){
			printf("%s\t  %i\t\t%i\t%i\t\t%s\n", jobQ->jobs[i].jobName, jobQ->jobs[i].timeToComplete, jobQ->jobs[i].priority, jobQ->jobs[i].arrivalTime,
			jobQ->jobs[i].progress);

		}
	}
}
//The following functions are for sorting the job queue based on a scheduling policy

/*
 * swaps to jobs in the job queue
 */
void swap(struct job* a, struct job* b) {
    struct job t = *a;
    *a = *b;
    *b = t;
}
/*
 *modified prtition function for sorting the queue
 *int schedPol is added to sort the array of jobs
 *based on a specified scheduling policy
 */
int partition (struct job arr[], int low, int high, int schedPol) {
    struct job pivot = arr[high];
    int i = (low - 1);
	int j;
	if(schedPol == 1){//shortest job first
		for (j = low; j <= high- 1; j++) {
        	if (arr[j].timeToComplete < pivot.timeToComplete) {
            	i++;
            	swap(&arr[i], &arr[j]);
        	}
    	}
	}else if(schedPol == 2){//priority
		for (j = low; j <= high- 1; j++) {
        	if (arr[j].priority < pivot.priority) {
            	i++;
            	swap(&arr[i], &arr[j]);
        	}
    	}
	}else if(schedPol == 3){//first come, first serve
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
/*
 *quick sort modified for sorting based on scheduling policy
 */
void quickSort(struct job arr[], int low, int high, int schedPol) {
    if (low < high){
        int pi = partition(arr, low, high, schedPol);

        quickSort(arr, low, pi - 1,schedPol);
        quickSort(arr, pi + 1, high, schedPol);
    }
}
