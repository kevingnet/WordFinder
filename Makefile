CC=g++
CFLAGS=-c -ggdb -Wall -I.
LDFLAGS=

SOURCES= compoundwords.cc 

OBJECTS=$(SOURCES:.cpp=.o)

WORD_FINDER=cw

all: $(SOURCES) $(WORD_FINDER) 
		
$(WORD_FINDER): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(WORD_FINDER)

