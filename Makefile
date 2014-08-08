CC=g++
CFLAGS=-Wall -Werror -O3 -std=c++11

SUBDIRS=external/exceptionpp/

INCLUDE=-Iinclude/
SOURCES=src/*cc

OBJECTS=$(SOURCES:.cc=.o)

EXECUTABLE=cachepp.app

.PHONY: all clean

all: $(EXECUTABLE) $(SOURCES)
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJECTS) -o $@ $(LIBS)

clean:
	for dir in $(SUBDIRS); do $(MAKE) clean -C $$dir; done
	rm -f $(EXECUTABLE) *.o

