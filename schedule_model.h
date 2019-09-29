/*
peter keres
sep 21 2019
(modified by Ben Larsen, Sep 28, 2019)

header file for the scheduling module
the schedualing model will handle any schedualing events that need
to happen in the csu batch system.
*/

// this lets us get the varables that are global in the main. c file
pthread_mutex_t queMutex;
pthread_cond_t jobsInQue;
extern struct jobQ* jobQueue;
extern struct job newJob;


//void newJob();
void scheduleJob(struct jobQ* jobQueue, struct job newJob);