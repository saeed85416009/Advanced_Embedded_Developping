/*
 * this is just fo test
 * ignore this file
 */

#include "test.h"

int main_test_process_server(int argc, char *argv[]) {

	int shmid;

	key_t key;
	char *shm;
	char *s;

	key = 9876;
	/*creating shared memory
	 * shmget (produce specific mem id -->
	 * shmat use allocated id and create a share memory space
	 * */
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("my shm: sh get ..\n");
		return 1;
	}
	shm = shmat(shmid, NULL, 0);
	if (shm == (char*) -1) {
		perror("my shm: shmat ..\n");
		return 1;
	}
	// we want to write sth into the shared memory:
	memcpy(shm, "Hello world", 11);

	// we now want to put the value 0 to the end of the address of shm by shifting 11 places
	// and then put 0 at the end point
	s = shm;
	s += 11;
	*s = 0;

	while (*shm != '*')
		sleep(1);

	return 0;
}

int main_test_process_client(int argc, char *argv[]) {

	int shmid;

	key_t key;
	char *shm;
	char *s;

	key = 9876;
	/*creating shared memory
	 * shmget (produce specific mem id -->
	 * shmat use allocated id and create a share memory space
	 * */
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("my shm: sh get ..\n");
		return 1;
	}
	shm = shmat(shmid, NULL, 0);
	if (shm == (char*) -1) {
		perror("my shm: shmat ..\n");
		return 1;
	}
	// we use the shared memory, written in the server:
	// start from the base address of shm; then increase by one point
	// and ends in the last point which is "0" as written in server
	for (s = shm; *s != 0; s++) {
		printf("client character = %c", *s);

	}

	// we now want to put the value 0 to the end of the address of shm by shifting 11 places
	// and then put 0 at the end point
	s = shm;
	s += 11;
	*s = 0;

	while (*shm != '*')
		sleep(1);

	return 0;
}

int main_test_pipe(int argc, char *argv[]) {

	pid_t pid;
	/*
	 * mypipefd[1] -->  writing
	 * mypipefd[0] -->  reading
	 * */
	int mypipefd[2];
	int ret;
	char buf[20];

	ret = pipe(mypipefd);
	if (ret == -1) {
		perror("my pipe: creating pipe error ..\n");
		return 1;;
	}

	pid = fork();

	if (pid == 0) {
		/* child process */
		close(mypipefd[0]);
		printf("child 1....\n");
		write(mypipefd[1], argv[1], 12);
		printf("child 2....\n");

	} else {
		/* parent process */
		sleep(1);
		close(mypipefd[1]);
		printf("parent ....\n");
		read(mypipefd[0], buf, 12);
		printf("buf: %s \n", buf);
		printf("buf: %d - %d \n", sizeof(*argv[1]), sizeof(char));
		return 0;;
	}
	return 0;

}

int main_test_time(int argc, char *argv[]) {
	time_t mytime;
	struct tm *mytm;

	mytime = time(NULL);
	mytm = localtime(&mytime);
	printf("year:%d \t month:%d \t day:%d \t hour:%d \t minutes: %d\n\n",
			1900 + mytm->tm_year, mytm->tm_mon, mytm->tm_mday, mytm->tm_hour,
			mytm->tm_min);
	return 0;
}

int main_test_option(int argc, char *argv[]) {

	int flags, opt;

	flags = none;
	while ((opt = getopt(argc, argv, "ha:b:")) != -1) {
		switch (opt) {
		case 'h':
			printf("you have requested help \n\n");
			flags = help;
			break;
		case 'a':
			printf("step 1 = %d \n\n", atoi(optarg));
			flags = step1;
			break;
		case 'b':
			printf("step 2 = %d \n\n", atoi(optarg));
			flags = step2;
			break;
		case '?':
			if ((optopt == 'a') || (optopt == 'b')) {
				fprintf(stderr, "option -%c needs argument", optopt);
			} else {
				fprintf(stderr, "unknown -%c option", optopt);
			}
			break;
		default:
			fprintf(stderr, "get option \n");
			return 1;;
		}
	}

	printf("flags=%d\n", flags);

	return 0;

}

int main_test_memMap(int argc, char *argv[]) {
	char *addr;
	int fd;
	struct stat sb;
	off_t offset, pa_offset;
	size_t length;
	ssize_t s;

	if (argc < 3 || argc > 4) {
		fprintf(stderr, "%s file offset [length]\n", argv[0]);
		return 1;;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		my_err_msg("open");

	if (fstat(fd, &sb) == -1) /* To obtain file size */
		my_err_msg("fstat");

	// this is the way if we want to allocate offset in mmap function with allocating memory
	offset = atoi(argv[2]);
	pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
	/* offset for mmap() must be page aligned */

	if (offset >= sb.st_size) {
		fprintf(stderr, "offset is past end of file\n");
		return 1;;
	}

	if (argc == 4) {
		length = atoi(argv[3]);
		if (offset + length > sb.st_size)
			length = sb.st_size - offset;
		/* Can't display bytes past end of file */

	} else { /* No length arg ==> display to end of file */
		length = sb.st_size - offset;
	}

	addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd,
			pa_offset);
	if (addr == MAP_FAILED)
		my_err_msg("mmap");

	s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
	if (s != length) {
		if (s == -1)
			my_err_msg("write");

		fprintf(stderr, "partial write");
		return 1;;
	}

	//remove allocated memory
	munmap(addr, length + offset - pa_offset);
	close(fd);

	my_success_msg("\n end of the program - success - \n");
	return 0;
}

int main_test_lseek(int argc, char *argv[]) {

	int fd, repo;
	char *name[5] = {"saeed \n", "vahidiiiiiiiiiii \n", "naviiiiiiiiiid \n"};
	char *buf, *stack_buf;
	//char *name = "saeed";
	fd = open("lssek_test",O_CREAT | O_WRONLY);
	if(fd<0)
		fprintf(stderr,"lseek error open");
for (int i=0;i<3;i++){
	if(write(fd, name[i],strlen(name[i]))<0)
		fprintf(stderr,"lseek error write");
}
//buf =  malloc(150);
if(read(fd, stack_buf,5)<0)
	fprintf(stderr,"\n error - read - \n");

repo = (strlen(name[0])+ strlen(name[1]));

if(lseek(fd,repo,SEEK_SET)<0)
	fprintf(stderr,"lseek error open");


if(read(fd,(void*) buf,5)<0)
	fprintf(stderr,"\n error - read - \n");

fprintf(stdout,"data is %s \n", *buf);

//free(buf);
close(fd);



		return 0;
}



