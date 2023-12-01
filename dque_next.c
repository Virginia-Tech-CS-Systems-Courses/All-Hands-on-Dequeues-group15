
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_next(                                  /* return next iterator in queue*/
dque_qhead     *queue,                      /* queue to have iterator       */
dque_qiter    **iterp )                     /* ptr to ptr to iterator       */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qiter     *iter;                   /* iterator ptr to node in queue*/

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (iterp == NULL_QITERP) {      /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITERP;
    } else if ((iter = *iterp) == NULL_QITER) {        /* invalid iterator? */
        errcode = DQUEERR_NOITER;
    } else {                        /* increment and check for end of queue */
        if (getdata(iter) == (void *)NULL) {/* invalid iterator?            */
            errcode = DQUEERR_INVITER;
            iter    = NULL_QITER;
	} else if ((iter = getnext(iter)) == gethead( queue )) { /* queue end? */
            iter    = NULL_QITER;           /* pointer to stop iteration    */
        }
        *iterp  = iter;                     /* save new iterator            */
    }

    return (errcode);
}

