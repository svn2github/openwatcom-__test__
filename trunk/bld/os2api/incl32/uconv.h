/*
    Unicode Conversions
*/

#ifndef _ULS_UCONV
#define _ULS_UCONV
#include <unidef.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ULS_UCONVP
  #define _ULS_UCONVP
  typedef void *UconvObject;
#endif

#ifndef _ULS_UNICHAR_DEFINED
  #define _ULS_UNICHAR_DEFINED
  typedef unsigned short UniChar;
#endif

#define uconv_error_t int

#define UCONV_EOTHER           ULS_OTHER
#define UCONV_EILSEQ           ULS_ILLEGALSEQUENCE
#define UCONV_EINVAL           ULS_INVALID
#define UCONV_E2BIG            ULS_BUFFERFULL
#define UCONV_ENOMEM           ULS_NOMEMORY
#define UCONV_EBADF            ULS_BADOBJECT
#define UCONV_BADATTR          ULS_BADATTR
#define UCONV_EMFILE           ULS_MAXFILESPERPROC
#define UCONV_ENFILE           ULS_MAXFILES
#define UCONV_NOTIMPLEMENTED   ULS_NOTIMPLEMENTED

#define IBM_437   (UniChar *)L"IBM-437"
#define IBM_819   (UniChar *)L"IBM-819"
#define IBM_850   (UniChar *)L"IBM-850"
#define UTF_8     (UniChar *)L"IBM-1208"
#define UCS_2     (UniChar *)L"IBM-1200"
#define ISO8859_1 (UniChar *)L"IBM-819"

#ifndef ULS_ATTR
#define ULS_ATTR

#define UCONV_OPTION_SUBSTITUTE_FROM_UNICODE  1
#define UCONV_OPTION_SUBSTITUTE_TO_UNICODE    2
#define UCONV_OPTION_SUBSTITUTE_BOTH          3

#define CVTTYPE_CTRL7F 1
#define CVTTYPE_CDRA   2
#define CVTTYPE_PATH   4

#define DSPMASK_DATA    0xffffffff
#define DSPMASK_DISPLAY 0x00000000
#define DSPMASK_TAB     0x00000200
#define DSPMASK_LF      0x00000400
#define DSPMASK_CR      0x00002000
#define DSPMASK_CRLF    0x00002400

enum uconv_esid {
    ESID_sbcs_data    = 0x2100,
    ESID_sbcs_pc      = 0x3100,
    ESID_sbcs_ebcdic  = 0x1100,
    ESID_sbcs_iso     = 0x4100,
    ESID_sbcs_windows = 0x4105,
    ESID_sbcs_alt     = 0xF100,
    ESID_dbcs_data    = 0x2200,
    ESID_dbcs_pc      = 0x3200,
    ESID_dbcs_ebcdic  = 0x1200,
    ESID_mbcs_data    = 0x2300,
    ESID_mbcs_pc      = 0x3300,
    ESID_mbcs_ebcdic  = 0x1301,
    ESID_ucs_2        = 0x7200,
    ESID_ugl          = 0x72FF,
    ESID_utf_8        = 0x7807,
    ESID_upf_8        = 0x78FF
};

#ifndef __conv_endian_t
  #define __conv_endian_t

  #define ENDIAN_SYSTEM 0x0000
  #define ENDIAN_BIG    0xfeff
  #define ENDIAN_LITTLE 0xfffe

  typedef struct _conv_endian_rec {
      unsigned short source;
      unsigned short target;
  } conv_endian_t;
#endif

typedef struct _uconv_attribute_t {
    unsigned long  version;
    char           mb_min_len;
    char           mb_max_len;
    char           usc_min_len;
    char           usc_max_len;
    unsigned short esid;
    char           options;
    char           state;
    conv_endian_t  endian;
    unsigned long  displaymask;
    unsigned long  converttype;
    unsigned short subchar_len;
    unsigned short subuni_len;
    char           subchar[16];
    UniChar        subuni[8];
} uconv_attribute_t;

typedef struct {
    unsigned short first;
    unsigned short last;
} udcrange_t;

#endif

int CALLCONV UniCreateUconvObject(UniChar*,UconvObject*);
int CALLCONV UniFreeUconvObject(UconvObject);
int CALLCONV UniMapCpToUcsCp(unsigned long,UniChar*,size_t);
int CALLCONV UniQueryUconvObject(UconvObject,uconv_attribute_t*,size_t,char[256],char[256],udcrange_t[32]);
int CALLCONV UniSetUconvObject(UconvObject,uconv_attribute_t*);
int CALLCONV UniStrFromUcs(UconvObject,char*,UniChar*,int);
int CALLCONV UniStrToUcs(UconvObject,UniChar*,char*,int);
int CALLCONV UniUconvToUcs(UconvObject,void**,size_t*,UniChar**,size_t*,size_t*);
int CALLCONV UniUconvFromUcs(UconvObject,UniChar**,size_t*,void**,size_t*,size_t*);

#ifdef __cplusplus
}
#endif

#endif
