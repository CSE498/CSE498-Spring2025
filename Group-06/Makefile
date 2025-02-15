# This file was created on February 6, 2025 by Ivan Bega
# The following resource has been used to generate Makefile: https://www.nicomedes.assistedcoding.eu/app/makefilegen/c
OBJS	= ArgManager/ArgManager.o CommandLine/CommandLine.o StringSet/StringSet.o ErrorManager/ErrorManager.o main.o
SOURCE	= ArgManager/ArgManager.cpp CommandLine/CommandLine.cpp StringSet/StringSet.cpp ErrorManager.cpp main.cpp
HEADER	= ArgManager/ArgManager.h Statis_String/StaticString.hpp StringSet/StringSet.h
OUT	= Lamport.exe
FLAGS	= -std=c++23 -g -c -Wall -Wextra
LFLAGS	= 
CC	= g++

all: clean	a.out

a.out: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

CommandLine/CommandLine.o: CommandLine/CommandLine.cpp
	$(CC) $(FLAGS) CommandLine/CommandLine.cpp -o CommandLine/CommandLine.o

StringSet/StringSet.o: StringSet/StringSet.cpp
	$(CC) $(FLAGS) StringSet/StringSet.cpp -o StringSet/StringSet.o

ErrorManager/ErrorManager.o: ErrorManager/ErrorManager.cpp
	$(CC) $(FLAGS) ErrorManager/ErrorManager.cpp -o ErrorManager/ErrorManager.o

ArgManager/ArgManager.o: ArgManager/ArgManager.cpp
	$(CC) $(FLAGS) ArgManager/ArgManager.cpp -o ArgManager/ArgManager.o

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f $(OBJS) $(OUT)