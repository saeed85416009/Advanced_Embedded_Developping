#include <my_process.h>

// shared data
static sem_t *demo_sem;
//

int main_simple_process(int argc, char *argv[]) {

	int pid;
	int status;
	pid = fork();
	if (pid == 0) {
		printf("I am the child, PID %d\n", getpid());
		sleep(10);
		exit(42);
	} else if (pid > 0) {
		printf("I am the parent, PID %d\n", getpid());
		wait(&status);
		printf("Child terminated, status %d\n", WEXITSTATUS(status));
	} else
		perror("fork:");
	return 0;
}

int main_simple_process_execution(int argc, char *argv[]) {

	char command_str[128];
	char arg_str_1[128];
	char arg_str_2[128];
	int pid;
	int child_status;
	int wait_for = 1;
	while (1) {
		printf("sh> ");
		scanf("%s", command_str);

		printf("arg1> ");
		scanf("%s", arg_str_1);

		printf("arg2> ");
		scanf("%s", arg_str_2);

		pid = fork();
		if (pid == 0) {
			/* child */
			printf("cmd '%s'\n", command_str);
			execl(command_str, command_str, arg_str_1, arg_str_2, (char*) NULL);
			/* We should not return from execl, so only get
			 to this line if it failed */
			perror("exec");
			exit(1);
		}
		if (wait_for) {
			waitpid(pid, &child_status, 0);
			printf("Done, status %d\n", child_status);
		}
	}
	return 0;
}

/*
 *
 * shared data process
 *
 *  */


/*
 * If the shared memory segment does not exist already, create it
 * Returns a pointer to the segment or NULL if there is an error
 */
static void* get_shared_memory(void) {
	int shm_fd;
	struct shared_data *shm_p;
	/* Attempt to create the shared memory segment */
	shm_fd = shm_open(SHM_SEGMENT_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (shm_fd > 0) {
		/* succeeded: expand it to the desired size (Note: dont't do
		 "this every time because ftruncate fills it with zeros) */
		printf("Creating shared memory and setting size=%d\n",
		SHM_SEGMENT_SIZE);
		if (ftruncate(shm_fd, SHM_SEGMENT_SIZE) < 0) {
			perror("ftruncate");
			exit(1);
		}
		/* Create a semaphore as well */
		demo_sem = sem_open(SEMA_NAME, O_RDWR | O_CREAT, 0666, 1);
		if (demo_sem == SEM_FAILED)
			perror("sem_open failed\n");
	} else if (shm_fd == -1 && errno == EEXIST) {
		/* Already exists: open again without O_CREAT */
		shm_fd = shm_open(SHM_SEGMENT_NAME, O_RDWR, 0);
		demo_sem = sem_open(SEMA_NAME, O_RDWR);
		if (demo_sem == SEM_FAILED)
			perror("sem_open failed\n");
	}
	if (shm_fd == -1) {
		perror("shm_open " SHM_SEGMENT_NAME);
		exit(1);
	}
	/* Map the shared memory */
	shm_p = mmap(NULL, SHM_SEGMENT_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_p == NULL) {
		perror("mmap");
		exit(1);
	}
	return shm_p;
}
int main_process_shared_data(int argc, char *argv[]) {
	char *shm_p;
	printf("%s PID=%d\n", argv[0], getpid());
	shm_p = get_shared_memory();
//	while (1) {
		printf("Press enter to see the current contents of shm\n");
		getchar();
		sem_wait(demo_sem);
		printf("%s\n", shm_p);
		/* Write our signature to the shared memory */
		sprintf(shm_p, "Hello from process %d\n", getpid());
		sem_post(demo_sem);
//	}
	return 0;
}

int main_process_shared_data_2(int argc, char *argv[]) {
	char *shm_p;
	printf("%s PID=%d\n", argv[0], getpid());
	shm_p = get_shared_memory();
//	while (1) {
		printf("2: Press enter to see the current contents of shm\n");
		getchar();
		sem_wait(demo_sem);
		printf("%s\n", shm_p);
		/* Write our signature to the shared memory */
		sprintf(shm_p, "2: Hello from process %d\n", getpid());
		sem_post(demo_sem);
//	}
	return 0;
}
