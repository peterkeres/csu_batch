/*
peter keres
sep 21 2019

header file for the dispatching modle
the dispatching model will handle the execution of any batch file pulled form the queue
this ill hold the 'execv' fucntion that will run the batch file given

should also send off any data to the 'performace modeul' as needed
*/

// this lets us get the varables that are globale in the main. c file
extern pthread_mutex_t queMutex;
extern pthread_cond_t jobsInQue;
extern struct jobQ* jobQueue;

void job_exe(void * args[]);

void nextJob();
