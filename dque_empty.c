#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_empty(                                 /* return non-zero if empty     */
dque_qhead     *queue,                      /* queue to check for nodes     */
unsigned int   *data )                      /* pointer to returned data     */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (void *)NULL) {      /* invalid data pointer?        */
        errcode = DQUEERR_NODATA;
    } else {                                /* return non-zero if empty     */
	*data   = (unsigned int)(gethead(queue) == NULL_NODE ? 1 : 0);
    }

    return (errcode);
}

