
#include <stdio.h>                          /* need NULL definition         */
#include <stdarg.h>                         /* need for variadic arguments  */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned status              */
dque_options(                               /* get/set queue option         */
dque_qhead     *queue,                      /* queue to count nodes         */
int             opt,                        /* get/set option               */
                ... )                       /* option arguments             */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    int             *major, *minor;
    unsigned int    siz, *val;
    char           *buf;
    va_list         args;

    if (queue == NULL_QUEUE && !(opt == DQUEOPT_HEADSIZ || opt == DQUEOPT_NODESIZ) ) {
        errcode = DQUEERR_NOQUEUE;          /* if opt not head size, invalid queue? */
    } else {
        va_start( args, opt );
	switch (opt) {
            case DQUEOPT_NOOPT:             /* no operation, couldn't resist*/
                break;
	    case DQUEOPT_VERSION:
                major   = va_arg( args, int * );
                minor   = va_arg( args, int * );
               *major   = (getvers( queue ) >> 16) & 0x0000FFFF;
               *minor   =  getvers( queue )        & 0x0000FFFF;
                break;
            case DQUEOPT_NODECNT:           /* # nodes to allocate each time*/
		siz = va_arg( args, unsigned int );
                if (siz < (unsigned int)DQUE_MINCNT) {
                    errcode = DQUEERR_MINCNT;   /* siz not => minimum size? */
                } else {
                    setacnt( queue, siz );  /* valid node count size, set it*/
                }
                break;
            case DQUEOPT_HEADSIZ:           /* returns size of queue head   */
                val     = va_arg( args, unsigned int * );
                *val    = sizeof( dque_qhead );
                break;
            case DQUEOPT_NODESIZ:           /* returns size of queue node   */
                val     = va_arg( args, unsigned int * );
                *val    = sizeof( dque_qnode );
                break;
	    case DQUEOPT_NOALLOC:       /* siz is size of buf, need # nodes */
                siz = va_arg( args, unsigned int ) / sizeof(dque_qnode);
                buf = va_arg( args, char * );
                if (getflag( queue, DQUE_NOALLOC ) == 0) {
                    errcode = DQUEERR_ALLOCNA;
                } else if (siz < (unsigned int)DQUE_MINCNT) {
                    errcode = DQUEERR_MINCNT;   /* siz not => minimum size? */
                } else if ((errcode = dque_mypopulate( queue, siz, (dque_qnode *)buf )) == DQUEERR_NOERR) {
                    setflag( queue, DQUE_NOALLOC );
                }
                break;
            case DQUEOPT_NODUPE:        /* !0 = no duplicates in priority queue, 0 = allow duplicates  */
                siz     = va_arg( args, unsigned int ); /* siz == a boolean  */
                setflag( queue, ((siz != 0) ? DQUE_NODUPE : 0) );
                break;
            case DQUEOPT_NOSCAN:        /* !0 = no scan on insert, remove, 0 = scan before insert,remove  */
                siz     = va_arg( args, unsigned int ); /* siz == a boolean  */
                setflag( queue, ((siz != 0) ? DQUE_NOSCAN : 0) );
                break;
            default:
                errcode = DQUEERR_UNKOPT;
                break;
            }
        va_end( args );
        }

    return (errcode);
}

