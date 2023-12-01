#include <stdio.h>                          /* need NULL definition         */
#include <string.h>                         /* need for sprintf, strcpy     */
#include "mydque.h"
#include "dque.h"

static const char  *emsg[]  = {
    "No error",
    "Unknown error code",
    "Could not dynamically allocate memory",
    "Invalid pointer to queue",
    "Invalid pointer to pointer to queue",
    "Invalid pointer to data",
    "Invalid pointer to pointer to data",
    "Invalid pointer to iterator",
    "Invalid pointer to pointer to iterator",
    "Specified buffer size is too small",
    "Buffer size resulted in too few nodes",
    "Empty queue",
    "Invalid pointer to key",
    "Invalid pointer to comparison function",
    "Dynamic allocation not allowed",
    "Node not found",
    "Unknown queue options option",
    "No duplicates allowed in priority queue",
    "invalid iterator to deleted node",
    "invalid pointer to buffer",
    "invalid header buffer"
};

static const int DQUEERR_MAXERR = sizeof(emsg)/sizeof(char *); /* maximum error code */

dque_err                                    /* returned error code          */
dque_error(                                 /* build error msg from err     */
dque_err        err,                        /* error code                   */
char           *buf,                        /* buffer to hold error message */
unsigned int    siz )                       /* size of buf                  */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;

    if (err < 0) {                          /* it is OK to be negative      */
        err     = -err;
    }

    if (err >= DQUEERR_MAXERR) {            /* invalid error code?          */
        err     = DQUEERR_UNKERR;
    }

    if (buf == (char *)NULL) {              /* invalid input?               */
        errcode = DQUEERR_NOBUF;
    } else if (siz == 0) {
        errcode = DQUEERR_BUFSIZE;
    } else {
        (void) strncpy( buf, emsg[err], siz );
    }

    return (errcode);
}

dque_err                                    /* returned error code          */
dque_error_len(                             /* return size of err message   */
dque_err        err,                        /* error code                   */
unsigned int   *len )                       /* returned length of message   */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;

    if (err < 0) {                          /* it is OK to be negative      */
        err     = -err;
    }

    if (len == (unsigned int *)NULL) {      /* invalid pointer to data      */
        errcode = DQUEERR_NODATA;
    } else if (err >= DQUEERR_MAXERR) {     /* invalid error code?          */
        errcode = DQUEERR_UNKERR;
	*len    = 0;
    } else {
    	*len    = strlen( emsg[err] );
    }

    return (errcode);
}

