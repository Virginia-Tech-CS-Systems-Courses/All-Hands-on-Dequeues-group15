#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_key_erase(                             /* remove node w/specified key  */
dque_qhead     *queue,                      /* queue to have node removed   */
void           *key,                        /* key to use to find node      */
COMPFUNC        comp,                       /* user comparison function     */
void          **data )                      /* data from deleted found node */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *headp;                  /* pointer to first qnode in queue */
    dque_qnode     *node;                   /* removed node                 */
    dque_qnode     *temp;                   /* node for temporary head      */

    if (queue == NULL_QUEUE) {              /* invalid queue?               */
        errcode = DQUEERR_NOQUEUE;
    } else if (key == (void *)NULL) {       /* no key?                      */
        errcode = DQUEERR_NOKEY;
    } else if (comp == (COMPFUNC)NULL) {    /* no comparison function?      */
        errcode = DQUEERR_NOCOMP;
    } else if (data == (void **)NULL) {     /* invalid data pointer?        */
        errcode = DQUEERR_NODATAP;
    } else if ((headp = gethead(queue)) == NULL_NODE) {     /* empty queue? */
        *data   = (void *)NULL;
	return (DQUEERR_NOERR);             /* OK, qnode is not in the queue*/
    } else if ((errcode = dque_myfind( &headp, key, comp, &temp )) != DQUEERR_NOERR) {
        *data   = (void *)NULL;
	return (DQUEERR_NOERR);             /* OK, qnode is not in the queue*/
    } else if (temp == headp) {             /* delete the first node?       */
        errcode = dque_mydelete( &gethead(queue), &node, NOROTATE, &gethcnt(queue) );
    } else {                                /* no, delete qnode in the queue*/
        errcode = dque_mydelete( &temp,           &node, NOROTATE, &gethcnt(queue) );
    }

    if (errcode != DQUEERR_NOERR) {         /* error? do not free node      */
        ;
    } else if ((errcode = dque_myinsert( &getfree( queue ), node, NOROTATE, &getfcnt( queue ) )) == DQUEERR_NOERR) {
        *data   = getdata( node );
        setdata( node, (void *)NULL );      /* set to null to show invalid  */
    }

    return (errcode);
}

