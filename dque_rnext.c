
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned status              */
dque_rnext(                                 /* return prev iterator in queue*/
dque_qhead     *queue,                      /* queue to have iterator       */
dque_qiter    **iterp )                     /* pointer to returned iterator */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qiter     *iter;                   /* iterator ptr to node in queue*/

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (iterp == NULL_QITERP) {      /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITERP;
    } else if ((iter = *iterp) == NULL_QITER) {        /* invalid iterator? */
        errcode = DQUEERR_NOITER;
    } else {
        if (getdata(iter) == (void *)NULL) {/* invalid iterator?            */
            errcode = DQUEERR_INVITER;
            iter    = NULL_QITER;
	} else if (iter == gethead( queue )) {  /* end of queue?            */
            iter    = NULL_QITER;           /* pointer to stop iteration    */
        } else {
            iter    = getprev(iter);        /* else next iteration          */
        }
        *iterp  = iter;                     /* save new iterator            */
    }

    return (errcode);
}

