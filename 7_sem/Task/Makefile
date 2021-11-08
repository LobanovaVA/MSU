LIBS  = -lm
GPROF = -pg
DEBUG = -g #$(GPROF)

CC = g++ -c
LD = g++

CFLAGS	= $(DEBUG) -W -Wall -O3 -Wextra -pedantic #-Werror
LDFLAGS = $(DEBUG)


NAME = a.out
OBJS = main.o func_base.o func_coefs.o scheme_builder.o scheme_solver.o \
       residual.o in_out.o unit_tests.o 
       
all : $(NAME)

$(NAME) : $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(NAME)
