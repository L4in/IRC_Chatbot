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

%token NOM DEMANDE GREET DUMP HELP TIME LEAVE STOPDUMP
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
          | NOM DUMP DEMANDE
          | DEMANDE DUMP NOM
          ;

list_help : request HELP
          | HELP request
          | NOM HELP DEMANDE
          | DEMANDE HELP NOM
          ;

date_     : request TIME
          | TIME request
          | NOM TIME DEMANDE
          | DEMANDE TIME NOM
          ;

disconnect : request LEAVE
           | LEAVE request
           | NOM LEAVE DEMANDE
           | DEMANDE LEAVE NOM
           ;

stop_dump : NOM STOPDUMP
          | STOPDUMP NOM
          | request STOPDUMP
          ;


statment  : greetings   {reply_greetings();}
          | conv_dump   {netprint("The save is running...\n"); startDump();}
          | list_help   {printf("LIST_HELP\n\n"); list_help();}
          | date_       {char time[100]; getTime(time); char sentence[200]; sprintf(sentence, "My internal clock display %s\n", time); netprint(sentence);}
          | disconnect   {irc_disconnect();}
          | error NEWLINE {yyerrok;}
          | stop_dump   {endDump();}
          ;

%%
