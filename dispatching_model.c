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

void start(void * args[]){

  puts("in the dispatching_module, about to run the other program");


  pid_t pid;

  pid = fork();

  // if a error happend in the fork 
  if (pid == -1) {
    puts("error happend when making the fork");
  // child process, we let it call the other program
  } else if (pid == 0) {
    execv(args[0], args);
  }
  // parent/ calling process. have it wait untill child is done
  else{
    wait(NULL);
  }

}
