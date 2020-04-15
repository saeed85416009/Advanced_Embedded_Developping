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

int main(int argc, char *argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */


//	if (argc != 4) {
//			printf("you have to enter at least four arguments......\n\n ");
//		}

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
	return 0;
}
