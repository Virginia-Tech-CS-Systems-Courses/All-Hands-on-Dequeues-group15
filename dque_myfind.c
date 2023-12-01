#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

/* ------------------------------------------------------------------------ */
/*      F U N C T I O N S                                                   */
/* ------------------------------------------------------------------------ */

dque_err                                    /* returned completion status   */
dque_myfind(                                /* search queue for qnode       */
dque_qnodep    *nodep,                      /* queue to search for qnode    */
void           *key,                        /* key to search queue for      */
COMPFUNC        comp,                       /* user comparison function     */
dque_qnode    **node )                      /* qnode to search for          */
{                                           /*------------------------------*/
    dque_qnode     *headp   = *nodep;       /* ptr to first qnode in queue  */
    dque_qnode     *currp   = headp;        /* ptr to current search qnode  */
    int             val;

    do  {
        if ((val = (*comp)( key, getdata(currp) )) == 0) {   /* found node? */
            *node   = currp;
            return (DQUEERR_NOERR);         /* return no error as true      */
        } else if (val < 0) {               /* past where key is in queue?  */
            break;
        }
        currp = getnext(currp);             /* increment current pointer    */
    } while (currp != headp);               /* until we search whole list   */

    return (DQUEERR_NOTFOUND);              /* return error as false        */
}

