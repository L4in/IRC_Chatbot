all: chatbot

chatbot: wired_main.o y.tab.o lex.yy.o adressresolver.o
	gcc wired_main.o y.tab.o lex.yy.o adressresolver.o -o chatbot

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: wired_lexer.l y.tab.h
	lex wired_lexer.l

y.tab.c y.tab.h: wired_parser.y wired_main.h 
	yacc -d wired_parser.y

adressresolver.o: adressresolver.c adressresolver.h
	gcc -c adressresolver.c

wired_main.o:  wired_main.c adressresolver.h wired_main.h
	gcc -c wired_main.c

clean:
	rm *.o
