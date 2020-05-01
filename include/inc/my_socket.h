
#ifndef MY_SOCKET_H
#define MY_SOCKET_H


//prototypes
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

#include <sys/socket.h> //socket
#include <netinet/in.h> //socket
#include <netdb.h>  //socket

#define PORT_ADDR 					5000
#define PORT_ADDR_CLIENT 					5000

#define NUMBER_OF_CONNECTION_LISTEN 5
#define SEND_DATA  "Hello I am Saeed"
// prototypes
int main_socket_server(int argc, char *argv[]);
int main_socket_client(int argc, char *argv[]);


#endif




