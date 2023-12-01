#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_get_data(                              /* get iterator's node data     */
dque_qiter     *iter,                       /* pointer to iterator          */
void          **data )                      /* pointer to data              */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (iter == NULL_QITER) {               /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITER;
    } else if (data == (void **)NULL) {     /* invalid data pointer?        */
        errcode = DQUEERR_NODATAP;
    } else {                                /* return user's data pointer   */
        *data   = getdata( iter );
    }

    return (errcode);
}

