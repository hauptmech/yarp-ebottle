CC=g++
CXXFLAGS=-c -Wall -g -ggdb
LDFLAGS= /usr/local/lib/libYARP_OS.a -lACE
SOURCES=main.cc eBottle.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=eBottleTest

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CXXFLAGS) $< -o $@
	
clean :
	-rm $(EXECUTABLE)
	-rm *.o