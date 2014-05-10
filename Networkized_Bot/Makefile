# Networkized_Bot/Makefile
#.SUFFIXES:
#.PHONY:

#
CC 		= 	gcc
YACC		=	yacc
LEX		=	lex
DEBUG 		= 	yes
#OBJ 		=	wired_main.o adressresolver.o lex.yy.o	
OUTPUT		=	networkizedChatbot

# Choice debug or release mode
ifeq ($(DEBUG),yes)
        CFLAGS 	= 	-g -W -Wall
else
        CFLAGS 	=	-W
endif

# Path list
CURDIR		=	./
BINDIR		=	bin/
INCDIR		=	inc/
SRCDIR		=	src/
OBJDIR		=	obj/

# All 
all: $(BINDIR)$(OUTPUT)
#all: clean $(OBJDIR)$(OBJ) 
#all: clean chatbot

ifeq ($(DEBUG),yes)
	@echo "Debug compilation"
else
	@echo "Release compilation"
endif


$(BINDIR)$(OUTPUT): $(OBJDIR)wired_main.o $(OBJDIR)adressresolver.o $(OBJDIR)y.tab.o $(OBJDIR)lex.yy.o 
	$(CC) $(OBJDIR)wired_main.o $(OBJDIR)y.tab.o $(OBJDIR)lex.yy.o $(OBJDIR)adressresolver.o -o $(BINDIR)$(OUTPUT)

$(OBJDIR)wired_main.o: $(SRCDIR)wired_main.c $(INCDIR)adressresolver.h $(INCDIR)wired_main.h
	$(CC) -c $(SRCDIR)wired_main.c -o $(OBJDIR)wired_main.o 

$(OBJDIR)y.tab.o: $(SRCDIR)y.tab.c
	$(CC) -c $(SRCDIR)y.tab.c -o $(OBJDIR)y.tab.o

$(OBJDIR)lex.yy.o: $(SRCDIR)lex.yy.c
	$(CC) -c $(SRCDIR)lex.yy.c -o $(OBJDIR)lex.yy.o

$(SRCDIR)lex.yy.c: $(SRCDIR)wired_lexer.l
	$(LEX) $(SRCDIR)wired_lexer.l

$(SRCDIR)y.tab.c $(INCDIR)y.tab.h : $(SRCDIR)wired_parser.y $(INCDIR)wired_main.h 
	$(YACC) -d $(SRCDIR)wired_parser.y

$(OBJDIR)adressresolver.o: $(SRCDIR)adressresolver.c $(INCDIR)adressresolver.h
	$(CC) -c $(SRCDIR)adressresolver.c -o $(OBJDIR)adressresolver.o

clean:
	rm -rf *.o
