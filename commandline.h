

#ifndef  COMMANDLINE_H
#define  COMMANDLINE_H

int cmd_run(int nargs, char **args, struct jobQ* jobQueue);

int cmd_quit(int nargs, char **args, struct jobQ* jobQueue);

void showmenu(const char *name, const char *x[]);

int cmd_helpmenu(int n, char **a, struct jobQ* jobQueue);

int cmd_schedule_policy(int narg, char** args, struct jobQ* jobQueue);

int cmd_list(int narg, char** args, struct jobQ* jobQueue);

int cmd_test(int narg, char** args, struct jobQ* jobQueue);

int cmd_dispatch(char *cmd, struct jobQ* jobQueue);


#endif
