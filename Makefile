# Build config vars
CC=g++
CFLAGS=-Wall -std=c++17

all: directories build/search

directories: build

build:
	mkdir -p build

# .PHONY tells Make to not watch for any changes to a file named 'clean'
.PHONY: clean create_build_dir
clean:
	rm -f build/*

# `make debug` builds the executable with debug flags
debug: CFLAGS += -g
debug: all

# Build buildects
build/document.o: src/document.cpp include/document.h
	$(CC) -c $(CFLAGS) src/document.cpp -o build/document.o

build/index.o: src/index.cpp include/index.h
	$(CC) -c $(CFLAGS) src/index.cpp -o build/index.o

build/main.o: src/main.cpp include/index.h include/document.h
	$(CC) -c $(CFLAGS) src/main.cpp -o build/main.o

# Build buildary rule
build/search: build/document.o build/index.o build/main.o
	$(CC) $(CFLAGS) build/document.o build/index.o build/main.o -o build/search
