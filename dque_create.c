#include <stdio.h>                          /* need NULL definition         */
#include <stdlib.h>                         /* need for malloc and free     */
#include "mydque.h"
#include "dque.h"

dque_err static                             /* returned completion status   */
dque_populate_head(                         /* internal helper function     */
dque_qhead     *queue )                     /* pointer to queue             */
{
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */

    setvers( queue, DQUE_VERSION );         /* library version number       */
    setflgs( queue, DQUE_NOFLAGS );         /* library operation flags      */
    sethead( queue, NULL_NODE    );         /* NULL head queue              */
    setfree( queue, NULL_NODE    );         /* NULL free list               */
    setblks( queue, NULL_NODE    );         /* NULL allocation blocks list  */
    sethcnt( queue, 0            );         /* current # nodes on head queue*/
    setfcnt( queue, 0            );         /* current # nodes on free list */
    setbcnt( queue, 0            );         /* current # nodes on blks list */
    setacnt( queue, DQUE_NODECNT );         /* default node count allocation*/

    return (errcode);
}

dque_err                                    /* returned completion status   */
dque_create(                                /* create a queue               */
dque_qheadp    *queuep,                     /* ptr to ptr to queue          */
unsigned int    siz,                        /* size of the buffer           */   
char           *buf )                       /* ptr to buffer to use for head*/
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qhead     *queue   = NULL_QUEUE;
    unsigned        cnt;

    if (queuep == NULL_QUEUEP) {            /* invalid queue head pointer?  */
        errcode = DQUEERR_NOQUEUEP;
    } else if (siz == 0) {                  /* use dynamic memory allocation? */
        if ((queue = (dque_qhead *)malloc( sizeof(dque_qhead) )) == NULL_QUEUE) {
	    errcode = DQUEERR_NOALLOC;      /* queue head allocation fail?  */
        } else if ((errcode = dque_populate_head( queue )) == DQUEERR_NOERR) {
            *queuep = queue;
        }
    } else {                                /* do not use dynamic memory    */
        if (siz < sizeof(dque_qhead)) {     /* buffer size too small?       */
            errcode = DQUEERR_BUFSIZE;
        } else if (buf == (char *)NULL) {   /* invalid buffer pointer?      */
            errcode = DQUEERR_NOBUF;
        } else {
            queue   = (dque_qhead *)buf;    /* point queue to new queue head*/
            buf    += sizeof(dque_qhead);   /* move pointer past new qhead  */
            siz    -= sizeof(dque_qhead);     /* remove qhead size from buf size */
            cnt     = siz/sizeof(dque_qnode); /* convert buf size to qnode count */
            if ((errcode = dque_populate_head( queue )) == DQUEERR_NOERR) {
                setflag( queue, DQUE_NOALLOC );
            }
            *queuep = queue;                /* qhead valid at this point    */
            if (cnt != 0) {                 /* need to allocate nodes?      */  
                if (cnt < (unsigned int)DQUE_MINCNT) { /* invalid node cnt?*/
                    errcode = DQUEERR_MINCNT;
                } else {                    /* cnt valid, create nodes      */
                    errcode = dque_mypopulate( queue, cnt, (dque_qnode *)buf );
                }
            }
        }
    }

    return (errcode);
}

