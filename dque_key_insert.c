
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_key_insert(                            /* insert node at specified pnt */
dque_qhead     *queue,                      /* queue to have node inserted  */
void           *key,                        /* key to use 4 insertion point */
COMPFUNC        comp,                       /* user comparison function     */
void           *data )                      /* data to insert               */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *headp;                  /* pointer to first qnode in queue */
    dque_qnode     *node;                   /* node to insert               */
    dque_qnode     *temp;                   /* node for insertion point     */
    int             val;

    if (key == (void *)NULL) {              /* no key? use specified node   */
        key     = data;
    }

    if (queue == NULL_QUEUE) {              /* invalid queue?               */
        errcode = DQUEERR_NOQUEUE;
    } else if (comp == (COMPFUNC)NULL) {    /* no comparison function?      */
        errcode = DQUEERR_NOCOMP;
    } else if (data == (void *)NULL) {      /* invalid data pointer?        */
        errcode = DQUEERR_NODATA;
    } else if (getfree( queue ) == NULL_NODE && ((errcode = dque_myalloc( queue )) != DQUEERR_NOERR)) {
        ;                   /* no free nodes? try to create more free nodes */
    } else if ((errcode = dque_mydelete( &getfree( queue ), &node, NOROTATE, &getfcnt( queue ) )) == DQUEERR_NOERR) {
        setdata( node, data );              /* set the data                 */
    }

    if (errcode != DQUEERR_NOERR) {         /* error? do not insert node    */
        ;
    } else if ( ((headp = gethead(queue)) == NULL_NODE) || ((*comp)( key, getdata(headp)) < 0) ) {     /* node goes in front?  */
        errcode = dque_myinsert( &gethead(queue), node, ROTATE, &gethcnt(queue) );
    } else if ((val = (*comp)( key, getdata(getprev(headp)) )) >= 0) {              /* node goes in back?   */
        if (val == 0 && getflag(queue, DQUE_NODUPE)) {                      /* duplicate node not allowed?  */
            errcode = DQUEERR_NODUPE;
        } else {
            errcode = dque_myinsert( &gethead(queue), node, NOROTATE, &gethcnt(queue) );
        }
    } else if ((errcode = dque_myscan( &gethead(queue), key, comp, &temp )) == DQUEERR_NOERR) {	/* node goes in the middle */
        if (getflag(queue, DQUE_NODUPE) && !(*comp)( key, getdata(getprev(temp)) ) ) { /* dupe not allowed? */
            errcode = DQUEERR_NODUPE;
        } else {
            errcode = dque_myinsert( &temp, node, NOROTATE, &gethcnt(queue) );      /* node goes in middle  */
        }
    }

    return (errcode);
}

