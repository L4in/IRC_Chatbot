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

int sockfd = 0;
extern char* username;
char* channel;
//int yyparse();
int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead );

static int globalReadOffset;
//static const char *globalInputText = "3+4";


int main() {

    srand(time(NULL));

    struct sockaddr_in serv_addr;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error, could not create socket.\n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6667);
    serv_addr.sin_addr.s_addr = inet_addr(/*hostname_to_ip("")*/"192.168.1.22"); //Cette ligne est problématique

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nError : Connect failed.\n");
        return 1;
    }

    write(sockfd, "NICK Lainbot\n", sizeof("NICK Lainbot\n")-1);
    write(sockfd, "USER Lainbot 8 x : Battlestar\n", sizeof("USER Lainbot 8 x : Battlestar\n")-1);
    write(sockfd, "JOIN #test\n", sizeof("JOIN #test\n")-1);

    while(1)
    {
        yyparse();

    }
    return 0;
}

int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead ) {

    char* globalInputText;
    char wireBuff[1024];
    memset(wireBuff, '\0', sizeof(wireBuff));
    read(sockfd, wireBuff, sizeof(wireBuff));

    globalInputText = strdup(wireBuff);

    int numBytesToRead = maxBytesToRead;
    int bytesRemaining = strlen(globalInputText);
    int i;
    if ( numBytesToRead > bytesRemaining ) { numBytesToRead = bytesRemaining; }
    for ( i = 0; i < numBytesToRead; i++ ) {
        buffer[i] = globalInputText[i];
    }
    *numBytesRead = numBytesToRead;
    printf("%s", buffer);
    return 0;
}

void netprint(char* in_mess)
{
    char message[200];
    sprintf(message, "PRIVMSG %s :%s\n", channel, in_mess);
    in_mess = strdup(message);
    write(sockfd, in_mess, strlen(in_mess));
}

void reply_greetings()
{
    char message[100];
    switch(rand() % 5)
    {
        case 0:
            sprintf(message, "Hello, %s! How are you doing?\n", username);
            break;

        case 1:
            sprintf(message, "%s : Hi.\n", username);
            break;

        case 2:
            sprintf(message, "%s : Greetings!\n", username);
            break;

        case 3:
            sprintf(message, "Ahoy, %s.\n", username);
            break;

        case 4:
            sprintf(message, "Welcome, %s.\n", username);
            break;
    }

    char* out = strdup(message);
    netprint(out);
}
