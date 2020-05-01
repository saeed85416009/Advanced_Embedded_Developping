
/*
 * this is just fo test
 * ignore this file
 */

#ifndef __TEST_H
#define __TEST_H







#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>
#include <errno.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/syscall.h>


#include <sys/ipc.h> //shared memory
#include <sys/shm.h> //shared memory

#include <time.h>   //time

#include <getopt.h>   //opt

#define SHM_SEGMENT_SIZE 65536       	//shared data
#define SHM_SEGMENT_NAME "/demo-shm"  	// shared data
#define SEMA_NAME "/demo-sem" 			// shared data

#define my_err_msg(msg) \
	do{perror(msg); }while(0)

#define my_success_msg(msg) \
	do{perror(msg); }while(0)

typedef enum option_t{
	none,
	help,
	step1,
	step2,
	wrong_option,
}op_t;

#define SHSIZE 100
//prototypes
int main_test_process_server(int argc, char *argv[]);
int main_test_process_client(int argc, char *argv[]);
int main_test_pipe(int argc, char *argv[]);
int main_test_time(int argc, char *argv[]);
int main_test_option(int argc, char *argv[]);
int main_test_memMap(int argc, char *argv[]);

#endif




