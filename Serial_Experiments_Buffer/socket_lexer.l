%{
#include<string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#undef YY_INPUT
#define YY_INPUT(buffer,result,max_size) readInputForLexer(buffer,result,max_size)

%}


%%

.|\n    printf("JE N'AFFICHE PLUS RIEN.\n");;

%%

int yywrap()
{
    return -1;
}
