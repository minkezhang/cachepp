CC=g++
CFLAGS=-Wall -Werror -O3 -std=c++11 -g -Wl,--no-as-needed -ldl -rdynamic -fstack-protector-all
INCLUDE=-Iinclude/
INCLUDE_LIBS=-Iexternal/exceptionpp/include/ -Iinclude/libs/stacktrace/ -Iexternal/cachepp/include/
LIBS=-pthread

SOURCES=src/*cc libs/*/*cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=tutorial.app

.PHONY: all clean

all: clean $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_LIBS) $(INCLUDE) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -f $(EXECUTABLE) *.o
