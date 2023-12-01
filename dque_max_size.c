
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_max_size(                              /* return available # of qnodes */
dque_qhead     *queue,                      /* queue to check               */
unsigned int   *data )                      /* pointer to returned data     */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (unsigned *)NULL) {  /* invalid data pointer?        */
        errcode = DQUEERR_NODATA;
    } else {                                /* return head and free counts  */
        *data   = gethcnt(queue) + getfcnt(queue);
    }

    return (errcode);
}

