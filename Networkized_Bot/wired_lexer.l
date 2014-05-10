%{

#include "y.tab.h"
#include <stdio.h>

extern int sockfd;
extern char* username;
extern char* channel;
extern YYSTYPE yylval;

//#undef YY_INPUT
#define YY_INPUT(b,r,s) readInputForLexer(b,&r,s)
%}

%s HEADER
%x MESSCONTENT PINGRES

%%
^PING {printf("PING READ, ATTEMPTING RESPONSE.\n\n"); BEGIN PINGRES;}

<PINGRES>:[a-zA-Z.]+ {char pong[100]; sprintf(pong, "PONG %s\n", yytext); write(sockfd, pong, strlen(pong)); BEGIN INITIAL;}

<MESSCONTENT>(Lain(bot)?|[bB][oO][tT][sS]*|[cC]hat[bB]ot[s]*|[iI]rc[bB]ot|[tT]oaster|Marvin)/[ ,?;.:/!()\t\n]*       {printf("Token NOM grepp'd.\n");
                        return NOM;}

<MESSCONTENT>([hH]ello|[gG]reetings|[hH]i|[sS]alutation|[yY]o|[yY]op|[hH]iya|[aA]hoy|[pP]lop|[dD]iglett|[Ww]elcome)/[ ,?;.:/!()\t\n]+      {printf("Token GREET grepp's, form %s.\n", yytext);
                        return GREET;}

<MESSCONTENT>([Hh]elp|[Cc]ommand|[Ll]ist)/[ ,?;.:/!\t\n()]+    {printf("HELP Token.\n"); return HELP;}

<MESSCONTENT>[sS]ave|[lL]oad|[mM]onitor(ing)?|[rR]egister|[cC]opy       {printf("Token DUMP grepp'd.\n");
                        return DUMP;}

<MESSCONTENT>([Ll]eave|[Qq]uit|[Dd]isconnect)/[ ,?;.:/!()\t\n]*        {printf("LEAVE token.\n"); return LEAVE;}

<MESSCONTENT>[cC]ould|[cC]an|[wW]ill|[wW]ould|[mM]ay|[sS]hould|[Nn]eed|[Ww]ant|[Gg]ive|[?]    {printf("Token DEMANDE grepp'd.\n");
                        return DEMANDE;}

<MESSCONTENT>[fF]uck|[cC]unt|[bB]rat|[jJ]erk|[fF]ag|[fF]aggot|[mM]oron|[wW]anker|[aA]rsehole|[aA]sshole|[fF]ucker|[sS]crubber|[sS]lag|[kK]nob|[wW]azzock|[tT]wit|[mM]inebag|[mM]aggot    {printf("Token INSULT grepp'd.\n");
                        return INSULT;}

^:                      {BEGIN HEADER;}

<HEADER>[a-zA-Z0-9]+/[!]   {username = strdup(yytext);
                                printf("Name %s GET\n", username);}

<HEADER>([#]+[a-zA-Z]+)/[ ]           {BEGIN MESSCONTENT;
                                        channel = strdup(yytext);
                                        }

\n                      {BEGIN INITIAL;}

<MESSCONTENT>\n         {BEGIN INITIAL;
                        return NEWLINE; }

<HEADER>.                       /*Nuthing*/;

<MESSCONTENT>.                  /*Nuthing too*/;

%%


void yyerror(char* s) {
}

int yywrap() {
    return -1;
}
