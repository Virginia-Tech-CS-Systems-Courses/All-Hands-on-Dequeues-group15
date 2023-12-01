
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_size(                                  /* return number of nodes       */
dque_qhead     *queue,                      /* queue to count nodes         */
unsigned int   *data )                      /* ptr to returned data         */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (unsigned *)NULL) {  /* invalid data pointer?        */
        errcode = DQUEERR_NODATA;
    } else {                                /* return head queue counts     */
        *data   = gethcnt( queue );
    }

    return (errcode);
}

