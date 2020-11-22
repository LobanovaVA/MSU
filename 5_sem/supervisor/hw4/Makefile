DEBUG	= -g
CC	= gcc -c
LD	= gcc
CFLAGS	= $(DEBUG) -W -Wall -Wextra -pedantic -Werror -O3
LIBS	= -lm
LDFLAGS = $(DEBUG)


HEADERS = addition.h
OBJS = func.o init.o matr_op.o


all: 1.out 2.out 3.out #4.out 5.out 6.out 7.out 8.out 9.out 10.out


# Functions
func.o: func.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

init.o: init.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

matr_op.o: matr_op.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@	


# Problems
1.out: main1.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main1.o: main1.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

2.out: main2.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main2.o: main2.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

3.out: main3.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main3.o: main3.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

4.out: main4.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main4.o: main4.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

5.out: main5.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main5.o: main5.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

6.out: main6.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main6.o: main6.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

7.out: main7.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main7.o: main7.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

8.out: main8.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main8.o: main8.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

9.out: main9.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main9.o: main9.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

10.out: main10.o $(OBJS)
	$(LD) $(LDFLAGS) $^ $(LIBS) -o $@
main10.o: main10.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@


clean:
	rm -f *.o *.out 