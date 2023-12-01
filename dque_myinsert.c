
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_myinsert(                              /* internal node insert         */
dque_qnodep    *nodep,                      /* queue to have node inserted  */
dque_qnode     *node,                       /* qnode to insert into queue   */
int             rotate,                     /* rotate inserted node 2 front?*/
unsigned int   *count )                     /* queue counter to increment   */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *headp   = *nodep;       /* ptr to first qnode in queue  */

    if (headp == NULL_NODE) {               /* empty queue?                 */
	headp   = node;                     /* needed if we rotate          */
        setprev( node,  node );             /* node->prev  = node;          */
        setnext( node,  node );             /* node->next  = node;          */
        *nodep  = node;                     /* *nodep      = node;          */
    } else {                                /* queue not empty, insert node */
        setnext( node, headp );             /* node->next  = headp;         */
	setprev( node, getprev(headp) );    /* node->prev  = headp->prev;   */
	setnext( getprev(headp), node );    /* headp->prev->next   = node;  */
	setprev( headp, node          );    /* headp->prev = node;          */
    }

    if (rotate) {                           /* insert at front of queue?    */
        *nodep = getprev( headp );          /* *nodep = headp->prev         */
    }

    if (count != (unsigned int *)NULL) {    /* have counter to increment?   */
        inc_uns(*count);                    /* increment if all went well   */
    }

    return (errcode);
}

