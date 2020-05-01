#include "my_database.h"

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

#define my_err_close_msg(msg) \
	do{perror(msg); return 1;}while(0)

#define my_success_close_msg(msg) \
	do{perror(msg); return 1;}while(0)

#define my_err_msg(msg) \
	do{perror(msg);}while(0)

#define my_success_msg(msg) \
	do{perror(msg);}while(0)



typedef struct{
	int key;
	char fname[15];
	char lname[15];
	int age;
}person_rec;

static int open_record(char *filename){
	int fd;

	if((fd=open(filename, O_CREAT | O_RDWR | O_APPEND, 0644)) == -1){
		fprintf(stderr,"db: open fd error function:%s - line: %d \n", __func__, __LINE__);
	}
	return fd;
}

static int close_record(int fd){
	close(fd);
	return 0;
}

static int insert_record(int fd, person_rec *rec){
	int ret;
	ret = write(fd, rec, sizeof(person_rec));
	return ret;
}

static person_rec* get_record(int fd, person_rec *rec, int key){
	int ret;
	while((ret=read(fd,rec,sizeof(person_rec))) != -1){
		if(ret == 0){
			printf("db: nothing to read anymore !!! \n");
			return 0;
		}else if ((rec->key) == key){
			printf("db: find the key !!! \n");
			return rec;
		}
	}
	return rec;
}

static person_rec* delete_record(int fd, int key ){
	int ret;
	person_rec *rec;
	off_t pos;
	// change the position to the first of file e
	pos = lseek(fd, 0, SEEK_SET);

	while((ret=read(fd,rec,sizeof(person_rec))) != -1){
			if(ret == 0){
				printf("db: nothing to read anymore !!! \n");
				//before exiting, we should get back the position);
							lseek(fd, pos, SEEK_SET);
				return 0;
			}else if ((rec->key) == key){
				//before exiting, we should get back the position);
							lseek(fd, pos, SEEK_SET);
				printf("db: find the key !!! \n");
				rec->key=0;
				return rec;
			}
		}

	lseek(fd, pos, SEEK_CUR);
		return rec;


}


int main_database(int argc, char *argv[]) {

	int fd;
	person_rec rec;
	fd = open_record("db");

	if (argc>5 && !strcmp(argv[1],"insert")){

		/* insert data */
		rec.key=atoi(argv[2]);
		printf("arg 2 %d \n", atoi(argv[2]));
		strcpy(rec.fname,argv[3]);
		printf("arg 3 %s \n", argv[3]);
     	strcpy(rec.lname,argv[4]);
     	printf("arg 4 %s \n", argv[4]);
		rec.age=atoi(argv[5]);
		printf("arg 5 %d \n", atoi(argv[5]));
		insert_record(fd,&rec);

	}




	/* delete */

	if (argc>2 && !strcmp(argv[1],"delete"))
		delete_record(fd,atoi(argv[2]));

	if (argc>2 && !strcmp(argv[1],"print")){
		get_record(fd,&rec,atoi(argv[2]));

		printf("key = %d \n",rec.key);
		printf("first = %s \n",rec.fname);
		printf("last = %s \n",rec.lname);
		printf("age = %d \n",rec.age);
	}


	/* print */

	if (argc > 2 && !strcmp(argv[1], "print")){
		get_record(fd, &rec, atoi(argv[2]));

		printf("key = %d \n", rec.key);
		printf("first name = %s \n", rec.fname);
		printf("last name = %s \n", rec.lname);
		printf("age = %d \n", rec.age);
	}



	close_record(fd);
	return 0;
}










