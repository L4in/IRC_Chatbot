#ifndef WIRED_MAIN_H
#define WIRED_MAIN_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "adressresolver.h"

int main();

int readInputForLexer(char* buffer, int *numBytesRead, int maxButesToRead);

void netprint(char* message);

void reply_greetings();

void irc_disconnect();

void list_help();

void startDump();

void sopDump();

#endif
