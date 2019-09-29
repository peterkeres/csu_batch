/*
 * (modified by Ben Larsen, Sep. 28, 2019)
 * 
 */
 
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "schedule_model.h"
#include "jobQueue.h"

/* Error Code */
#define EINVAL       1
#define E2BIG        2

#define MAXMENUARGS  4 
#define MAXCMDLINE   64 

/*void menu_execute(char *line, int isargs); 
int cmd_run(int nargs, char **args, struct jobQ* jobQueue); 
int cmd_quit(int nargs, char **args, struct jobQ* jobQueue); 
void showmenu(const char *name, const char *x[]);
int cmd_helpmenu(int n, char **a, struct jobQ* jobQueue);
int cmd_dispatch(char *cmd, struct jobQ* jobQueue);*/

/*
 * The run command - submit a job.
 */
int cmd_run(int nargs, char **args, struct jobQ* jobQueue) {
	if (nargs != 4) {
		printf("Usage: run <job> <time> <priority>\n");
		return EINVAL;
	}
    int i;
	for(i = 1; i < nargs; ++i){
		printf("%s\n", args[i]);
	}
	struct job newJob;
	newJob.jobName = strdup(args[1]);
	newJob.arrivalTime = atoi(args[2]);
	newJob.priority = atoi(args[3]);
	newJob.timeToComplete = rand() % 360 + 1;
	newJob.turnAround = 1;
	//addJob(jobQueue, newJob);
	scheduleJob(jobQueue, newJob);
	
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
	printf("Please display performance information before exiting csubatch!\n");
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
	//void quickSort(struct job arr[], int low, int high, int schedPol)
	
	if(strcmp(sjf, schedPol) == 0){
		jobQueue->schedInt = 1;
		jobQueue->schedPol = "sjf";
		quickSort(jobQueue->jobs, 0, jobQueue->size - 1, 1);
	}else if(strcmp(prio, schedPol) == 0){
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

int cmd_list(int narg, char** args, struct jobQ* jobQueue){
	printf("Total number of jobs in the queue: %i\n", jobQueue->size);
	printf("Scheduling policy: %s\n", jobQueue->schedPol);
	printQ(jobQueue);
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
			result = cmdtable[i].func(nargs, args, jobQueue);
			return result;
		}
	}

	printf("%s: Command not found\n", args[0]);
	return EINVAL;
}


