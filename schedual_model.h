/*
peter keres
sep 21 2019

header file for the schedualing modle
the schedualing model will handle any schedualing events that need
to happen in the csu batch system.
*/

// this lets us get the varables that are globale in the main. c file
extern pthread_mutex_t queMutex;
extern pthread_cond_t jobsInQue;
extern pthread_cond_t queNotFull;
extern struct jobQ* jobQueue;


// method that creates the jobs, call this when creating a thread
void newJob();
