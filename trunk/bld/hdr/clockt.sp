:: OpenWatcom only defines clock_t in time.h/ctime. However, the legacy
:: OW declaration was protected by an inclusion gaurd that defined the
:: symbol _CLOCK_T_DEFINED. This was done for compatibility with MS
:: Visual C. When I upgraded time.mh to support the generation of ctime,
:: I created this file. This complexity is technically unnecessary for
:: OpenWatcom, but this is the correct way to handle types defined with
:: inclusion gaurds. For consistency with size_t, time_t, and other similar
:: types, I felt it appropriate to configure clock_t in this way as well.
::
::Peter C. Chapin
::
:segment CNAME
#ifndef _STDCLOCK_T_DEFINED
#define _STDCLOCK_T_DEFINED
namespace std {
typedef unsigned long clock_t;
}
#endif
:elsesegment
#ifdef __cplusplus
#ifndef _STDCLOCK_T_DEFINED
#define _STDCLOCK_T_DEFINED
namespace std {
typedef unsigned long clock_t;
}
#endif
#ifndef _CLOCK_T_DEFINED
#define _CLOCK_T_DEFINED
using std::clock_t;
#endif
#else /* __cplusplus not defined */
#ifndef _CLOCK_T_DEFINED
#define _CLOCK_T_DEFINED
typedef unsigned long clock_t;
#endif
#endif /* __cplusplus */
:endsegment
