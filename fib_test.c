
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cilk/cilk.h>
#include "ctimer.h"

#include <pthread.h>
#include <sched.h>
#include <assert.h>
#include <sys/time.h>
#include <errno.h>

#include <string.h>             
#include <time.h>
#include "dque.h"
//#include "mydque2.h"
#include "dque_util.h"

#ifdef CMPXCHG
#include "spinlock-cmpxchg.h"
#elif TTAS
#include "spinlock-ttas.h"
#else
#endif

#ifndef cpu_relax
#define cpu_relax() asm volatile("pause\n": : :"memory")
#endif

//---------------------------------------------------------------------------
//carried frm spilock tests
//---------------------------------------------------------------------------
#define N_PAIR 16000000

static int nthr = 0;

static volatile uint32_t wflag;
/* Wait on a flag to make all threads start almost at the same time. */
void wait_flag(volatile uint32_t *flag, uint32_t expect) {
    __sync_fetch_and_add((uint32_t *)flag, 1);
    while (*flag != expect) {
        cpu_relax();
    }
}

#define NCOUNTER 1
#define CACHE_LINE 64

// Use thread local counter to avoid cache contention between cores.
// For TSX, this avoids TX conflicts so the performance overhead/improvement is
// due to TSX mechanism.
static __thread int8_t counter[CACHE_LINE*NCOUNTER];

spinlock sl;

void *inc_thread(void *id) {
    int n = N_PAIR / nthr;
    assert(n * nthr == N_PAIR);

    wait_flag(&wflag, nthr);

    /* Start lock unlock test. */
    for (int i = 0; i < n; i++) {
        spin_lock(&sl);
        for (int j = 0; j < NCOUNTER; j++) counter[j*CACHE_LINE]++;
        spin_unlock(&sl);
    }
    return NULL;
}

//--------------------------------------------------
dque_err errcode = DQUEERR_NOERR;
unsigned status;

void     myprintf( dque_qhead *queue, int typ       );
void     myrprintf(dque_qhead *queue, int typ       );
dque_err prtest(   char *name,   dque_err expcode, dque_err errcode );
int      intcomp(  void *i1,     void *i2      );
int      intrcomp( void *i1,     void *i2      );

char    buf[128], bfr[128], bfr2[128], buff[128];
int    array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
int   array3[] = { 6, 2, 4, 1, 9, 3, 0, 8, 4, 0 };
char *array2[] = { "zero", "one", "two", "three", "four" };
char *name = "West East";

//--------------------------------------------------
typedef struct {
    int  id;
    char name[20];
    int  year;
    int  classes[7];
} record;

void prrecord( record *rec );

//--------------------------------------------------
typedef struct {
    int   idx;
    int   val;
    char *str;
} reckey;

//--------------------------------------------------
record  array4[] = {
	{ 1076, "Hello World", 2021, { 123, 654, 789, 0, 0, 0, 0 }},
	{ 1145, "Hello World", 2022, { 123, 456, 707, 0, 0, 0, 0 }},
	{ 1103, "Hello World", 2021, { 123, 456, 987, 0, 0, 0, 0 }},
	{ 1000, "Hello World", 2020, { 123, 456, 789, 0, 0, 0, 0 }},
	{ 1172, "Hello World", 2023, { 123, 654, 999, 0, 0, 0, 0 }}
	};

//---------------------------------------------------------------------------
long fib(long n) {

    dque_qhead *queue;
    //dque_qhead *queue2 = NULL_QUEUE;
    //dque_pri_qhead *pri;
    //int   *val,  val2;
    //int   major, minor;
    unsigned int headsize, nodesize;
    //dque_qiter *iter   = NULL_QITER;
    //dque_qiter *iter2  = NULL_QITER;
    //void  *data, *data2;
    //reckey  key;
    //record *rec;
    headsize=DQUEOPT_HEADSIZ;
    nodesize=DQUEOPT_NODESIZ;

    //create(&queue, headsize+(2*nodesize), bfr);
    //spin_lock(&sl);
    //push_back( queue, &array[0] );
    //pop_front( queue, (void *)&val );
    //spin_unlock(&sl);

  if (n < 2)
    return n;
  long x, y;
  cilk_scope {
    x = cilk_spawn fib(n-1);
    y = fib(n-2);
  }
  cilk_sync;
   //destroy(&queue);
  return x + y;
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    pthread_t *thr;

    long n = 10;
    n = atol(argv[1]);
    nthr = atoi(argv[2]);
    /*printf("using %d threads\n", nthr);*/
    thr = calloc(sizeof(*thr), nthr);

    // Start thread
    for (long i = 0; i < nthr; i++) {
      if (pthread_create(&thr[i], NULL, inc_thread, (void *)i) != 0) {
           perror("thread creating failed");
      }
    } 

  ctimer_t t;
  ctimer_start(&t);

  long result = fib(n);

  ctimer_stop(&t);
  ctimer_measure(&t);

  printf("fib(%ld) = %ld\t", n, result);
  ctimer_print(t, "fib");

  // join thread
  for (long i = 0; i < nthr; i++)
      pthread_join(thr[i], NULL);

  return 0;
}
//---------------------------------------------------------------------------
