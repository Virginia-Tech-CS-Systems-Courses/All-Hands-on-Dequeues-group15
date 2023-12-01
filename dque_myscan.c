
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_myscan(                                /* scan queue for insert point  */
dque_qnodep    *nodep,                      /* queue to search for insert   */
void           *key,                        /* key to search queue for      */
COMPFUNC        comp,                       /* user comparison function     */
dque_qnode    **node )                      /* ptr to qnode for insertion   */
{                                           /*------------------------------*/
    dque_qnode     *headp   = *nodep;       /* ptr to first qnode in queue  */
    dque_qnode     *currp   = headp;        /* ptr to current search qnode  */

    if ((*comp)( key, getdata(currp) ) >= 0) {/* insert point not at headp? */
        for (currp = getnext(currp); currp != headp; currp = getnext(currp) ) {
            if ((*comp)( key, getdata(currp) ) < 0) {
                break;                      /* found insert point?          */
            }
        }
    }

    *node   = currp;

    return (DQUEERR_NOERR);                 /* return no error              */
}

