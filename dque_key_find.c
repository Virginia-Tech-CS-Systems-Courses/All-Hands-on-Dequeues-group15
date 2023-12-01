#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_key_find(                              /* find node with specified key */
dque_qhead     *queue,                      /* queue to have node inserted  */
void           *key,                        /* key to search queue for      */
COMPFUNC        comp,                       /* comparison function          */
dque_qiter    **iter )                      /* iterator to specified node   */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *headp;                  /* pointer to 1st qnode in queue*/
    dque_qnode     *node;                   /* returned node as iterator    */

    if (queue == NULL_QUEUE) {              /* invalid queue pointer?       */
        errcode = DQUEERR_NOQUEUE;
    } else if (key == (void *)NULL) {       /* no key?                      */
        errcode = DQUEERR_NOKEY;
    } else if (comp == (COMPFUNC)NULL) {    /* no caomparison function?     */
        errcode = DQUEERR_NOCOMP;
    } else if (iter == NULL_QITERP) {       /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITERP;
    } else if ((headp = gethead(queue)) == NULL_NODE) {     /* empty queue? */
        errcode = DQUEERR_NOTFOUND;
    } else if ((errcode = dque_myfind( &headp, key, comp, &node )) == DQUEERR_NOERR) {
        *iter   = (dque_qiter *)node;       /* set the data                 */
    }

    if (errcode != DQUEERR_NOERR && iter != NULL_QITERP) {
        *iter   = NULL_QITER;               /* just to make sure            */
    }

    return (errcode);
}

