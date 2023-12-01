
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


//-------------------------------------------------
unsigned long long todval (struct timeval *tp) {
    return tp->tv_sec * 1000 * 1000 + tp->tv_usec;
}
//-------------------------------------------------
/* 
 * nqueen  4 = 2 
 * nqueen  5 = 10 
 * nqueen  6 = 4 
 * nqueen  7 = 40 
 * nqueen  8 = 92 
 * nqueen  9 = 352 
 * nqueen 10 = 724
 * nqueen 11 = 2680 
 * nqueen 12 = 14200 
 * nqueen 13 = 73712 
 * nqueen 14 = 365596 
 * nqueen 15 = 2279184 
 */

/*
 * <a> contains array of <n> queen positions.  Returns 1
 * if none of the queens conflict, and returns 0 otherwise.
 */
//-------------------------------------------------
int ok (int n, char *a) {

  int i, j;
  char p, q;

  for (i = 0; i < n; i++) {
    p = a[i];
    for (j = i + 1; j < n; j++) {
      q = a[j];
      if (q == p || q == p - (j - i) || q == p + (j - i))
        return 0;
    }
  }

  return 1;
}
//-------------------------------------------------

int nqueens (int n, int j, char *a) {

  char *b;
  int *count;
  int solNum = 0;

  if (n == j) {
    return 1;
  }

  count = (int *) alloca(n * sizeof(int));
  (void) memset(count, 0, n * sizeof (int));

  b = (char *) alloca((j + 1) * sizeof (char));
  memcpy(b, a, j * sizeof (char));

  cilk_scope {
    for (int i = 0; i < n; i++) {
      b[j] = i;
      if (ok(j + 1, b))
        count[i] = cilk_spawn nqueens(n, j + 1, b);
    }
  }
  cilk_sync;

  for (int i = 0; i < n; i++) {
    solNum += count[i];
  }

  return solNum;
}

//-------------------------------------------------
int main(int argc, char *argv[]) { 
  pthread_t *thr;

  nthr = atoi(argv[2]);
  /*printf("using %d threads\n", nthr);*/
  thr = calloc(sizeof(*thr), nthr);

  int n = 13;
  char *a;
  int res;

  if (argc < 2) {
    fprintf (stderr, "Usage: %s [<cilk-options>] <n>\n", argv[0]);
    fprintf (stderr, "Use default board size, n = 13.\n");

  } else {
    n = atoi (argv[1]);
    //-- fprintf (stderr, "Running %s with n = %d.\n", argv[0], n);
  }

  // Start thread
  for (long i = 0; i < nthr; i++) {
     if (pthread_create(&thr[i], NULL, inc_thread, (void *)i) != 0) {
          perror("thread creating failed");
     }
  } 

  a = (char *) alloca (n * sizeof (char));
  res = 0;

  ctimer_t t;
  ctimer_start(&t);

  res = nqueens(n, 0, a);

  ctimer_stop(&t);
  ctimer_measure(&t);
  ctimer_print(t, "nqueens");

  // join thread
  for (long i = 0; i < nthr; i++)
      pthread_join(thr[i], NULL);

  if (res == 0) {
    fprintf (stderr, "No solution found.\n");
  } else {
    //-- fprintf (stderr, "Total number of solutions : %d\n", res);
  }
  return 0;
}

//-------------------------------------------------


