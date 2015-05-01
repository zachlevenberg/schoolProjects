#------------------------------------------------------------------------------
# makefile for alphaNum.c with Macros
#------------------------------------------------------------------------------

FLAGS = -std=c99 -Wall
SOURCES = alphaNum.c
OBJECTS = alphaNum.o
EXEBIN = alphaNum

all: $(EXEBIN)

$(EXEBIN) : $(OBJECTS)
	gcc -o $(EXEBIN) $(OBJECTS)

$(OBJECTS) : $(SOURCES)
	gcc -c $(FLAGS) $(SOURCES)

clean :
	rm $(EXEBIN) $(OBJECTS)

