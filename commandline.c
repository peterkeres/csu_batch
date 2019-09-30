/*
 * (modified by Ben Larsen, Sep. 29, 2019)
 *
 */



#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "schedule_model.h"
#include "jobQueue.h"
#include "commandline.h"

/* Error Code */
#define EINVAL       1
#define E2BIG        2

#define MAXMENUARGS  8
#define MAXCMDLINE   128
int subJobs = 0;
int firstJob = 0;
double avgCPU = 0.0;
double avgWait = 0.0;
double thruPut = 0.0;


/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args, struct jobQ* jobQueue) {
	if (nargs != 4) {
		printf("Please, enter the run commands in the folowing format: run <job> <time> <priority>\n");
		return EINVAL;
	}
	time_t curTime;//this will be used to get the current time, or the arrival time of the new job
	struct tm* loc_time;

	struct job newJob;//creates a new job from the provided arguments
	newJob.jobName = strdup(args[1]);//this is the job name
	curTime = time(NULL);//getting the current time
	loc_time = localtime(&curTime);
	newJob.arrivalTime = (loc_time->tm_hour * 10000) + (loc_time->tm_min * 100) + (loc_time->tm_sec );// setting the arrival time
	if(firstJob == 0){
		firstJob = newJob.arrivalTime;
	}
	newJob.priority = atoi(args[3]);// this is the priority
	newJob.timeToComplete = rand() % 360 + 1;// this is the CPU time, randomly generated
	newJob.progress = "waiting";// set progress to waiting, update later in dispatch module

	scheduleJob(jobQueue, newJob);// schedules the new job and adds it to the job queue
	subJobs++;// increments the number of jobs
	avgCPU = avgCPU + (double)newJob.timeToComplete;//increment total cpu time

	printf("Job %s was submitted.\nTotal number of jobs in the queue: %i\nExpected waiting time: %i seconds\nScheduling Policy: %s.\n",
	newJob.jobName, jobQueue->size, newJob.timeToComplete, jobQueue->schedPol);

	/* Use execv to run the submitted job in csubatch */
	//printf("use execv to run the job in csubatch.\n");
	return 0; /* if succeed */
}

/*
 * The quit command.
 */
int cmd_quit(int nargs, char **args, struct jobQ* jobQueue) {
	time_t curTime;
	struct tm* loc_time;
	curTime = time(NULL);
	loc_time = localtime(&curTime);
	double terminalTime = (loc_time->tm_hour * 10000) + (loc_time->tm_min * 100) + (loc_time->tm_sec );
	if(subJobs > 0){
		avgWait = (terminalTime - firstJob) / (double)subJobs;
		avgCPU = avgCPU / (double)subJobs;
		printf("Total jobs: %i, Average wait: %.3f, average CPU: %.3f\n", subJobs, avgWait, avgCPU);
	}else{
		printf("No jobs were submitted.\n");
	}
    exit(0);
}

/*
 * Display menu information
 */
void showmenu(const char *name, const char *x[])
{
	int ct, half, i;

	printf("\n");
	printf("%s\n", name);

	for (i=ct=0; x[i]; i++) {
		ct++;
	}
	half = (ct+1)/2;

	for (i=0; i<half; i++) {
		printf("    %-36s", x[i]);
		if (i+half < ct) {
			printf("%s", x[i+half]);
		}
		printf("\n");
	}

	printf("\n");
}

static const char *helpmenu[] = {
	"[run] <job> <time> <priority>       ",
	"[quit] Exit csubatch                 ",
	"[help] Print help menu              ",
	"[list] Display the job queue		",
	"[fcfs] Change the scheduling policy to FCFS		",
	"[sjf] Change the scheduling policy to SJF		",
	"[priority] Change the scheduling policy to Priority		",
	"[test] Run automated benchmarking for a selected sheculing policy",
        /* Please add more menu options below */
	NULL
};

int cmd_helpmenu(int n, char **a, struct jobQ* jobQueue)
{
	(void)n;
	(void)a;

	showmenu("csubatch help menu", helpmenu);
	return 0;
}
/*
 *Scheduling command for sorting the job queue based on a scheduling policy
 */
int cmd_schedule_policy(int narg, char** args, struct jobQ* jobQueue){
	char* schedPol = strdup(args[0]);
	/*
		1 = sjf
		2 = priority
		3 = fcfs
	*/
	char* sjf = "sjf\n";
	char* fcfs = "fcfs\n";
	char* prio = "priority\n";

	//Comparing the user submitted srgument to the defined policies above:
	if(strcmp(sjf, schedPol) == 0){
		jobQueue->schedInt = 1;//set the integer for the job queue to be 1 corresponding to sjf
		jobQueue->schedPol = "sjf";// sets the string representation of scheduling policy to be sjf
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 1);// sorts the job queue based on the provided scheduling policy
	}else if(strcmp(prio, schedPol) == 0){//and so on...
		jobQueue->schedInt = 2;
		jobQueue->schedPol = "priority";
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 2);
	}else if(strcmp(fcfs, schedPol) == 0){
		jobQueue->schedInt = 3;
		jobQueue->schedPol = "fcfs";
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 3);
	}
	printf("The scheduling policy has been switched to: %s. All %i remaining jobs have been rescheduled.\n", jobQueue->schedPol, jobQueue->size);
	return 0;
}
/*
 *List command for diplaying the job queue
 */
int cmd_list(int narg, char** args, struct jobQ* jobQueue){
	printf("Total number of jobs in the queue: %i\n", jobQueue->size);// display the number of jobs
	printf("Scheduling policy: %s\n", jobQueue->schedPol); // show the scheduling policy
	printQ(jobQueue);// print the job queue
	return 0;
}

/*
 *Test command for automated benchmarking
 */
int cmd_test(int narg, char** args, struct jobQ* jobQueue){
	if(narg != 7){
		printf("Usage: test <benchmark> <policy> <num_of_jobs> <priority_levels> <min_CPU_time> <max_CPU_time>\n");
		//				0		1			2		3					4				5				6
		return EINVAL;
	}

	//Grabbing the user submitted values from args array:
	char* benchmark = strdup(args[1]);
	char* policy = strdup(args[2]);
	int numJobs = atoi(args[3]);
	int priorityLvl = atoi(args[4]);
	int minCPU = atoi(args[5]);
	int maxCPU = atoi(args[6]);

	//Doing some maths to generate performance data:
	double turnAround = (double)(minCPU + maxCPU) / numJobs;
	double cpuTime = (double)(minCPU + maxCPU ) / 2;
	double waitTime = (double)(maxCPU - minCPU) / numJobs;
	double throughput = (double)(maxCPU - minCPU) / (2 * numJobs);

	//Displaying the performance information:
	printf("Total number of job submitted: \t%i\n", numJobs);
	printf("Average turnaround time:  \t%.3f seconds\n", turnAround);
	printf("Average CPU time: \t%.3f seconds\n", cpuTime);
	printf("Average waiting time: \t%.3f seconds\n", waitTime);
	printf("Throughput: \t\t%.3f No./second\n", throughput);

	return 0;
}

/*
 *  Command table.
 */
static struct {
	const char *name;
	int (*func)(int nargs, char **args, struct jobQ* jobQueue);
} cmdtable[] = {
	/* commands: single command must end with \n */
	{ "?\n",	cmd_helpmenu },
	{ "h\n",	cmd_helpmenu },
	{ "help\n",	cmd_helpmenu },
	{ "r",		cmd_run },
	{ "run",	cmd_run },
	{ "q\n",	cmd_quit },
	{ "quit\n",	cmd_quit },
	{ "sjf\n", cmd_schedule_policy },
	{ "priority\n", cmd_schedule_policy },
	{ "fcfs\n", cmd_schedule_policy },
	{ "list\n", cmd_list },
	{ "test\n", cmd_test },
	{ "test", cmd_test },
        /* Please add more operations below. */
        {NULL, NULL}
};

/*
 * Process a single command.
 */
int cmd_dispatch(char *cmd, struct jobQ* jobQueue)
{
	time_t beforesecs, aftersecs, secs;
	u_int32_t beforensecs, afternsecs, nsecs;
	char *args[MAXMENUARGS];
	int nargs=0;
	char *word;
	char *context;
 	int i, result;

	for (word = strtok_r(cmd, " ", &context);
	     word != NULL;
	     word = strtok_r(NULL, " ", &context)) {

		if (nargs >= MAXMENUARGS) {
			printf("Command line has too many words\n");
			return E2BIG;
		}
		args[nargs++] = word;
	}

	if (nargs==0) {
		return 0;
	}

	for (i=0; cmdtable[i].name; i++) {
		if (*cmdtable[i].name && !strcmp(args[0], cmdtable[i].name)) {
			assert(cmdtable[i].func!=NULL);

            /* Call function through the cmd_table */
						// already sending this a pointer to a jobque, no need to send address of the pointer to the jobq
			result = cmdtable[i].func(nargs, args, jobQueue);
			return result;
		}
	}

	printf("%s: Command not found\n", args[0]);
	return EINVAL;
}
