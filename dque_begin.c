#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_begin(                                 /* return iterator to queue     */
dque_qhead     *queue,                      /* queue to have iterator       */
dque_qiter    **iter )                      /* pointer to returned iterator */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (iter == NULL_QITERP) {       /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITERP;
    } else if (gethead(queue) == NULL_NODE){/* empty queue?                 */
        *iter   = NULL_QITER;               /* equal to dque_end()          */
    } else {
        *iter   = gethead( queue );         /* pointer to first node in queue */
    }

    return (errcode);
}

