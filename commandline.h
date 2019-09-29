/*
 * peter keres
 * sep 28 2019
 *
 * this is the header file for the commandline file
*/

// we check if commadn line as already been defined
#ifndef  COMMANDLINE_H
#define  COMMANDLINE_H

// runs a command
int cmd_run(int nargs, char **args, struct jobQ* jobQueue);

// quits the CSU Batch
int cmd_quit(int nargs, char **args, struct jobQ* jobQueue);

// shows a menu sent
void showmenu(const char *name, const char *x[]);

// creates the help menu
int cmd_helpmenu(int n, char **a, struct jobQ* jobQueue);

// allows user to swtich the current policy
int cmd_schedule_policy(int narg, char** args, struct jobQ* jobQueue);

// display the list of current batch process in the system
int cmd_list(int narg, char** args, struct jobQ* jobQueue);

// runs automate peforemace evaluatoin of a job
int cmd_test(int narg, char** args, struct jobQ* jobQueue);

// this is the main method called to get a UI
int cmd_dispatch(char *cmd, struct jobQ* jobQueue);


#endif
