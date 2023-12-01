#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_end(                                   /* return stop iterator         */
dque_qhead     *queue,                      /* queue to have iterator       */
dque_qiter    **iter )                      /* pointer to returned iterator */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (iter == NULL_QITERP) {       /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITERP;
    } else {                                /* return ptr to stop iteration */
        *iter   = NULL_QITER;
    }

    return (errcode);
}

