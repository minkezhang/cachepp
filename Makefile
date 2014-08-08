CC=g++
CFLAGS=-Wall -Werror -O3 -std=c++11 -g -Wl,--no-as-needed -ldl -rdynamic -fstack-protector-all

SUBDIRS=external/exceptionpp/

INCLUDE=-Iinclude/
INCLUDE_LIBS=-Iexternal/exceptionpp/include/ -Iinclude/libs/stacktrace/
SOURCES=src/*cc libs/*/*cc

OBJECTS=$(SOURCES:.cc=.o)

EXECUTABLE=cachepp.app

.PHONY: all clean

all: $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_LIBS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -f $(EXECUTABLE) *.o

