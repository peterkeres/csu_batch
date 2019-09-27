/*
peter keres
sep 21 2019

header file for the schedualing modle
the schedualing model will handle any schedualing events that need
to happen in the csu batch system.
*/


extern pthread_mutex_t queMutex;
extern pthread_cond_t queCond;
extern struct jobQ* jobQueue;

void test3();
