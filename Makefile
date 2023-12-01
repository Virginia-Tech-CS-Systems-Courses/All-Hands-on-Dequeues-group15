#---------------------------------------------------------------------------
#       Makefile for the Queue Function Library
#---------------------------------------------------------------------------
AR      =ar
ARFLAGS =-r

CC      =gcc
#CCFLAGS =-Wall -g -std=c11
#CCFLAGS =-Wall -g -std=c99
#CCFLAGS =-Wall -g -std=c90
#CCFLAGS =-Wall -g -ansi -Wpedantic
CCFLAGS = -O3 -Wall -g -lpthread -fPIC -march=x86-64

HDRS    = dque.h dque_util.h

OBJS1   =dque_create.o dque_destroy.o dque_error.o dque_options.o
OBJS2   =dque_empty.o dque_size.o dque_max_size.o dque_key_erase.o dque_key_find.o dque_key_insert.o
OBJS3   =dque_back.o dque_front.o dque_get_data.o dque_set_data.o
OBJS4   =dque_begin.o dque_next.o dque_end.o dque_rbegin.o dque_rnext.o dque_rend.o
OBJS5	=dque_insert.o dque_erase.o dque_pop_back.o dque_pop_front.o dque_push_back.o dque_push_front.o
OBJS6   =dque_myalloc.o dque_mydelete.o dque_myfind.o dque_myinsert.o dque_myscan.o dque_mysearch.o
OBJS    =$(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS5) $(OBJS6)

LIBS    = libdque.a

all:    $(LIBS) $(HDRS) test fib_test_ttas fib_test_lockfree qsort_test_ttas qsort_test_lockfree chess_test_ttas chess_test_lockfree

$(OBJS): %.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

#../dque.h:     dque.h
#	cp dque.h ..

libdque.a:  $(HDRS) mydque.h $(OBJS)
	rm -f libdque.a
	$(AR) $(ARFLAGS) libdque.a $(OBJS)

test:	test.c dque_util.c dque_util.h $(LIBS)
	$(CC) $(CCFLAGS) -DTTAS test.c dque_util.c dque_util.h $(LIBS) -o $@

.PHONY : fib_test_ttas
fib_test_ttas:	
	#./clang -fopencilk -fcilktool=cilkscale -O3 fib_test.c -o fib_test
	./clang -fopencilk $(CCFLAGS) -DTTAS fib_test.c -o fib_test_ttas

.PHONY : qsort_test_ttas
qsort_test_ttas:	
	./clang -fopencilk $(CCFLAGS) -DTTAS qsort_test.c -o qsort_test_ttas

.PHONY : chess_test_ttas
chess_test_ttas:	
	./clang -fopencilk $(CCFLAGS) -DTTAS chess_test.c -o chess_test_ttas

.PHONY : fib_test_lockfree
fib_test_lockfree:	
	./clang -fopencilk $(CCFLAGS) -DCMPXCHG fib_test.c -o fib_test_lockfree

.PHONY : qsort_test_lockfree
qsort_test_lockfree:	
	./clang -fopencilk $(CCFLAGS) -DCMPXCHG qsort_test.c -o qsort_test_lockfree

.PHONY : chess_test_lockfree
chess_test_lockfree:	
	./clang -fopencilk $(CCFLAGS) -DCMPXCHG chess_test.c -o chess_test_lockfree

.PHONY : clean
clean:
	rm -f *.o
	rm -f *~
	rm -rf test
	rm -rf *test_ttas
	rm -rf *test_lockfree

# end
