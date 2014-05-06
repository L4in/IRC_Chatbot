%{

#include<stdio.h>

#define YYSTYPE char*

YYSTYPE yylval;

char* username ;
%}

%token NOM DEMANDE GREET DUMP HELP TIME INSULT

%%

statments : statments statment
          | statment
          ;

request : NOM DEMANDE   {printf("Request recieved.\n");}
        | DEMANDE NOM   {printf("Request recieved.\n");}
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

date_ : request TIME
      | TIME request
      ;

insulted : INSULT   {printf("DAT IS NOT GOOD LANGUAGE, %s.\n", username);}
         ;

statment    : greetings      {printf("Hello, %s. How are you?\n", username);}
            | conv_dump      {printf("Dump request recieved.\n");}
            | list_help      {printf("Help request recieved.\n");}
            | date_          {printf("Date request recieved.\n");}
            | insulted
            ;

%%

FILE *yyin;

yyerror(s)
char *s;
{
}

main()
{
    printf("NICK Lainbot\nUSER Lainbot 8 x : Battlestar\nJOIN #test");
    do
    {
    yyparse();
    }
    while (!feof(yyin));
}
