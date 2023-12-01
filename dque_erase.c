#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned status              */
dque_erase(                                 /* remove node from queue       */
dque_qhead     *queue,                      /* queue to have node deleted   */
void          **data,                       /* returned data pointer        */
dque_qiter     *iter )                      /* iterator to specified node   */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *headp;                  /* first qnode in queue     */
    dque_qnode     *node;                   /* pointer to deleted node      */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (void **)NULL) {     /* invalid data pointer         */
        errcode = DQUEERR_NODATAP;
    } else if (iter == NULL_QITER) {        /* invalid iterator?            */
        errcode = DQUEERR_NOITER;
    } else if ((headp = gethead(queue)) == NULL_NODE) {     /* empty queue? */
        *data    = (void *)NULL;            /* technically OK, but no data  */
        return (DQUEERR_NOERR);
    } else if (headp == iter) {             /* specified node is first node */
        errcode = dque_mydelete( &gethead( queue ), &node, NOROTATE, &gethcnt( queue ) );
    } else if (getflag(queue,DQUE_NOSCAN) || (errcode = dque_mysearch( &gethead( queue ), iter )) == DQUEERR_NOERR) {
        errcode = dque_mydelete( &iter, &node, NOROTATE, &gethcnt(queue) ); /* node in queue? */
    } else if (errcode == DQUEERR_NOTFOUND) {   /* iter specified node not found? */
        *data    = (void *)NULL;            /* technically OK, but no data  */
        return (DQUEERR_NOERR);
    }

    if (errcode != DQUEERR_NOERR) {         /* error? do not free node      */
        ;
    } else if ((errcode = dque_myinsert( &getfree( queue ), node, NOROTATE, &getfcnt( queue ) )) == DQUEERR_NOERR) {
        *data   = getdata( node );
	setdata( node, (void *)NULL );      /* set to null for safety       */
    }

    return (errcode);
}

