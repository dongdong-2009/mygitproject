#ifndef _Boon_ALGO_UNZIP_PRIVATE_H_
#define _Boon_ALGO_UNZIP_PRIVATE_H_


#include "Boon_algo_unzipmem.h"


#ifdef __cplusplus
extern "C"      //声明对分割模块的调用接口为C形式
{
#endif
	typedef char *   voidp;
	typedef unsigned char  uch;
	typedef unsigned short ush;
	typedef unsigned int  ulg;
#define OF(args)  args
#define memzero(s, n)     memset ((voidp)(s), 0, (n))
	/* Compression methods (see algorithm.doc) */
#define STORED      0 /* stored */
#define COMPRESSED  1 /* compressed */
#define PACKED      2 /* packed */
#define LZHED       3 /* lzwed */
	/* methods 4 to 7 reserved */
#define DEFLATED    8 /* 缺省 */
#define MAX_METHODS 9 /* 最大化压缩 */


#define INBUFSIZ  0x8000  /* input buffer size */
#define INBUF_EXTRA  64     /* required by unlzw() */
#define OUTBUFSIZ   16384  /* output buffer size */
#define OUTBUF_EXTRA 2048   /* required by unlzw() */
#define DIST_BUFSIZE 0x8000 /* buffer for distances, see trees.c */
#define EXTERN(type, array)  extern type *  array
#define DECLARE(type, array, size)  type *  array



#define fcalloc(segment, items, size)    Public_Calloc(segment, (size_t)(items)*(size_t)(size), 8)
#define fcfree(segment, array, items, size)   Public_Free(segment, array, (size_t)(items)*(size_t)(size))

#define ALLOC(segment, type, array, size) { \
	array = (type*)fcalloc(segment, (size_t)(((size)+1L)/2), 2*sizeof(type)); \
	if (array == NULL) return  0; \
	}

#define FREE(segment,type, array, size) { \
	if (array != NULL) {fcfree(segment, array, (size_t)(((size)+1L)/2), 2*sizeof(type)); array=NULL;} \
	}


	EXTERN( uch, inbuf );          /* input buffer */
	EXTERN( uch, outbuf );         /* output buffer */
	EXTERN( ush, d_buf );          /* buffer for distances, see trees.c */
	EXTERN( uch, window );         /* Sliding window and suffix table (unlzw) */
#define tab_suffix window
#define tab_prefix prev    /* hash link (see deflate.c) */
#define head (prev+WSIZE)  /* hash head (see deflate.c) */
	EXTERN( ush, tab_prefix );  /* prefix code (see unlzw.c) */

	extern unsigned insize; /* valid bytes in inbuf */
	extern unsigned inptr;  /* index of next byte to be processed in inbuf */
	extern unsigned outcnt; /* bytes in output buffer */

	extern int bytes_in;   /* number of input bytes */
	extern int bytes_out;  /* number of output bytes */
	extern int header_bytes;/* number of bytes in gzip header */

#define isize bytes_in
	/* for compatibility with old zip sources (to be cleaned) */
	extern int method;         /* compression method */

#define PACK_MAGIC     "\037\036" /* Magic header for packed files */
#define GZIP_MAGIC     "\037\213" /* Magic header for gzip files, 1F 8B */
#define OLD_GZIP_MAGIC "\037\236" /* Magic header for gzip 0.5 = freeze 1.x */
#define LZH_MAGIC      "\037\240" /* Magic header for SCO LZH Compress files*/
#define PKZIP_MAGIC    "\120\113\003\004" /* Magic header for pkzip files */

	/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
	//#define RESERVED     0xC0 /* bit 6,7:   reserved */
#define BOON       0x40
	/* internal file attribute */
#define UNKNOWN 0xffff /* 未知 */
#define BINARY  0 /* binary */
#define ASCII   1 /* ascII */

#ifndef WSIZE
#define WSIZE 0x8000     /* window size--must be a power of two, and */
#endif                     /*  at least 32K for zip's deflate method */

#define MIN_MATCH  3 /* min match */
#define MAX_MATCH  258 /* max match*/
	/* The minimum and maximum match lengths */

#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
	/* Minimum amount of lookahead, except at the end of the input file.
	* See deflate.c for comments aBoonut the MIN_MATCH+1.
	*/

#define MAX_DIST  (WSIZE-MIN_LOOKAHEAD)
	/* In order to simplify the code, particularly on 16 bit machines, match
	* distances are limited to MAX_DIST instead of WSIZE.
	*/

	extern int quiet;          /* be quiet (-q) */
	extern int level;          /* compression level */

#define get_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf(0))

	/* Macros for getting two-byte and four-byte header values */
#define SH(p) ((ush)(uch)((p)[0]) | ((ush)(uch)((p)[1]) << 8))
	/* Macros for getting two-byte and four-byte header values */
#define LG(p) ((ulg)(SH(p)) | ((ulg)(SH((p)+2)) << 16))

	/* Diagnostic functions */
#define Assert(cond,msg)
#define Trace(x)
#define Tracev(x)
#define Tracevv(x)
#define Tracec(c,x)
#define Tracecv(c,x)

	extern unsigned char * zip_mem_outptr ;
	extern int zip_mem_outlen;
	extern unsigned char * unzip_mem_inptr ;
	extern int unzip_mem_insize ;
	extern int unzip_mem_inpos;

#ifndef BITS
#define BITS 16 /* bits len */
#endif

#define INIT_BITS 9              /* Initial number of bits per code */
#define LZW_MAGIC  "\037\235"   /* Magic header for lzw files, 1F 9D */
#define BIT_MASK    0x1f /* Mask for 'number of compression bits' */
#define BLOCK_MODE  0x80 
#define LZW_RESERVED 0x60 /* reserved bits */
#define CLEAR  256       /* flush the dictionary */
#define FIRST  ( CLEAR + 1 ) /* first free entry */

#ifdef __cplusplus
}
#endif

#endif  