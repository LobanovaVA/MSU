LIBS  = -lm #-pthread -lpthread
GPROF = -pg
DEBUG = -g #$(GPROF)

CC = mpicxx -c
LD = mpicxx

CFLAGS	= $(DEBUG) -W -Wall -O3 -Wextra -pedantic #-Werror
LDFLAGS = $(DEBUG)


NAME = a.out
OBJS = addition.o size_arguments.o in_out.o solve.o main.o

all : $(NAME)

$(NAME) : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

%.o: %.cpp 
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(NAME)
