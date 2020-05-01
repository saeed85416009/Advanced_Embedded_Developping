#include "my_linkedList.h"

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

#include <stdint.h>
#include <strings.h>

int main_linkedList(int argc, char *argv[]){

	struct people_tag *head = NULL;
	struct people_tag *new;
	struct people_tag *list;

	char *name[] = {"Andy", "John", "Saeed", "\0"};
	char *last[] = {"BMW", "Bosch", "Pg","\0"};
	unsigned int age[]= {25,30,33};

	int i=0;

	while(strcmp(name[i],"\0")){
		new = (struct people_tag *)malloc(sizeof(new));
		if(new==NULL){
			fprintf(stderr, "unable to allocate memory. \n");
			exit(1);
		}
		strcpy(new->first_name,name[i]);
		strcpy(new->last_name,last[i]);
		new->age=age[i];
		new->next=head;
		head = new;
		i++;
	}
	list = head;

	while (list->next != NULL){

		printf("First name : %s \n", list->first_name);
		printf("last : %s \n", list->last_name);
		printf("age : %d \n", list->age);

		list = list->next;


	}
	list = head;

	while (list->next != NULL){
		head = list->next;
		free(list);
		list = head;
	}


return 0;
}
