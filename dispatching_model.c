/*
peter keres
sep 21 2019

file for the dispatching modle
the dispatching model will handle the execution of any batch file pulled form the queue
this ill hold the 'execv' fucntion that will run the batch file given

should also send off any data to the 'performace modeul' as needed
*/



void start(void * args[]){

  puts("in the dispatching_module, about to run the other program");


  execv(args[0], args);
  
}
