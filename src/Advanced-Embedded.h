#ifndef __ADVANCED_EMBEDDED_H
#define __ADVANCED_EMBEDDED_H
#include <stdio.h>
#include <stdint.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my_process.h"
#include "test.h"
#include "my_socket.h"
#include "my_linkedList.h"
#include "my_usb.h"
#include "my_database.h"

#define _GNU_SOURCE
#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE
#define POSIXLY_CORRECT


#define SIMPLE_PROCESS "simple_process"


//prototypes
void segmentationfault_handler(void);
void segfunc(int signal, siginfo_t *si, void*arg);



#endif



