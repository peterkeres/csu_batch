struct job{
	int priority;
	int timeToComplete;
	int arrivalTime;
	char* jobName;
	int turnAround;
};

struct jobQ{
	int first, last, size, numJobs;
	struct job* jobs;
};
struct jobQ* buildJobQ(int capacity);
int isFull(struct jobQ* jobQ);
int isEmpty(struct jobQ* jobQ);
void addJob(struct jobQ* jobQ, struct job job);
struct job removeJob(struct jobQ* jobQ);
void printQ(struct jobQ* jobQ);
