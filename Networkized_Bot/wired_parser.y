%{
#include <stdio.h>
#include "wired_main.h"
#define YYSTYPE char*

YYSTYPE yylval;

char* username;
extern void netprint(char* message);
extern int sockfd;
extern void yyerror(char* s);
extern int yylex();
extern int readInputForLexer(char* buffer,int *numBytesRead,int maxBytesToRead);
%}

%token NOM DEMANDE GREET DUMP HELP TIME INSULT
%token NEWLINE
%%

statments : statments statment
          | statment
          ;

request : NOM DEMANDE {printf("Request recieved.\n"); }
        | DEMANDE NOM {printf("Request recieved.\n"); }
        ;

greetings : GREET NOM
          | NOM GREET
          ;

conv_dump : request DUMP
          | DUMP request
          ;

list_help : request HELP
          | HELP request
          ;

date_     : request TIME
          | TIME request
          ;

insulted  : INSULT {printf("\t\tSockfd = %d\n\n", sockfd); send(sockfd, "PRIVMSG #test :Insult recieved.\n", sizeof("PRIVMSG #test :Insult recieved.\n")-1);}
          ;

statment  : greetings   {reply_greetings();}
          | conv_dump   {printf("\t\tSockfd = %d\n\n", sockfd); send(sockfd, "PRIVMSG #test :Dump request recieved.\n", sizeof("PRIVMSG #test :Dump request recieved.\n")-1); printf("DUMP\n");}
          | list_help   {send(sockfd, "PRIVMSG #test :Help request recieved.\n", sizeof("PRIVMSG #test :Help request recieved.\n")-1);}
          | date_       {send(sockfd, "PRIVMSG #test :Date request recieved.\n", sizeof("PRIVMSG #test :Date request recieved.\n")-1);}
          |insulted
          |error NEWLINE {yyerrok;}
          ;

%%
