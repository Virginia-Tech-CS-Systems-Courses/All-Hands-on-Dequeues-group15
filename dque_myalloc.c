
#include <stdio.h>                          /* need NULL definition         */
#include <stdlib.h>                         /* need for malloc and free     */
#include "mydque.h"
#include "dque.h"

dque_err                                    /* returned completion status   */
dque_myalloc(                               /* internal qnode allocation    */
dque_qhead    *queue )                      /* pointer to queue head        */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    dque_qnode     *array;

    if (getflag( queue, DQUE_NOALLOC ) != 0) {
        errcode = DQUEERR_ALLOCNA;          /* allowed to allocate memory?  */
    } else if ((array = (dque_qnode *)malloc( getacnt(queue) * sizeof(dque_qnode) )) == NULL_NODE) {
        errcode = DQUEERR_NOALLOC;          /* memory allocation fail?      */
    } else if ((errcode = dque_myinsert( &getblks( queue ), &array[0], NOROTATE, &getbcnt( queue ) )) == DQUEERR_NOERR) {
        errcode = dque_mypopulate( queue, getacnt(queue)-1, &array[1] );   /* save first node to free allocation later */
    }                                                                      /* put the remaining nodes on the free list */

    return (errcode);
}

dque_err                                    /* returned completion status   */
dque_mypopulate(                            /* internal qnode population    */
dque_qhead    *queue,                       /* pointer to queue head        */
unsigned int   cnt,                         /* number of qnodes to populate */
dque_qnode    *array )                      /* array of qnodes              */
{                                           /*------------------------------*/
    dque_err        errcode = DQUEERR_NOERR;/* non-zero indicates failure   */
    int             i;

    for (i = 0; i < cnt; ++i) {             /* put remaining nodes on free list */
        setdata( &array[i], (void *)NULL ); /* set data to null to show invalid qnode */
        if ((errcode = dque_myinsert( &getfree( queue ), &array[i], NOROTATE, &getfcnt( queue ) )) != DQUEERR_NOERR) {
            break;
        }
    }

    return (errcode);
}

