#!/bin/bash

function run_test() {
    for nthr in 1 2 4 8 16; do
        ./$1 $nthr > /dev/null
        for i in `seq 1 3`; do
            ./$1 $nthr
        done
        echo
    done
}

make clean
make all
echo "--------------------------------------"
echo "test test-spinlock-ttas"
echo "--------------------------------------"
run_test "test-spinlock-ttas"
echo "--------------------------------------"
echo "Deque - Functional Correctness tests"
echo "--------------------------------------"
./test
echo "--------------------------------------"
echo " Fibonacci Test (Deque-Lock)"
echo "--------------------------------------"
CILK_NWORKERS=1  ./fib_test_ttas 40 1
CILK_NWORKERS=2  ./fib_test_ttas 40 2
CILK_NWORKERS=4  ./fib_test_ttas 40 4
CILK_NWORKERS=8  ./fib_test_ttas 40 8
CILK_NWORKERS=16 ./fib_test_ttas 40 16
echo "--------------------------------------"
echo " Qsort Test - 1 Million Number Sorting (Deque Lock)"
echo "--------------------------------------"
CILK_NWORKERS=1  ./qsort_test_ttas 1000000 1
CILK_NWORKERS=2  ./qsort_test_ttas 1000000 2
CILK_NWORKERS=4  ./qsort_test_ttas 1000000 4
CILK_NWORKERS=8  ./qsort_test_ttas 1000000 8
CILK_NWORKERS=16 ./qsort_test_ttas 1000000 16
echo "--------------------------------------"
echo " Chess Test - N Queens Problem - 16 (Deque-Lock)"
echo "--------------------------------------"
CILK_NWORKERS=1  ./chess_test_ttas 14 1
CILK_NWORKERS=2  ./chess_test_ttas 14 2
CILK_NWORKERS=4  ./chess_test_ttas 14 4
CILK_NWORKERS=8  ./chess_test_ttas 14 8
CILK_NWORKERS=16 ./chess_test_ttas 14 16
echo "--------------------------------------"
echo "--------------------------------------"
echo "--------------------------------------"
echo " Fibonacci Test (Deque-Lock-Free)"
echo "--------------------------------------"
CILK_NWORKERS=1  ./fib_test_lockfree 40 1
CILK_NWORKERS=2  ./fib_test_lockfree 40 2
CILK_NWORKERS=4  ./fib_test_lockfree 40 4
CILK_NWORKERS=8  ./fib_test_lockfree 40 8
CILK_NWORKERS=16 ./fib_test_lockfree 40 16
echo "--------------------------------------"
echo " Qsort Test - 1 Million Number Sorting (Deque-Lock-Free)"
echo "--------------------------------------"
CILK_NWORKERS=1  ./qsort_test_lockfree 1000000 1
CILK_NWORKERS=2  ./qsort_test_lockfree 1000000 2
CILK_NWORKERS=4  ./qsort_test_lockfree 1000000 4
CILK_NWORKERS=8  ./qsort_test_lockfree 1000000 8
CILK_NWORKERS=16 ./qsort_test_lockfree 1000000 16
echo "--------------------------------------"
echo " Chess Test - N Queens Problem - 8 (Deque-Lock-Free)"
echo "--------------------------------------"
CILK_NWORKERS=1  ./chess_test_lockfree 14 1
CILK_NWORKERS=2  ./chess_test_lockfree 14 2
CILK_NWORKERS=4  ./chess_test_lockfree 14 4
CILK_NWORKERS=8  ./chess_test_lockfree 14 8
CILK_NWORKERS=16 ./chess_test_lockfree 14 16
echo "========================================="
echo " END OF ALL TESTS"
echo "========================================="

