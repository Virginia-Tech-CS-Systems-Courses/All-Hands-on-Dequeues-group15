#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_insert(                                /* insert node in a queue       */
dque_qhead     *queue,                      /* queue to have node inserted  */
void           *data,                       /* data to insert with new node */
dque_qiter     *iter )                      /* iterator to specified node   */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *node;

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (data == (void *)NULL) {      /* invalid data pointer         */
        errcode = DQUEERR_NODATA;
    } else if (getfree( queue ) == NULL_NODE && ((errcode = dque_myalloc( queue )) != DQUEERR_NOERR)) {
        ;                   /* no free nodes? try to create more free nodes */
    } else if ((errcode = dque_mydelete( &getfree( queue ), &node, NOROTATE, &getfcnt( queue ) )) == DQUEERR_NOERR) {
        setdata( node, data );              /* set the data                 */
    }

    if (errcode != DQUEERR_NOERR) {         /* error? do not insert node    */
        ;
    } else if (iter == NULL_QITER) {        /* insert at the back of the queue? */
        errcode = dque_myinsert( &gethead(queue), node, NOROTATE, &gethcnt( queue ) ); 
    } else if (gethead(queue) == iter) {    /* first node is specified node?*/
        errcode = dque_myinsert( &gethead(queue), node, ROTATE, &gethcnt( queue ) );  /* insert at head of queue  */
    } else if (getflag(queue,DQUE_NOSCAN) || (errcode = dque_mysearch( &gethead(queue), iter )) == DQUEERR_NOERR) {
        errcode = dque_myinsert( &iter, node, NOROTATE, &gethcnt( queue ) ); /* insert at iterator used as headp */
    }

    return (errcode);
}

