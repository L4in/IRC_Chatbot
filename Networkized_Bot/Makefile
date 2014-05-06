all: chatbot

chatbot: wired_parser.o y.tab.o lex.yy.o adressresolver.o
	gcc wired_parser.o y.tab.o lex.yy.o adressresolver.o -o chatbot

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: wired_lexer.l y.tab.h
	lex wired_lexer

y.tab.c y.tab.h: wired_parser.y 
	yacc -d wired_parser.y

adressresolver.o: adressresolver.c adressresolver.h
	gcc -c adressresolver.c

wired_parser.o:  wired_parser.c adressresolver.h
	gcc -c wired_parser.c

clean:
	rm *.o && rm chatbot
