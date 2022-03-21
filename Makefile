# Build config vars
CC=g++
CFLAGS=-Wall -std=c++17

all: bin/search

# `make debug` builds the executable with debug flags
debug: CFLAGS += -g
debug: bin/search

# Build objects
obj/document.o: src/document.cpp include/document.h
	$(CC) -c $(CFLAGS) src/document.cpp -o obj/document.o

obj/index.o: src/index.cpp include/index.h
	$(CC) -c $(CFLAGS) src/index.cpp -o obj/index.o

obj/main.o: src/main.cpp include/index.h include/document.h
	$(CC) -c $(CFLAGS) src/main.cpp -o obj/main.o

# Build binary rule
bin/search: obj/document.o obj/index.o obj/main.o
	$(CC) $(CFLAGS) obj/document.o obj/index.o obj/main.o -o bin/search

# .PHONY tells Make to not watch for any changes to a file named 'clean'
.PHONY: clean
clean:
	rm -f obj/*.o bin/search