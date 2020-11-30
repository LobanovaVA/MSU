LIBS  = -lm
GPROF = -pg
DEBUG = -g #$(GPROF)

CC = g++ -c
LD = g++

CFLAGS	= $(DEBUG) -W -Wall -Wextra -pedantic -Werror -O3
LDFLAGS = $(DEBUG)


all: a.out clean_obj

a.out: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@ 

%.o: %.cpp
	$(CC) $(CFLAGS) -MD $<

include $(wildcard *.d)


clean_obj:
	rm -f *.o *.d
	
clean: clean_obj
	rm -f *.out 

