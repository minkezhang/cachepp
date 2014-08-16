CC=g++
CFLAGS=-Wall -Werror -O3 -std=c++11 -g -Wl,--no-as-needed -ldl -rdynamic -fstack-protector-all

SUBDIRS=external/exceptionpp/

INCLUDE=-Iinclude/
INCLUDE_LIBS=-Iexternal/catch/include/ -Iexternal/exceptionpp/include/ -Iinclude/libs/stacktrace/
SOURCES=src/*cc libs/*/*cc tests/*cc

LIBS=-pthread

OBJECTS=$(SOURCES:.cc=.o)

EXECUTABLE=cachepp.app

.PHONY: all clean test

all: $(EXECUTABLE) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_LIBS) $(INCLUDE) $(OBJECTS) -o $@ $(LIBS)

test: clean all
	# set ulimit -c unlimited to get a core dump and analyze via gdb
	#	cf. http://bit.ly/1zlOj8u, http://bit.ly/1n2ONGD, http://bit.ly/1n2ONGD, http://bit.ly/VCQ0yM
	ulimit -c unlimited && ./$(EXECUTABLE) | tee results.log

clean:
	rm -f $(EXECUTABLE) *.o *.log core
