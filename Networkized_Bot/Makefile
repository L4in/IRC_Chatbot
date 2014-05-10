# Networkized_Bot/Makefile
#.SUFFIXES:
#.PHONY:

#
CC 		= 	gcc
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

# Source and object files list
#SRC		=	$(addprefix $(SRCBDIR), $(CHOICE).cpp) $(addprefix $(SRCLDIR), libImageManip.cpp) $(addprefix $(SRCLDIR), grayScale.cpp) $(addprefix $(SRCLDIR), sobelFilter.cpp) $(addprefix $(SRCLDIR), interestPoint.cpp) $(addprefix $(SRCLDIR), harrisMap.cpp)
#OBJB		=	$(patsubst $(SRCBDIR)$(CHOICE).cpp,$(OBJDIR)$(CHOICE).o,$(SRC))
#OBJL		=	$(patsubst $(SRCLDIR)%.cpp,$(OBJDIR)%.o,$(SRC))



# All 
all: clean $(BINDIR)$(OUTPUT)
#all: clean $(OBJDIR)$(OBJ) 
#all: clean chatbot

ifeq ($(DEBUG),yes)
	@echo "Debug compilation"
else
	@echo "Release compilation"
endif


$(BINDIR)$(OUTPUT): wired_main.o adressresolver.o y.tab.o lex.yy.o 
	$(CC) wired_main.o y.tab.o lex.yy.o adressresolver.o -o chatbot

wired_main.o:  wired_main.c adressresolver.h
	$(CC) -c wired_main.c -o wired_main.o 

adressresolver.o: adressresolver.c adressresolver.h
	$(CC) -c adressresolver.c -o adressresolver.o

y.tab.o: y.tab.c
	$(CC) -c y.tab.c -o y.tab.o

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c -o lex.yy.o

y.tab.c: wired_parser.y 
	yacc -d wired_parser.y

lex.yy.c: wired_lexer.l
	lex wired_lexer.l




 
clean:
	rm -rf *.o





