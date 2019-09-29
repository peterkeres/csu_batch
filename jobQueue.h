/*
 * Ben Larsen
 * 20190928
 *
 */

#ifndef	JOBQUEUE_H
#define JOBQUEUE_H


struct job{
	int priority;
	int timeToComplete;
	int arrivalTime;
	char* jobName;
	char* progress;
};

struct jobQ{
	int first, last, size, numJobs;
	int schedInt;
	char* schedPol;
	struct job* jobs;
};

struct jobQ* buildJobQ(int capacity);
int isFull(struct jobQ* jobQ);
int isEmpty(struct jobQ* jobQ);
void addJob(struct jobQ* jobQ, struct job job);
struct job removeJob(struct jobQ* jobQ);
void printQ(struct jobQ* jobQ);
void swap(struct job* a, struct job* b);
int partition (struct job arr[], int low, int high, int schedPol);
void quickSort(struct job arr[], int low, int high, int schedPol);


#endif
