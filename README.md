# All-Hands-on-Dequeues-group15
ECE5510/CS5510 Fall2023 - Assignment #3

##### Lalit Prasad Peri (lalitprasad@vt.edu)
##### Will Downey (willd20@vt.edu)

### Description
### HowTo Compile & Run
* Ensure gcc and clang variables in Makefile are pointing to correct compiler versions
* run-test.sh is a one step compile and run script, which invokes Make and run.
* >>./run-test.sh

### Deliverables**
You should implement:
* one lock-based dequeue (35% of your grade) - *Done*
* one lock-free dequeue (35%) of your grade  - *Done*
* You should also provide a report with your findings and an explanation for them (15%). - *Done*
* Report.pdf (15%) - *Done*

### Results
##### |--------------------------------------
##### |Deque - Functional Correctness tests
##### |--------------------------------------
##### |------------------------------
##### |testing options() with no queue
##### |dque_options (DQUEOPT_HEADSIZ):                                             Pass
##### |qhead size: 48
##### |dque_options (DQUEOPT_NODESIZ):                                             Pass
##### |qnode size: 24
##### |
##### |------------------------------
##### |testing create() with static memory, add static memory with options()
##### |dque_create (using static memory):                                          Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back (no allocation allowed):                                     Pass
##### |dque_options (DQUEOPT_NOALLOC):                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_destroy (using static memory):                                         Pass
##### |
##### |------------------------------
##### |testing dynamic create() function calls
##### |dque_create (using dynamic memory):                                         Pass
##### |dque_options (DQUEOPT_VERSION):                                             Pass
##### |version 1.1
##### |dque_empty:                                                                 Pass
##### |empty queue: True
##### |
##### |------------------------------
##### |testing invalid calls to size() and max_size()
##### |dque_size (invalid pointer to queue):                                       Pass
##### |dque_size (invalid pointer to data):                                        Pass
##### |dque_max_size (invalid pointer to queue):                                   Pass
##### |dque_max_size (invalid pointer to data):                                    Pass
##### |
##### |size and maxsize should both be 0
##### |dque_size:                                                                  Pass
##### |    size: 0
##### |dque_max_size:                                                              Pass
##### |max size: 0
##### |
##### |------------------------------
##### |testing invalid calls to back() and front()
##### |dque_back (invalid pointer to queue):                                       Pass
##### |dque_back (invalid ptr to ptr to data):                                     Pass
##### |dque_front (invalid pointer to queue):                                      Pass
##### |dque_front (invalid ptr to ptr to data):                                    Pass
##### |
##### |------------------------------
##### |testing invalid calls to empty(), error(), and error_len()
##### |dque_empty (invalid pointer to queue):                                      Pass
##### |dque_empty (invalid pointer to data):                                       Pass
##### |dque_error (invalid pointer to buffer):                                     Pass
##### |dque_error (invalid buffer size):                                           Pass
##### |dque_error_len (invalid pointer to data):                                   Pass
##### |dque_error_len (unknown error code):                                        Pass
##### |
##### |------------------------------
##### |testing invalid calls to insert(), and erase() (delete)
##### |dque_insert (invalid pointer to queue):                                     Pass
##### |dque_insert (invalid pointer to data):                                      Pass
##### |dque_erase (invalid pointer to queue):                                      Pass
##### |dque_erase (invalid ptr to ptr to data):                                    Pass
##### |dque_erase (invalid pointer to iter):                                       Pass
##### |##### |------------------------------
##### |testing invalid calls to push_*() and pop_*()
##### |dque_push_back (invalid pointer to queue):                                  Pass
##### |dque_push_back (invalid pointer to data):                                   Pass
##### |dque_push_front(invalid pointer to queue):                                  Pass
##### |dque_push_front(invalid pointer to data):                                   Pass
##### |dque_pop_back  (invalid pointer to queue):                                  Pass
##### |dque_pop_back  (invalid data pointer):                                      Pass
##### |dque_pop_front (invalid pointer to queue):                                  Pass
##### |dque_pop_front (invalid data pointer):                                      Pass
##### |
##### |------------------------------
##### |testing invalid calls to iterator function
##### |dque_begin (invalid pointer to queue):                                      Pass
##### |dque_begin (invalid ptr to ptr to iter):                                    Pass
##### |dque_rbegin (invalid pointer to queue):                                     Pass
##### |dque_rbegin (invalid ptr to ptr to iter):                                   Pass
##### |dque_next (invalid pointer to queue):                                       Pass
##### |dque_next (invalid ptr to ptr to iter):                                     Pass
##### |dque_next (invalid ptr to iterator):                                        Pass
##### |dque_rnext (invalid pointer to queue):                                      Pass
##### |dque_rnext (invalid ptr to ptr to iter):                                    Pass
##### |dque_rnext (invalid ptr to iterator):                                       Pass
##### |dque_end (invalid pointer to queue):                                        Pass
##### |dque_end (invalid ptr to ptr to iter):                                      Pass
##### |dque_rend (invalid pointer to queue):                                       Pass
##### |dque_rend (invalid ptr to ptr to iter):                                     Pass
##### |
##### |------------------------------
##### |testing invalid calls to key_*()
##### |dque_key_find (invalid pointer to queue):                                   Pass
##### |dque_key_find (invalid pointer to key):                                     Pass
##### |dque_key_find (invalid pointer to comp):                                    Pass
##### |dque_key_find (invalid ptr to ptr to iter):                                 Pass
##### |dque_key_find (empty queue):                                                Pass
##### |dque_key_insert (invalid pointer to queue):                                 Pass
##### |dque_key_insert (invalid pointer to comp):                                  Pass
##### |
##### |dque_key_erase (invalid pointer to queue):                                  Pass
##### |dque_key_erase (invalid pointer to key):                                    Pass
##### |dque_key_erase (invalid pointer to comp):                                   Pass
##### |dque_key_erase (invalid ptr to ptr to data):                                Pass
##### |
##### |------------------------------
##### |use options() to force two dynamic memory allocations
##### |dque_options (set node count to 6):                                         Pass
##### |fill queue with ten integer elements to force allocations
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |size and maxsize should both be 10, if so, two allocations of 6 were successful
##### |dque_size:                                                                  Pass
##### |    size: 10
##### |dque_max_size:                                                              Pass
##### |max size: 10
##### |print queue of integers using forward iterator then reverse iterator
##### | 0 1 2 3 4 5 6 7 8 9
##### | 9 8 7 6 5 4 3 2 1 0
##### |
##### |------------------------------
##### |testing invalid calls to get_data(), and set_data()
##### |dque_get_data (invalid pointer to queue):                                   Pass
##### |dque_get_data (invalid ptr to ptr to data):                                 Pass
##### |dque_set_data (invalid pointer to queue):                                   Pass
##### |dque_set_data (invalid ptr to ptr to data):                                 Pass
##### |------------------------------
##### |test key_*() functions
##### |dque_key_erase (remove zero node):                                          Pass
##### |dque_key_erase data == zero node:                                           Pass
##### |dque_key_erase (remove fifth node):                                         Pass
##### |dque_key_erase data == fifth node:                                          Pass
##### |dque_key_erase (remove ninth node):                                         Pass
##### |dque_key_erase data == ninth node:                                          Pass
##### |dque_key_erase (attempt to remove non-existent node):                       Pass
##### | 1 2 3 4 6 7 8
##### | 8 7 6 4 3 2 1
##### |
##### |remove all but one integer elements
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |
##### |compare pointers returned by dque_back() and dque_front(), should be the same
##### |dque_back:                                                                  Pass
##### |dque_front:                                                                 Pass
##### |dque_back == dque_front:                                                    Pass
##### |
##### |compare iterators returned by dque_begin() and dque_rbegin(), should be the same
##### |dque_begin:                                                                 Pass
##### |dque_rbegin:                                                                Pass
##### |dque_begin == dque_rbegin:                                                  Pass
##### |
##### |insert and erase at the front, back, and middle of the queue
##### |dque_insert:                                                                Pass
##### |dque_insert:                                                                Pass
##### |dque_insert:                                                                Pass
##### | 0 5 8 9
##### | 9 8 5 0
##### |dque_rnext:                                                                 Pass
##### |dque_delete:                                                                Pass
##### |dque_delete data == fifth node:                                             Pass
##### |dque_begin:                                                                 Pass
##### |dque_delete:                                                                Pass
##### |dque_delete data == zero node:                                              Pass
##### |dque_rbegin:                                                                Pass
##### |dque_delete:                                                                Pass
##### |dque_delete data == ninth node:                                             Pass
##### | 8
##### | 8
##### |
##### |remove last integer elements
##### |dque_pop_front:                                                             Pass
##### |dque_empty:                                                                 Pass
##### |empty: True
##### |dque_destroy (invalid qhead pointer):                                       Pass
##### |dque_destroy (invalid queue pointer):                                       Pass
##### |dque_destroy (using dynamic memory):                                        Pass
##### |
##### |------------------------------
##### |fill queue with ten random order integer elements using key_insert
##### |dque_create (using dynamic memory):                                         Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |
##### |print queue of integers using forward iterator
##### | 0 0 1 2 3 4 4 6 8 9
##### |print queue of integers using forward iterator
##### | 0 0 1 2 3 4 4 6 8 9
##### |
##### |remove all integer elements
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |dque_pop_front:                                                             Pass
##### |
##### |------------------------------
##### |turn off duplication, fill queue with eight random order integer elements
##### |dque_options (DQUEOPT_NODUPE):                                              Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert:                                                            Pass
##### |dque_key_insert (with duplicate key):                                       Pass
##### |dque_destroy (using dynamic memory):                                        Pass
##### |
##### |------------------------------
##### |fill queue with five string elements
##### |dque_create (using dynamic memory):                                         Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |dque_push_back:                                                             Pass
##### |++++++++++++++++++++++++++++++++++++++++++
##### |DEQUE: HELLO WORLD!!!
##### |++++++++++++++++++++++++++++++++++++++++++
##### |
##### |++++++++++++++++++++++++++++++++++++++++++
##### |OVERALL DEQUE FUNCTIONAL TEST STATUS:                                       PASS
##### |++++++++++++++++++++++++++++++++++++++++++
##### |
##### |--------------------------------------
##### | Fibonacci Test (Deque-Lock)
##### |--------------------------------------
##### |fib(40) = 102334155      Time(fib) = 6.437202675 sec
##### |fib(40) = 102334155      Time(fib) = 3.309294032 sec
##### |fib(40) = 102334155      Time(fib) = 1.783994213 sec
##### |fib(40) = 102334155      Time(fib) = 0.959027745 sec
##### |fib(40) = 102334155      Time(fib) = 0.574613550 sec
##### |--------------------------------------
##### | Qsort Test - 1 Million Number Sorting (Deque Lock)
##### |--------------------------------------
##### |Time(sample_qsort) = 0.149345755 sec
##### |Time(sample_qsort) = 0.078168955 sec
##### |Time(sample_qsort) = 0.049957029 sec
##### |Time(sample_qsort) = 0.035758559 sec
##### |Time(sample_qsort) = 0.034763643 sec
##### |--------------------------------------
##### | Chess Test - N Queens Problem - 16 (Deque-Lock)
##### |--------------------------------------
##### |Time(nqueens) = 52.401178088 sec
##### |Time(nqueens) = 27.726055888 sec
##### |Time(nqueens) = 14.222283716 sec
##### |Time(nqueens) = 7.506914728 sec
##### |Time(nqueens) = 4.272595235 sec
##### |--------------------------------------
##### |--------------------------------------
##### |--------------------------------------
##### | Fibonacci Test (Deque-Lock-Free)
##### |--------------------------------------
##### |fib(40) = 102334155      Time(fib) = 6.643173696 sec
##### |fib(40) = 102334155      Time(fib) = 3.699610741 sec
##### |fib(40) = 102334155      Time(fib) = 1.808304547 sec
##### |fib(40) = 102334155      Time(fib) = 0.969222910 sec
##### |fib(40) = 102334155      Time(fib) = 0.570719983 sec
##### |--------------------------------------
##### | Qsort Test - 1 Million Number Sorting (Deque-Lock-Free)
##### |--------------------------------------
##### |Time(sample_qsort) = 0.156331574 sec
##### |Time(sample_qsort) = 0.081102899 sec
##### |Time(sample_qsort) = 0.048834315 sec
##### |Time(sample_qsort) = 0.035476208 sec
##### |Time(sample_qsort) = 0.036703825 sec
##### |--------------------------------------
##### | Chess Test - N Queens Problem - 8 (Deque-Lock-Free)
##### |--------------------------------------
##### |Time(nqueens) = 53.595329430 sec
##### |Time(nqueens) = 30.480677994 sec
##### |Time(nqueens) = 14.731846333 sec
##### |Time(nqueens) = 7.582406832 sec
##### |Time(nqueens) = 4.258525693 sec
##### |=========================================
##### | END OF ALL TESTS
##### |=========================================


