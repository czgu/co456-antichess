#
OS := $(shell uname)
LINUXCC=g++
MACCC=clang++
# 
LINUXFLAGS=-pthread
MACFLAGS=-stdlib=libc++
SHAREDFLAGS= -Wall -std=c++11 -Wno-c++11-extensions

FILES=main board search player
SOURCES=$(FILES:=.cpp)
OBJECTS=$(FILES:=.o)
EXECUTABLES=chess


ifeq ($(OS),Darwin)
	CC=$(MACCC)
	FLAGS=$(MACFLAGS)
else
	CC=$(LINUXCC)
	FLAGS=$(LINUXFLAGS)
endif

all: $(SOURCES) $(EXECUTABLES)

%.o:%.cpp
	$(CC) $(FLAGS) $(SHAREDFLAGS) -c $< -o $@

$(EXECUTABLES): $(OBJECTS)
	$(CC) $(OBJECTS) $(FLAGS) $(SHAREDFLAGS) -o $(EXECUTABLES)


clean:
	rm -rf *o chess

.PHONY:
	clean
