#ifndef __SIMPLE_PROCESS_H
#define __SIMPLE_PROCESS_H





#define SHM_SEGMENT_SIZE 65536       	//shared data
#define SHM_SEGMENT_NAME "/demo-shm"  	// shared data
#define SEMA_NAME "/demo-sem" 			// shared data

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

typedef struct struct_output_thread{
	char *out_string;
	int out_int;

};
enum car_feature{
	color,
	model,
	price,
};
typedef enum color{
	red,
	green,
	black,
};
//prototypes
int main_simple_process(int argc, char *argv[]);
int main_simple_process_execution(int argc, char *argv[]);
static void* get_shared_memory(void);
int main_process_shared_data(int argc, char *argv[]);
int main_process_shared_data_2(int argc, char *argv[]);
static void* thread_fn(void *arg);
int main_simple_thread(int argc, char *argv[]);
void* my_func_th_1(void* arg);
void* my_func_th_2(void* arg);
int main_advanced_thread(int argc, char *argv[]);

//void* consumer(void *arg);
//void* producer(void *arg);

#endif
