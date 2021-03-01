LIBS  = -lm #-pthread -lpthread
GPROF = -pg
DEBUG = -g #$(GPROF)

CC = mpicxx -c
LD = mpicxx

CFLAGS	= $(DEBUG) #-W -Wall -Wextra -pedantic -Werror -O3
LDFLAGS = $(DEBUG)


NAME = a.out
#OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJS = addition.o size_arguments.o in_out.o block_action.o main.o

all : $(NAME)

$(NAME) : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

%.o: %.cpp addition.h
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(NAME)
