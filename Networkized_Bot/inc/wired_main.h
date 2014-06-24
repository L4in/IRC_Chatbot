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
#include <pthread.h>
#include "adressresolver.h"

int main();

int readInputForLexer(char* buffer, int *numBytesRead, int maxButesToRead);

void netprint(char* message);

void reply_greetings();

void irc_disconnect();

void list_help();

void startDump();

void endDump();

void *paused_unban(void * banned_user);

void empty_barrel();

void load_russian_roulette();

void weapon_swap(int desired_number);

void roll_barrel();

void fire_russian_roulette();

#endif
