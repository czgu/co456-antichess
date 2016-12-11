#
OS := $(shell uname)
LINUXCC=g++
MACCC=clang++
# 
LINUXFLAGS=-Wall -std=c++11 -pthread
MACFLAGS=-Wall -std=c++11 -stdlib=libc++

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

%.o:%.cc
	$(CC) $(FLAGS) -c $< -o $@

$(EXECUTABLES): $(OBJECTS)
	$(CC) $(OBJECTS) $(FLAGS) -o $(EXECUTABLES)


clean:
	rm -rf *o chess

.PHONY:
	clean
