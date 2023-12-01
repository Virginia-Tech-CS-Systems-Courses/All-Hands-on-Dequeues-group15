
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_pop_front(                             /* remove first qnode from queue*/
dque_qhead     *queue,                      /* queue to have node removed   */
void          **data )                      /* returned pointer to data     */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *node;                   /* pointer to deleted node      */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (void **)NULL) {     /* invalid data pointer?        */
        errcode = DQUEERR_NODATAP;
    } else if (gethead(queue) == NULL_NODE){/* empty queue?                 */
        *data    = (void *)NULL;            /* technically OK, but no data  */
    } else if ((errcode = dque_mydelete( &gethead( queue ), &node, NOROTATE, &gethcnt( queue ) )) != DQUEERR_NOERR) {
        ;                                   /* NOROTATE to delete from front*/
    } else if ((errcode = dque_myinsert( &getfree( queue ), node, NOROTATE, &getfcnt( queue ) )) == DQUEERR_NOERR) {
        *data   = getdata( node );
	setdata( node, (void *)NULL );      /* set to null for safety       */
    }

    return (errcode);
}

