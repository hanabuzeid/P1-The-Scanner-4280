CC = g++
CXXFLAGS = -std=c++11 - Wall
LDFLAGS =

# Makefile settings - Can be cutomized
APPNAME = Scanner
EXT = .cpp
SRCDIR = ./
OBJDIR = OBJDIR

#################
.DEFAULT_GOAL := Scanner
Scanner:
	g++ main.cpp Scanner.cpp  TestScanner.cpp  token.cpp -std=c++11
	mv a.out Scanner
clean:
	rm Scanner 