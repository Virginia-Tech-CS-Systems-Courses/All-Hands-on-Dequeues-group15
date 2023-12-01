#include <stdio.h>                          /* need NULL definition         */
#include <stdlib.h>                         /* need for malloc and free     */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_destroy(                               /* destroy a queue              */
dque_qheadp    *queuep )                    /* ptr to ptr to a queue        */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qhead     *queue;
    dque_qnode     *node;

    if (queuep == NULL_QUEUEP) {            /* no pointer to queue head?    */
        errcode = DQUEERR_NOQUEUEP;
    } else if ((queue = *queuep) == NULL_QUEUE) {   /* no pointer to queue? */
        errcode = DQUEERR_NOQUEUE;
    } else if (getflag(queue, DQUE_NOALLOC) != 0) { /* no dynamic allocation? */
        ;                                           /* yes, so nothing to free*/
    } else {                                /* no, free the allocated memory  */
        while (getblks(queue) != NULL_NODE && errcode == DQUEERR_NOERR) {
            /* while block list is not empty, remove last memory block and free it  */
            if ((errcode = dque_mydelete( &getblks(queue), &node, ROTATE, &getbcnt(queue) )) == DQUEERR_NOERR) {
                free( node );
            }
        }

        if (errcode == DQUEERR_NOERR) {
            free( queue );
            *queuep = NULL_QUEUE;
        }
    }

    return (errcode);
}

