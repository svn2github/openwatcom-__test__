/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  WHEN YOU FIGURE OUT WHAT THIS FILE DOES, PLEASE
*               DESCRIBE IT HERE!
*
****************************************************************************/


#include "variety.h"
#include <time.h>
#if defined(__QNX__)
#include <sys/types.h>
#include <sys/timers.h>
#elif defined(__LINUX__)
#include <sys/times.h>
#include <errno.h>
#endif
#include <rtinit.h>
#include "timedata.h"

#ifdef __LINUX__

_WCRTLINK clock_t clock(void)
{
    struct tms buf;
    int save_errno = errno;
    clock_t clk = times( &buf );
    errno = save_errno;
    return clk;
}

#else

#define MAX_CLOCK_T   ~((clock_t)0)
#define MAX_SECONDS   ((time_t)(MAX_CLOCK_T / CLOCKS_PER_SEC) - 1)

static clock_t init_milliseconds;
static time_t  init_seconds;

static void get_clock_time(time_t *secs, clock_t *milliseconds)
{
#if defined(__QNX__)
    struct timespec timer;

    getclock(TIMEOFDAY, &timer);
    *secs = (time_t)timer.tv_sec;
    *milliseconds = (clock_t)(timer.tv_nsec / (1000000000 / CLOCKS_PER_SEC));
#else
    struct tm t;

    *milliseconds = (clock_t)__getctime(&t);
    *secs = mktime(&t);
#endif
} /* get_clock_time() */

_WCRTLINK clock_t clock(void)
{
    time_t  new_seconds;
    clock_t ticks;

    /*
     * Get the change in seconds and milliseconds of seconds since startup.
     */
    get_clock_time(&new_seconds, &ticks);
    ticks       -= init_milliseconds;
    new_seconds -= init_seconds;

    /*
     * Make sure we won't overflow.
     */
    if (new_seconds > MAX_SECONDS)
        return -1;

    /*
     * `ticks' right now contains the number of milliseconds of seconds since
     * startup.  We still need to account for the number of full seconds that
     * may have passed.
     */
    ticks += (clock_t)(new_seconds * CLOCKS_PER_SEC);

    return ticks;
} /* clock() */

static void __clock_init(void)
{
    get_clock_time(&init_seconds, &init_milliseconds);
} /* __clock_init() */

/* Note: __clock_init() ends up calling tzset() which ends up querying the
 * TZ envirnment variable. Because getenv() access has also
 * INIT_PRIORITY_LIBRARY, we must make sure __clock_init() can't be executed
 * before the environment access is initialised!!   MN
 */
AXI( __clock_init, INIT_PRIORITY_LIBRARY + 1)

#endif
