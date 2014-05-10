#ifndef ADRESSRESOLVER_H
#define ADRESSRESOLVER_H

#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //for exit(0);
#include<sys/socket.h>
#include<errno.h> //For errno - the error number
#include<netdb.h> //hostent
#include<arpa/inet.h>

char * hostname_to_ip (char* hostname);

#endif
