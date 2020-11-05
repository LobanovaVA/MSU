CFLASGS = -c -Wall -Wextra -pedantic -Werror -O3 -g 
SHELL = /bin/sh

all: 1_1.out 1_2.out 1_3.out 1_4.out \
	 2_1.out 2_2.out 2_3.out \
	 3_1.out 3_2.out 3_3.out 3_4.out 3_5.out 3_6.out 3_7.out \
	 4_1.out 4_2.out 4_3.out 4_4.out

# Functions
func_series.o: func_series.c
	gcc $< $(CFLASGS) 
func_arrays.o: func_arrays.c
	gcc $< $(CFLASGS) 
func_sorts.o: func_sorts.c
	gcc $< $(CFLASGS) 
func_strings.o: func_strings.c
	gcc $< $(CFLASGS)
func_srt_matrix.o: func_srt_matrix.c
	gcc $< $(CFLASGS)

# Series
1_1.out: main1_1.o func_series.o
	gcc -g $^ -o $@
main1_1.o: main1_1.c
	gcc $< $(CFLASGS) 

1_2.out: main1_2.o func_series.o
	gcc -g $^ -o $@
main1_2.o: main1_2.c
	gcc $< $(CFLASGS) 

1_3.out: main1_3.o func_series.o
	gcc -g $^ -o $@
main1_3.o: main1_3.c
	gcc $< $(CFLASGS) 

1_4.out: main1_4.o func_series.o
	gcc -g $^ -o $@
main1_4.o: main1_4.c
	gcc $< $(CFLASGS) 


# Arrays
2_1.out: main2_1.o func_arrays.o 
	gcc -g $^ -o $@
main2_1.o: main2_1.c
	gcc $< $(CFLASGS) 

2_2.out: main2_2.o func_arrays.o 
	gcc -g $^ -o $@
main2_2.o: main2_2.c
	gcc $< $(CFLASGS) 

2_3.out: main2_3.o func_arrays.o 
	gcc -g $^ -o $@
main2_3.o: main2_3.c
	gcc $< $(CFLASGS) 

# Sorts
3_1.out: main3_1.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_1.o: main3_1.c
	gcc $< $(CFLASGS) 

3_2.out: main3_2.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_2.o: main3_2.c
	gcc $< $(CFLASGS) 

3_3.out: main3_3.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_3.o: main3_3.c
	gcc $< $(CFLASGS) 

3_4.out: main3_4.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_4.o: main3_4.c
	gcc $< $(CFLASGS) 

3_5.out: main3_5.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_5.o: main3_5.c
	gcc $< $(CFLASGS) 

3_6.out: main3_6.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_6.o: main3_6.c
	gcc $< $(CFLASGS)

3_7.out: main3_7.o func_sorts.o func_arrays.o
	gcc -g $^ -o $@
main3_7.o: main3_7.c
	gcc $< $(CFLASGS) 


# Strings
4_1.out: main4_1.o func_strings.o
	gcc -g $^ -o $@
main4_1.o: main4_1.c
	gcc $< $(CFLASGS) 

4_2.out: main4_2.o func_strings.o
	gcc -g $^ -o $@
main4_2.o: main4_2.c
	gcc $< $(CFLASGS) 

4_3.out: main4_3.o func_strings.o
	gcc -g $^ -o $@
main4_3.o: main4_3.c
	gcc $< $(CFLASGS) 

4_4.out: main4_4.o func_srt_matrix.o
	gcc -g $^ -o $@
main4_4.o: main4_4.c
	gcc $< $(CFLASGS) 


clean:
	rm -rf *.o *.out 