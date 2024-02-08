CC=g++
CFLAGS=-I.
LDLIBS=-lncurses

SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))

release: CFLAGS+=-O3
release: bin

debug: CFLAGS+=-Wall -g
debug: bin

clean:
	rm -f bin *.o

bin: $(OBJ)
	$(CC) $^ -o $@ $(LDLIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
