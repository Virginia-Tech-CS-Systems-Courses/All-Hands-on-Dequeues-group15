
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_mydelete(                              /* delete first node from queue */
dque_qnodep    *nodep,                      /* queue to have node deleted   */
dque_qnode    **node,                       /* ptr to deleted node          */
int             rotate,                     /* rotate 2 delete end node?    */
unsigned int   *count )                     /* queue counter to decrement   */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *headp   = *nodep;       /* ptr to first qnode in queue  */

    if (rotate) {                           /* delete the last node instead?*/
        *nodep  = getprev( headp );         /* queue = headp->prev          */
        headp   = *nodep;                   /* get new first node in queue  */
    }

    if (headp == getnext( headp )) {        /* queue has only one qnode?    */
        *node   = headp;                    /* set returned node            */
        *nodep  = NULL_NODE;                /* queue now a NULL queue       */
    } else {                                /* else get qnode               */
        *node   = headp;                    /* set returned node            */
        *nodep  = getnext(headp);           /* queue = headp->next;         */
        setprev( getnext(headp), getprev(headp) );  /* headp->next->prev = headp->prev; */
        setnext( getprev(headp), getnext(headp) );  /* headp->prev->next = headp->next; */
    }

    if (count != (unsigned int *)NULL) {    /* have counter to decrement?   */
        dec_uns(*count);                    /* safe decrement               */
    }

    return (errcode);

}

