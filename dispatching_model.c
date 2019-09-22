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
