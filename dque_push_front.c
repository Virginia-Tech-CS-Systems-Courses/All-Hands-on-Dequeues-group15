#include <stdio.h>
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_push_front(                            /* insert node onto front of queue */
dque_qhead     *queue,                      /* queue to have node inserted  */
void           *data )                      /* data to insert into queue    */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *node;                   /* pointer to inserted node     */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (void *)NULL) {      /* invalid data pointer?        */
        errcode = DQUEERR_NODATA;
    } else if (getfree( queue ) == NULL_NODE && ((errcode = dque_myalloc( queue )) != DQUEERR_NOERR)) {
        ;                   /* no free nodes? try to create more free nodes */
    } else if ((errcode = dque_mydelete( &getfree( queue ), &node, NOROTATE, &getfcnt( queue ) )) == DQUEERR_NOERR) {
        //spin_lock(&sl);
        setdata( node, data );              /* got node, set the data       */
        //spin_unlock(&sl);
    }

    if (errcode == DQUEERR_NOERR) {         /* no error? insert node        */
        errcode = dque_myinsert( &gethead( queue ), node, ROTATE, &gethcnt( queue ) );
    }                                       /* ROTATE to insert at front    */

    return (errcode);
}

