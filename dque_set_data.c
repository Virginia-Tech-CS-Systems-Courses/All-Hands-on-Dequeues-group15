
#include <stdio.h>                          /* need NULL definition         */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_set_data(                              /* set iterator's node data     */
dque_qiter     *iter,                       /* pointer to iterator          */
void           *data )                      /* pointer to data              */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    if (iter == NULL_QITER) {               /* invalid iterator pointer?    */
        errcode = DQUEERR_NOITER;
    } else if (data == (void *)NULL) {      /* invalid data pointer?        */
        errcode = DQUEERR_NODATA;
    } else {                                /* set the user's data          */
        setdata( iter, data );
    }

    return (errcode);
}

