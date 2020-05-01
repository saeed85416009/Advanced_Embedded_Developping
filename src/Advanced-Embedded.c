/*
 ============================================================================
 Name        : Advanced-Embedded.c
 Author      : saeed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 * choice:
 * 1- simple_process
 */

#include "Advanced-Embedded.h"
uint32_t global_data_1=0;


int main(int argc, char *argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	char saeed[15], vahid[15];
	*saeed = (char *)"saeed";
	strcpy(saeed, vahid);

	segmentationfault_handler();
//	if (argc != 4) {
//			printf("you have to enter at least four arguments......\n\n ");
//			exit(1);
//		}
	main_database(argc, argv);
	if (strcmp(argv[1], "socket") == 0) {
				if (main_socket_client(argc, argv)) {
					printf("error in internal led program....\n\n");
					return -1;
				}
			}
	if (strcmp(argv[1], "socket") == 0) {
				if (main_linkedList(argc, argv)) {
					printf("error in internal led program....\n\n");
					return -1;
				}
			}
	if (strcmp(argv[1], "simple_process") == 0) {
		if (main_simple_process(argc, argv)) {
			printf("error in internal led program....\n\n");
			return -1;
		}
	}
	if (strcmp(argv[1], "process_execution") == 0) {
		if (main_simple_process_execution(argc, argv)) {
			printf("error in internal led program....\n\n");
			return -1;
		}
	}
	if (strcmp(argv[1], "process_shared") == 0) {
		if (main_process_shared_data_2(argc, argv)) {
			printf("error in internal led program....\n\n");
			return -1;
		}
		if (main_process_shared_data(argc, argv)) {
			printf("error in internal led program....\n\n");
			return -1;
		}
	}
	if (strcmp(argv[1], "thread_simple") == 0) {
			if (main_simple_thread(argc, argv)) {
				printf("error in internal led program....\n\n");
				return -1;
			}
		}
	if (strcmp(argv[1], "thread_advanced") == 0) {
			if (main_advanced_thread(argc, argv)) {
				printf("error in internal led program....\n\n");
				return -1;
			}
		}
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return 0;
}


void segmentationfault_handler(void){

	struct sigaction sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=SA_SIGINFO;
	sa.sa_sigaction=segfunc;

	sigaction(SIGSEGV, &sa, NULL);

}

void segfunc(int signal, siginfo_t *si, void*arg){
	my_err_msg("test: you are in the segmentation fault situation");
}
