/*
peter keres
sep 21 2019

file for the dispatching modle
the dispatching model will handle the execution of any batch file pulled form the queue
this ill hold the 'execv' fucntion that will run the batch file given

should also send off any data to the 'performace modeul' as needed
*/



#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "jobQueue.h"
#include "dispatching_model.h"


// this should run forever untill the user enters quit
void nextJob(){

  // runs forever 
  while(1){
    // locks out the other threads from messing with the jobQueue
    pthread_mutex_lock(&queMutex);

    // if the jobQueue is empty, we wait until told there is somthing in the jobQueue
    while( isEmpty(jobQueue) ){
        // waits untill told by the signal
        pthread_cond_wait(&jobsInQue, &queMutex);
    }

    // gets the next job from the jobQueue
    struct job nextjob = removeJob(jobQueue);

    // lets other threads know there is an opening in the job queue
    pthread_cond_signal(&queNotFull);

    // frees up the jobQueue, got what we needed
    pthread_mutex_unlock(&queMutex);


    // takes out the name from the job object, sends it to the job_exe() which will run the job
    char * name = nextjob.jobName;
    char * args[] = {name,NULL};
    job_exe((void*) &args);

  }

}



// this will excute a job given
void job_exe(void * args[]){

  // the id of the new created process aka the fork
  pid_t pid;

  // this makes the new process
  pid = fork();

  // if a error happend in the fork / process creation
  if (pid == -1) {
    puts("error happend when making the fork");
  // child process, we let it call the other program
  // execv will kill the current process, so we let the child take care of that and let it die
  // that way the parent can live on and go back to the calling code
  } else if (pid == 0) {
    execv(args[0], args);
  }
  // parent/ calling process. have it wait untill child is done
  // if not, the main program could end before the execv is finished
  else{
    wait(NULL);
  }

}
