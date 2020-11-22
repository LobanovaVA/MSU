DEBUG	= -g
CC	= gcc -c
LD	= gcc
CFLAGS	= $(DEBUG) -W -Wall -Wextra -pedantic -Werror -O3
LIBS	= -lm
LDFLAGS = $(DEBUG)

HEADERS = all_func.h
OBJS_1 = func_interpolation.c
OBJS_2 = func_equations.o f.o
OBJS_3 = func_integrals.o f.o

all: 1_1.out 1_2.out 1_3.out \
	 2_1.out 2_2.out 2_3.out 2_4.out 2_5.out 2_6.out 2_7.out 2_8.out 2_9.out 2_10.out \
	 3_1.out 3_2.out 3_3.out 3_4.out 3_5.out 3_6.out 3_7.out 3_8.out 3_9.out

# Functions
func_interpolation.o: func_interpolation.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

func_equations.o: func_equations.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

func_integrals.o: func_integrals.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

f.o: f.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@


# Interpolation
1_1.out: main_1_1.o $(OBJS_1)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_1_1.o: main_1_1.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

1_2.out: main_1_2.o $(OBJS_1)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_1_2.o: main_1_2.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

1_3.out: main_1_3.o $(OBJS_1)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_1_3.o: main_1_3.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@


# Equations
2_1.out: main_2_1.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_1.o: main_2_1.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_2.out: main_2_2.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_2.o: main_2_2.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_3.out: main_2_3.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_3.o: main_2_3.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_4.out: main_2_4.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_4.o: main_2_4.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_5.out: main_2_5.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_5.o: main_2_5.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_6.out: main_2_6.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_6.o: main_2_6.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_7.out: main_2_7.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_7.o: main_2_7.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_8.out: main_2_8.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_8.o: main_2_8.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_9.out: main_2_9.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_9.o: main_2_9.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2_10.out: main_2_10.o $(OBJS_2)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_2_10.o: main_2_10.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@


# Integrals
3_1.out: main_3_1.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_1.o: main_3_1.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_2.out: main_3_2.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_2.o: main_3_2.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_3.out: main_3_3.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_3.o: main_3_3.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_4.out: main_3_4.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_4.o: main_3_4.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_5.out: main_3_5.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_5.o: main_3_5.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_6.out: main_3_6.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_6.o: main_3_6.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_7.out: main_3_7.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_7.o: main_3_7.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_8.out: main_3_8.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_8.o: main_3_8.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3_9.out: main_3_9.o $(OBJS_3)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main_3_9.o: main_3_9.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.out 