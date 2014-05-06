#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int sockfd = 0;


//int yyparse();
int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead );

static int globalReadOffset;
//static const char *globalInputText = "3+4";

int main() {

    struct sockaddr_in serv_addr;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error, could not create socket.\n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6667);
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.22");

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
        //globalReadOffset = 0;
        yyparse();

    }
    return 0;
}

int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead ) {

    char* globalInputText;
    char wireBuff[1024];
    memset(wireBuff, '\0', sizeof(wireBuff));
    read(sockfd, wireBuff, sizeof(wireBuff));

    //printf("WireBuff contient %s\n", wireBuff);
    globalInputText = strdup(wireBuff);

    int numBytesToRead = maxBytesToRead;
    //printf("\tNombre de bytes à lire placé au maiximum, soit %d.\n", numBytesToRead);
    int bytesRemaining = strlen(globalInputText);//-globalReadOffset;
    //printf("Nombre de bytes restant à lire : %d\n", bytesRemaining);
    int i;
    if ( numBytesToRead > bytesRemaining ) { numBytesToRead = bytesRemaining; /*printf("On a plus de bytes à lire que de bytes restant, on place le nombre de bytes restant comme limite.\n");*/}
    for ( i = 0; i < numBytesToRead; i++ ) {
        buffer[i] = globalInputText[/*globalReadOffset+*/i];
        //printf("Byte %c placé en position %d du buffer.\n", globalInputText[/*globalReadOffset+*/i], i);
    }
    //printf("Et on sort de la boucle.\n");
    *numBytesRead = numBytesToRead;
    //printf("Si je ne m'affiche pas, le problème ne vient pas de là où je pense.\n");
//    globalReadOffset += numBytesToRead;
    //printf("Au final, j'ai dans mon buffer \"%s\", soit %d caractères sur les %d maximum.\n", buffer, *numBytesRead, maxBytesToRead);
    printf("%s", buffer);
    return 0;
}
