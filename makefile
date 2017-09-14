############ \
  File:   Makefile \
  Author: Islam Abdeen \
  mail: engehassan@gmail.com \
  Created on September 8, 2017, 1:30 AM \
  Description: This make file to configure and build all project \
  Note: To add run time debugging add -D DEBON to CPPFLAGS.(still working on it) \
		TO compile under Linux add -D UNIX (Windows by default).
############


CC = gcc

DB = test.db

CFLAGS = -g -std=c99 #-D UNIX

#CPPFLAGS = -D DEBON

#LDLIBS = 

LIBB = 

SRC = replace.c 

INC = replace.h 

OBJ = replace.o 

PROG = replace

$(PROG) : $(OBJ)
	$(CC) -o $(PROG) $(OBJ) $(LIBB) $(CFLAGS)

$(OBJ) : $(SRC) replace.h 
       #windows	rm $(PROG) $(OBJ) Linux
.PHONY : clean
clean:
	del *.o *.exe

.PHONY : install
install:
	#cp $(PROG) $(DB) ~/Desktop Linux
	

