Hello and thank you for using our CSU batch processing system!

The following document is the instruction manual for the program

Any question or concern please direct them towards the two developers
  peter keres: keres_peter@columbusstate.edu
  Ben Larsen: larsen_ben@columbusstate.edu


CONFIGURATION INSTRUCTIONS:
  Please make sure you have the 'GCC' compiler or equivalent installed on your system.
  to see if you have this compiler installed, go to the command line and type 'GCC --which'.
  Also make sure you have access to the 'make' application
  The batch jobs you are submitting to the system, They must be in the same directory as the program files
  As of v1.0, there is no current system for running batch files not in the same directory.

  to see some same batch process, we include 2 sample batch process. 'example_batch' and 'example_batch2'
  Inorder to run these files, they must be compiled first
  run the following make command 'make example example2'


INSTALLATION INSTRUCTIONS:
  Once it is GCC is installed, go to the current directly where you put the program. Run the 'make' command.
  The make command will compile all the code need for the program to run.
  Afterwords, you should have a "csubatch" excitable file to run.
  Run this excitable file to start the CSU batch system!


OPERATING INSTRUCTIONS:
  Once the excitable runs, it will open a command line interface.
  From this interface, you have a list of commands avaiable too you.
  you can type 'help' to see the full list of commands.
  The main command you will be running is the 'run' command.
  this command will execute a batch job in the following format.
  'run <job name> <execution time in sec> <Priority>'.
  once you are done with the program, please use the 'quit' command
