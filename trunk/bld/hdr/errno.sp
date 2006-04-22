#ifndef errno
_WCRTLINK extern int *__get_errno_ptr( void );
#define errno (*__get_errno_ptr())
#else
:: cannot be made volatile because users are allowed to
:: declare "extern int errno;" in their code in the presence
:: of <errno.h>
_WCRTLINKD extern int errno;
#endif
