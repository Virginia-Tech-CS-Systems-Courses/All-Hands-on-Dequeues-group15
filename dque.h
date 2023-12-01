#ifndef DQUE_H
#define DQUE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DQUE_QHEAD_DEF
typedef struct dque_qhead { int type; } dque_qhead, *dque_qheadp, **dque_qheadpp;
#endif

#ifndef NULL_QUEUE
#define NULL_QUEUE      (dque_qhead *)NULL  /* a NULL queue pointer         */
#define NULL_QUEUEP     (dque_qhead **)NULL
#endif

#ifndef DQUE_QITER_DEF
typedef struct dque_qiter { int type; } dque_qiter, *dque_qiterp, **dque_qiterpp;
#endif

#ifndef NULL_QITER
#define NULL_QITER      (dque_qiter *)NULL  /* a NULL qiter pointer         */
#define NULL_QITERP     (dque_qiter **)NULL
#endif

#ifndef COMFUNC_DEF
typedef int (* COMPFUNC)( void *, void * );
#endif

#ifndef DQUE_ERR_DEF
/* error numbers deliberately not defined here. */
typedef enum dque_err {
        DQUEERR_NOERR       =  0,
        DQUEERR_UNKERR      =  1,
        DQUEERR_NOALLOC     =  2,
        DQUEERR_NOQUEUE     =  3,
        DQUEERR_NOQUEUEP    =  4,
        DQUEERR_NODATA      =  5,
        DQUEERR_NODATAP     =  6,
        DQUEERR_NOITER      =  7,
        DQUEERR_NOITERP     =  8,
        DQUEERR_BUFSIZE     =  9,
        DQUEERR_MINCNT      = 10,
        DQUEERR_EMPTY       = 11,
        DQUEERR_NOKEY       = 12,
        DQUEERR_NOCOMP      = 13,
        DQUEERR_ALLOCNA     = 14,
        DQUEERR_NOTFOUND    = 15,
        DQUEERR_UNKOPT      = 16,
        DQUEERR_NODUPE      = 17,
        DQUEERR_INVITER     = 18,
        DQUEERR_NOBUF       = 19,
        DQUEERR_INVHDR      = 20
	} dque_err;
#endif

/* member functions */
extern dque_err dque_create(    dque_qhead **, unsigned int,     char *        );
extern dque_err dque_destroy(   dque_qhead **                                  );
extern dque_err dque_error(     dque_err,      char  *,          unsigned int  );
extern dque_err dque_error_len( dque_err,                        unsigned int *);
extern dque_err dque_options(   dque_qhead *,  int, ...                        );

/* capacity */
extern dque_err dque_empty(     dque_qhead *,  unsigned int *                  );
extern dque_err dque_size(      dque_qhead *,  unsigned int *                  );
extern dque_err dque_max_size(  dque_qhead *,  unsigned int *                  );

/* element access */
extern dque_err dque_back(      dque_qhead *,  void **                         );
extern dque_err dque_front(     dque_qhead *,  void **                         );
extern dque_err dque_key_find(  dque_qhead *,  void *, COMPFUNC, dque_qiter ** );
extern dque_err dque_get_data(  dque_qiter *,  void **                         );
extern dque_err dque_set_data(  dque_qiter *,  void *                          );

/* iterators */
extern dque_err dque_begin(     dque_qhead *,                    dque_qiter ** );
extern dque_err dque_rbegin(    dque_qhead *,                    dque_qiter ** );
extern dque_err dque_next(      dque_qhead *,                    dque_qiter ** );
extern dque_err dque_rnext(     dque_qhead *,                    dque_qiter ** );
extern dque_err dque_end(       dque_qhead *,                    dque_qiter ** );
extern dque_err dque_rend(      dque_qhead *,                    dque_qiter ** );

/* modifiers */
extern dque_err dque_erase(     dque_qhead *,  void **,          dque_qiter *  );
extern dque_err dque_insert(    dque_qhead *,  void *,           dque_qiter *  );
extern dque_err dque_key_erase( dque_qhead *,  void *, COMPFUNC, void **       );
extern dque_err dque_key_insert(dque_qhead *,  void *, COMPFUNC, void *        );
extern dque_err dque_pop_back(  dque_qhead *,  void **                         );
extern dque_err dque_pop_front( dque_qhead *,  void **                         );
extern dque_err dque_push_back( dque_qhead *,  void *                          );
extern dque_err dque_push_front(dque_qhead *,  void *                          );

/* dque options                                                             */
#define DQUEOPT_NOOPT       0
#define DQUEOPT_VERSION     1
#define DQUEOPT_NODECNT     2
#define DQUEOPT_HEADSIZ     3
#define DQUEOPT_NODESIZ     4
#define DQUEOPT_NOALLOC     5
#define DQUEOPT_NODUPE      6
#define DQUEOPT_NOSCAN      7

/* short forms of the function names if INSERT_DEF is not defined           */

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L))    /* conforms to C11 standard? */
    #define create(X,b,c)       _Generic ((X),                      \
				        dque_qheadpp: dque_create   \
				        ) (X,b,c)
    #define destroy(X)          _Generic ((X),                      \
				        dque_qheadpp: dque_destroy  \
				        ) (X)
    #define error(X,b,c)        _Generic ((X),                      \
				        dque_err: dque_error        \
				        ) (X,b,c)
    #define error_len(X,b)      _Generic ((X),                      \
				        dque_err: dque_error_len    \
				        ) (X,b)
    #define options(X,b, ...)   _Generic ((X),                      \
				        dque_qheadp: dque_options   \
				        ) (X,b, __VA_ARGS__)
    #define empty(X,b)          _Generic ((X),                      \
				        dque_qheadp: dque_empty     \
				        ) (X,b)
    #define size(X,b)           _Generic ((X),                      \
				        dque_qheadp: dque_size      \
				        ) (X,b)
    #define max_size(X,b)       _Generic ((X),                      \
				        dque_qheadp: dque_max_size  \
				        ) (X,b)
    #define back(X,b)           _Generic ((X),                      \
				        dque_qheadp: dque_back      \
				        ) (X,b)
    #define front(X,b)          _Generic ((X),                      \
				        dque_qheadp: dque_front     \
				        ) (X,b)
    #define key_find(X,b,c,d)   _Generic ((X),                      \
				        dque_qheadp: dque_key_find  \
				        ) (X,b,c,d)
    #define get_data(X,b)       _Generic ((X),                      \
				        dque_qiterp: dque_get_data  \
				        ) (X,b)
    #define set_data(X,b)       _Generic ((X),                      \
				        dque_qiterp: dque_set_data  \
				        ) (X,b)
    #define begin(X,b)          _Generic ((X),                      \
				        dque_qheadp: dque_begin     \
				        ) (X,b)
    #define rbegin(X,b)         _Generic ((X),                      \
				        dque_qheadp: dque_rbegin    \
				        ) (X,b)
    #define next(X,b)           _Generic ((X),                      \
				        dque_qheadp: dque_next      \
				        ) (X,b)
    #define rnext(X,b)          _Generic ((X),                      \
				        dque_qheadp: dque_rnext     \
				        ) (X,b)
    #define end(X,b)            _Generic ((X),                      \
			 	        dque_qheadp: dque_end       \
				        ) (X,b)
    #define rend(X,b)           _Generic ((X),                      \
				        dque_qheadp: dque_rend      \
				        ) (X,b)
    #define erase(X,b,c)        _Generic ((X),                      \
				        dque_qheadp: dque_erase     \
				        ) (X,b,c)
    #define insert(X,b,c)       _Generic ((X),                      \
				        dque_qheadp: dque_insert    \
				        ) (X,b,c)
    #define key_erase(X,b,c,d)  _Generic ((X),                      \
				        dque_qheadp: dque_key_erase \
				        ) (X,b,c,d)
    #define key_insert(X,b,c,d) _Generic ((X),                      \
				        dque_qheadp: dque_key_insert\
				        ) (X,b,c,d)
    #define pop_back(X,b)       _Generic ((X),                      \
				        dque_qheadp: dque_pop_back  \
				        ) (X,b)
    #define pop_front(X,b)      _Generic ((X),                      \
				        dque_qheadp: dque_pop_front \
				        ) (X,b)
    #define push_back(X,b)      _Generic ((X),                      \
				        dque_qheadp: dque_push_back \
				        ) (X,b)
    #define push_front(X,b)     _Generic ((X),                      \
				        dque_qheadp: dque_push_front\
				        ) (X,b)
    #ifndef __cplusplus
      #define delete(X,b,c)       _Generic ((X),                      \
	  			          dque_qheadp: dque_erase     \
				          ) (X,b,c)
      #define key_delete(X,b,c,d) _Generic ((X),                      \
				          dque_qheadp: dque_erase     \
				          ) (X,b,c,d)
    #endif

#else	/* compiler does not conform to C11 standard */

    #ifndef DQUE_LIB
    #define DQUE_LIB            1
    #endif

    #ifndef INSERT_DEF
    #define INSERT_DEF          DQUE_LIB
    #endif

    #if INSERT_DEF == DQUE_LIB
      /* member functions */
      #define create(a,b,c)       dque_create(a,b,c)
      #define destroy(a)          dque_destroy(a)
      #define error(a,b,c)        dque_error(a,b,c)
      #define error_len(a,b)      dque_error_len(a,b)
      #if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) /* conforms to C99 standard? */
        #define options(a,b, ...)   dque_options(a,b, __VA_ARGS__)
      #else
        #define options           dque_options
      #endif
      /* capacity */
      #define empty(a,b)          dque_empty(a,b)
      #define size(a,b)           dque_size(a,b)
      #define max_size(a,b)       dque_max_size(a,b)
      /* element access */
      #define back(a,b)           dque_back(a,b)
      #define front(a,b)          dque_front(a,b)
      #define key_find(a,b,c,d)   dque_key_find(a,b,c,d)
      #define get_data(a,b)       dque_get_data(a,b)
      #define set_data(a,b)       dque_set_data(a,b)
      /* iterators */
      #define begin(a,b)          dque_begin(a,b)
      #define rbegin(a,b)         dque_rbegin(a,b)
      #define next(a,b)           dque_next(a,b)
      #define rnext(a,b)          dque_rnext(a,b)
      #define end(a,b)            dque_end(a,b)
      #define rend(a,b)           dque_rend(a,b)
      /* Modifiers */
      #define erase(a,b,c)        dque_erase(a,b,c)
      #define insert(a,b,c)       dque_insert(a,b,c)
      #define key_erase(a,b,c,d)  dque_key_erase(a,b,c,d)
      #define key_insert(a,b,c,d) dque_key_insert(a,b,c,d)
      #define pop_back(a,b)       dque_pop_back(a,b)
      #define pop_front(a,b)      dque_pop_front(a,b)
      #define push_back(a,b)      dque_push_back(a,b)
      #define push_front(a,b)     dque_push_front(a,b)
      #ifndef __cplusplus
        #define delete(a,b,c)       dque_erase(a,b,c)
        #define key_delete(a,b,c,d) dque_key_erase(a,b,c,d)
      #endif                                /* __cplusplus                  */
    #endif                                  /* INSERT_DEF == DQUE_LIB       */
#endif                                      /* ifndef __STDC_VERSION__      */

#ifdef __cplusplus
}
#endif

#endif /* DQUE_H */
