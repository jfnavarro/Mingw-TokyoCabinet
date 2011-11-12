#ifndef _MINGW32_WRAPPER_H                         /* duplication check */
#define _MINGW32_WRAPPER_H   

  #include <mman.h>
  #include <windows.h>
  #include <stdio.h>
  #include <psapi.h>
  #include <tchar.h>
  #include <stdint.h>
  #include <limits.h>
  #include <errno.h>
  #include <winsock2.h>
  #include <winbase.h>
  #define mkdir(N,P) _mkdir(N)
  #define _P_tmpdir   "\\"
  #define P_tmpdir _P_tmpdir
  #define _fileno(__F) ((__F)->_file)
  #define fsync(N) _commit(N)
  #ifdef __USE_BSD
    #if defined __GNUC__ && !defined __cplusplus
      #define __WAIT_INT(status)                 \
      (__extension__ ({ union { __typeof(status) __in; int __i; } __u;        \
        __u.__in = (status); __u.__i; }))
    #else
      #define __WAIT_INT(status) (*(int *) &(status))
    #endif
    #if !defined __GNUC__ || __GNUC__ < 2 || defined __cplusplus
      #define __WAIT_STATUS  void *
      #define __WAIT_STATUS_DEFN void *
    #else
      /* This works in GCC 2.6.1 and later.  */
      typedef union
      {
	union wait *__uptr;
	int *__iptr;
      } __WAIT_STATUS __attribute__ ((__transparent_union__));
      #define __WAIT_STATUS_DEFN int *
    #endif
  #else /* Don't use BSD.  */
    #define __WAIT_INT(status)  (status)
    #define __WAIT_STATUS   int *
    #define __WAIT_STATUS_DEFN  int *
  #endif /* Use BSD.  */
  #ifndef WTERMSIG
    #ifdef HAVE_TYPE_UNIONWAIT
      #define	WTERMSIG(status)	SIGTERM
    #else
      #define	WTERMSIG(status)	((status) & 0x7f)
    #endif
  #endif
  #define __WEXITSTATUS(status) (((status) & 0xff00) >> 8)
  #define __WIFEXITED(status) (WTERMSIG(status) == 0)
  #define WIFEXITED(status) __WIFEXITED (__WAIT_INT (status))
  #define WEXITSTATUS(status) __WEXITSTATUS (__WAIT_INT (status))
  #define lstat(N,P) stat(N,P) 
  char *realpath(const char *path, char resolved_path[PATH_MAX]);
  /* getpagesize for windows */
  long getpagesize (void); 
  /* For posix fcntl() and `l_type' field of a `struct flock' for lockf().  */
  int pread(unsigned int fd, char *buf, size_t count, int offset);
  /* Pread simple implementation for windows */
  int pwrite(int fd, const void *buf, size_t nbytes, off_t offset);
  /* Pwrite simple implementation for windows */

  #define F_RDLCK		0	/* Read lock.  */
  #define F_WRLCK		1	/* Write lock.	*/
  #define F_UNLCK		2	/* Remove lock.	 */
  #define F_GETLK		5	/* Get record locking info.  */
  #define F_SETLK		6	/* Set record locking info (non-blocking).  */
  #define F_SETLKW		7	/* Set record locking info (blocking).	*/
  #ifdef _LARGEFILE64_SOURCE
      #ifdef _LP64
	  typedef off_t off64_t;
      #else
	  typedef LONGLONG off64_t;  
      #endif 
  #endif
  typedef int pid_t;
  typedef  off_t __off_t;
  typedef  off64_t __off64_t;
  #ifndef __pid_t_defined
    typedef  pid_t __pid_t;
    #define __pid_t_defined
  #endif
  struct flock
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
    #ifndef __USE_FILE_OFFSET64
      __off_t l_start;	/* Offset where the lock begins.  */
      __off_t l_len;	/* Size of the locked area; zero means until EOF.  */
    #else
      __off64_t l_start;	/* Offset where the lock begins.  */
      __off64_t l_len;	/* Size of the locked area; zero means until EOF.  */
    #endif
      __pid_t l_pid;	/* Process holding the lock.  */
  };
  #ifndef _SYS_TIMES_H
  #ifdef __cpluscplus
    extern "C" {
    #endif
    #define _SYS_TIMES_H 1
    #define __need_clock_t
  
    /* Structure describing CPU time used by a process and its children.  */
    struct tms
    {
      clock_t tms_utime;		/* User CPU time.  */
      clock_t tms_stime;		/* System CPU time.  */

      clock_t tms_cutime;		/* User CPU time of dead children.  */
      clock_t tms_cstime;		/* System CPU time of dead children.  */
    };


    /* Store the CPU time used by this process and all its
    dead children (and their dead children) in BUFFER.
    Return the elapsed real time, or (clock_t) -1 for errors.
    All times are in CLK_TCKths of a second.  */
    extern clock_t times (struct tms *__buffer);	
    #ifdef __cpluscplus
    }
    #endif
  #endif
#endif