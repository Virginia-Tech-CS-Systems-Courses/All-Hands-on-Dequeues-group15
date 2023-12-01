#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_back(                                  /* return last element data     */
dque_qhead     *queue,                      /* queue with element data      */
void          **data )                      /* ptr to ptr to returned data  */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *node;

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (void **)NULL) {     /* invalid data pointer?        */
        errcode = DQUEERR_NODATAP;
    } else if (gethead(queue) == NULL_NODE){/* empty queue?                 */
        *data    = (void *)NULL;            /* technically OK, but no data  */
    } else {
        node    = getprev( gethead(queue) );/* ptr to last node in queue    */
	*data   = getdata( node );
    }

    return (errcode);
}

