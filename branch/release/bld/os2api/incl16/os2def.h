/*
    OS/2 typedefs and constants for 16-bit development.
*/

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(M_I86SM) || defined(M_I86MM))
#define NULL   0
#else
#define NULL   0L
#endif

#define FAR     _far
#define NEAR    _near
#define PASCAL  _pascal
#define VOID    void

#define EXPENTRY  PASCAL FAR _loadds
#define APIENTRY  PASCAL FAR
#define CALLBACK  EXPENTRY

#define CHAR     char
#define SHORT    short
#define LONG     long
#define INT      int

typedef unsigned char   UCHAR;
typedef unsigned char   BYTE;
typedef unsigned short  USHORT;
typedef unsigned int    UINT;
typedef unsigned long   ULONG;

typedef unsigned short  SHANDLE;
typedef void FAR        *LHANDLE;

typedef SHANDLE    HFILE;
typedef HFILE FAR  *PHFILE;

typedef unsigned char FAR   *PSZ;
typedef unsigned char NEAR  *NPSZ;

typedef unsigned char FAR   *PCH;
typedef unsigned char NEAR  *NPCH;

typedef unsigned short  BOOL;
typedef BOOL FAR        *PBOOL;

#ifndef TRUE
#define TRUE   1
#endif

#ifndef FALSE
#define FALSE  0
#endif

#define MAKEP(sel, off)  ((PVOID)MAKEULONG(off, sel))

#define SELECTOROF(p)    (((PUSHORT)&(p))[1])
#define OFFSETOF(p)      (((PUSHORT)&(p))[0])

#define MAKETYPE(v, type) (*((type far *)&v))

#define FIELDOFFSET(type, field) ((SHORT)&(((type *)0)->field))

#define MAKEULONG(l, h)  ((ULONG)(((USHORT)(l)) | ((ULONG)((USHORT)(h))) << 16))
#define MAKELONG(l, h)   ((LONG)MAKEULONG(l, h))
#define MAKEUSHORT(l, h) (((USHORT)(l)) | ((USHORT)(h)) << 8)

#define LOUCHAR(w)  ((UCHAR)(w))
#define HIUCHAR(w)  ((UCHAR)(((USHORT)(w) >> 8) & 0xff))
#define LOUSHORT(l) ((USHORT)(l))
#define HIUCHAR(w)  ((UCHAR)(((USHORT)(w) >> 8) & 0xff))
#define HIUSHORT(l) ((USHORT)(((ULONG)(l) >> 16) & 0xffff))

typedef CHAR FAR     *PCHAR;
typedef SHORT FAR    *PSHORT;
typedef INT FAR      *PINT;
typedef LONG FAR     *PLONG;
typedef UCHAR FAR    *PUCHAR;
typedef UCHAR FAR    *PBYTE;
typedef USHORT FAR   *PUSHORT;
typedef UINT FAR     *PUINT;
typedef ULONG FAR    *PULONG;

typedef VOID FAR     *PVOID;

typedef int (PASCAL FAR  *PFN)();
typedef int (PASCAL NEAR *NPFN)();
typedef PFN FAR *PPFN;

typedef USHORT       SEL;
typedef SEL FAR      *PSEL;

typedef USHORT       HMODULE;
typedef HMODULE FAR  *PHMODULE;
typedef USHORT       PID;
typedef PID FAR      *PPID;
typedef USHORT       TID;
typedef TID FAR      *PTID;
typedef VOID FAR     *HSEM;
typedef HSEM FAR     *PHSEM;

typedef LHANDLE   HPS, FAR *PHPS;
typedef LHANDLE   HDC, FAR *PHDC;
typedef LHANDLE   HRGN, FAR *PHRGN;
typedef LHANDLE   HBITMAP, FAR *PHBITMAP;
typedef LHANDLE   HMF, FAR *PHMF;
typedef LONG      COLOR, FAR *PCOLOR;

typedef struct _POINTL {
    LONG x;
    LONG y;
} POINTL, FAR  *PPOINTL, NEAR *NPPOINTL;

typedef struct _POINTS {
    SHORT x;
    SHORT y;
} POINTS, FAR *PPOINTS;

typedef struct _RECTL {
    LONG xLeft;
    LONG yBottom;
    LONG xRight;
    LONG yTop;
} RECTL, FAR  *PRECTL, NEAR *NPRECTL;

typedef struct _WPOINT {
    SHORT x;
    SHORT dummy1;
    SHORT y;
    SHORT dummy2;
} WPOINT, FAR *PWPOINT, NEAR *NPWPOINT;

typedef struct _WRECT {
    SHORT xLeft;
    SHORT dummy1;
    SHORT yBottom;
    SHORT dummy2;
    SHORT xRight;
    SHORT dummy3;
    SHORT yTop;
    SHORT dummy4;
} WRECT, FAR *PWRECT, NEAR *NPWRECT;

typedef CHAR STR8[8], FAR *PSTR8;

typedef struct _DRIVDATA {
    LONG cb;
    LONG lVersion;
    CHAR szDeviceName[32];
    CHAR abGeneralData[1];
} DRIVDATA, FAR *PDRIVDATA;

#define FATTR_SEL_ITALIC            0x0001
#define FATTR_SEL_UNDERSCORE        0x0002
#define FATTR_SEL_OUTLINE           0x0008
#define FATTR_SEL_STRIKEOUT         0x0010
#define FATTR_SEL_BOLD              0x0020
#define FATTR_TYPE_KERNING          0x0004
#define FATTR_TYPE_MBCS             0x0008
#define FATTR_TYPE_DBCS             0x0010
#define FATTR_TYPE_ANTIALIASED      0x0020
#define FATTR_FONTUSE_NOMIX         0x0002
#define FATTR_FONTUSE_OUTLINE       0x0004
#define FATTR_FONTUSE_TRANSFORMABLE 0x0008

#define FACESIZE 32

typedef struct _FATTRS {
    USHORT usRecordLength;
    USHORT fsSelection;
    LONG   lMatch;
    CHAR   szFacename[FACESIZE];
    USHORT idRegistry;
    USHORT usCodePage;
    LONG   lMaxBaselineExt;
    LONG   lAveCharWidth;
    USHORT fsType;
    USHORT fsFontUse;
} FATTRS, FAR *PFATTRS;

#define FM_TYPE_FIXED     0x0001
#define FM_TYPE_LICENSED  0x0002
#define FM_TYPE_KERNING   0x0004
#define FM_TYPE_DBCS      0x0010
#define FM_TYPE_MBCS      0x0018
#define FM_TYPE_64K       0x8000
#define FM_DEFN_OUTLINE   0x0001
#define FM_DEFN_GENERIC   0x8000
#define FM_SEL_ITALIC     0x0001
#define FM_SEL_UNDERSCORE 0x0002
#define FM_SEL_NEGATIVE   0x0004
#define FM_SEL_OUTLINE    0x0008
#define FM_SEL_STRIKEOUT  0x0010
#define FM_SEL_BOLD       0x0020
#define FM_CAP_NOMIX      0x0001

typedef struct _FONTMETRICS {
    CHAR   szFamilyname[FACESIZE];
    CHAR   szFacename[FACESIZE];
    USHORT idRegistry;
    USHORT usCodePage;
    LONG   lEmHeight;
    LONG   lXHeight;
    LONG   lMaxAscender;
    LONG   lMaxDescender;
    LONG   lLowerCaseAscent;
    LONG   lLowerCaseDescent;
    LONG   lInternalLeading;
    LONG   lExternalLeading;
    LONG   lAveCharWidth;
    LONG   lMaxCharInc;
    LONG   lEmInc;
    LONG   lMaxBaselineExt;
    SHORT  sCharSlope;
    SHORT  sInlineDir;
    SHORT  sCharRot;
    USHORT usWeightClass;
    USHORT usWidthClass;
    SHORT  sXDeviceRes;
    SHORT  sYDeviceRes;
    SHORT  sFirstChar;
    SHORT  sLastChar;
    SHORT  sDefaultChar;
    SHORT  sBreakChar;
    SHORT  sNominalPointSize;
    SHORT  sMinimumPointSize;
    SHORT  sMaximumPointSize;
    USHORT fsType;
    USHORT fsDefn;
    USHORT fsSelection;
    USHORT fsCapabilities;
    LONG   lSubscriptXSize;
    LONG   lSubscriptYSize;
    LONG   lSubscriptXOffset;
    LONG   lSubscriptYOffset;
    LONG   lSuperscriptXSize;
    LONG   lSuperscriptYSize;
    LONG   lSuperscriptXOffset;
    LONG   lSuperscriptYOffset;
    LONG   lUnderscoreSize;
    LONG   lUnderscorePosition;
    LONG   lStrikeoutSize;
    LONG   lStrikeoutPosition;
    SHORT  sKerningPairs;
    SHORT  sFamilyClass;
    LONG   lMatch;
} FONTMETRICS, FAR *PFONTMETRICS;

#ifdef __cplusplus
}
#endif

