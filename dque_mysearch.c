#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned status              */
dque_mysearch(                              /* search queue for qnode       */
dque_qnodep    *nodep,                      /* queue to search for qnode    */
dque_qnode     *node )                      /* qnode to search for          */
{                                           /*------------------------------*/
    dque_qnode     *headp   = *nodep;       /* first qnode in queue         */
    dque_qnode     *currp   = headp;        /* current qnode in search      */


    do  {
        if (currp == node) {                /* specified node first in list?*/
            return (DQUEERR_NOERR);
        }
        currp = getnext(currp);
    } while (currp != headp);

    return (DQUEERR_NOTFOUND);
}

