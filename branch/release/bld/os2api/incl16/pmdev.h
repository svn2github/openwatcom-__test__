/*
    OS/2 Presentation Manager device support include file for 16-bit development.
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef INCL_ERRORS
    #define INCL_DEVERRORS
#endif

#if defined(INCL_DEV) || !defined(INCL_NOCOMMON)

#define DEV_ERROR 0L
#define DEV_OK    1L

#define OD_QUEUED           2L
#define OD_DIRECT           5L
#define OD_INFO             6L
#define OD_METAFILE         7L
#define OD_MEMORY           8L
#define OD_METAFILE_NOQUERY 9L

#define CAPS_FAMILY                    0L
#define CAPS_IO_CAPS                   1L
#define CAPS_TECHNOLOGY                2L
#define CAPS_DRIVER_VERSION            3L
#define CAPS_WIDTH                     4L
#define CAPS_HEIGHT                    5L
#define CAPS_WIDTH_IN_CHARS            6L
#define CAPS_HEIGHT_IN_CHARS           7L
#define CAPS_HORIZONTAL_RESOLUTION     8L
#define CAPS_VERTICAL_RESOLUTION       9L
#define CAPS_CHAR_WIDTH               10L
#define CAPS_CHAR_HEIGHT              11L
#define CAPS_SMALL_CHAR_WIDTH         12L
#define CAPS_SMALL_CHAR_HEIGHT        13L
#define CAPS_COLORS                   14L
#define CAPS_COLOR_PLANES             15L
#define CAPS_COLOR_BITCOUNT           16L
#define CAPS_COLOR_TABLE_SUPPORT      17L
#define CAPS_MOUSE_BUTTONS            18L
#define CAPS_FOREGROUND_MIX_SUPPORT   19L
#define CAPS_BACKGROUND_MIX_SUPPORT   20L
#define CAPS_DEVICE_WINDOWING         31L
#define CAPS_ADDITIONAL_GRAPHICS      32L
#define CAPS_VIO_LOADABLE_FONTS       21L
#define CAPS_WINDOW_BYTE_ALIGNMENT    22L
#define CAPS_BITMAP_FORMATS           23L
#define CAPS_RASTER_CAPS              24L
#define CAPS_MARKER_HEIGHT            25L
#define CAPS_MARKER_WIDTH             26L
#define CAPS_DEVICE_FONTS             27L
#define CAPS_GRAPHICS_SUBSET          28L
#define CAPS_GRAPHICS_VERSION         29L
#define CAPS_GRAPHICS_VECTOR_SUBSET   30L
#define CAPS_PHYS_COLORS              33L
#define CAPS_COLOR_INDEX              34L
#define CAPS_GRAPHICS_CHAR_WIDTH      35L
#define CAPS_GRAPHICS_CHAR_HEIGHT     36L
#define CAPS_HORIZONTAL_FONT_RES      37L
#define CAPS_VERTICAL_FONT_RES        38L
#define CAPS_DEVICE_FONT_SIM          39L
#define CAPS_IO_DUMMY                  1L
#define CAPS_IO_SUPPORTS_OP            2L
#define CAPS_IO_SUPPORTS_IP            3L
#define CAPS_IO_SUPPORTS_IO            4L
#define CAPS_TECH_UNKNOWN              0L
#define CAPS_TECH_VECTOR_PLOTTER       1L
#define CAPS_TECH_RASTER_DISPLAY       2L
#define CAPS_TECH_RASTER_PRINTER       3L
#define CAPS_TECH_RASTER_CAMERA        4L
#define CAPS_TECH_POSTSCRIPT           5L
#define CAPS_COLTABL_RGB_8             1L
#define CAPS_COLTABL_RGB_8_PLUS        2L
#define CAPS_COLTABL_TRUE_MIX          4L
#define CAPS_COLTABL_REALIZE           8L
#define CAPS_FM_OR                     1L
#define CAPS_FM_OVERPAINT              2L
#define CAPS_FM_XOR                    8L
#define CAPS_FM_LEAVEALONE            16L
#define CAPS_FM_AND                   32L
#define CAPS_FM_GENERAL_BOOLEAN       64L
#define CAPS_BM_OR                     1L
#define CAPS_BM_OVERPAINT              2L
#define CAPS_BM_XOR                    8L
#define CAPS_BM_LEAVEALONE            16L
#define CAPS_DEV_WINDOWING_SUPPORT     1L
#define CAPS_GRAPHICS_KERNING_SUPPORT  2L
#define CAPS_FONT_OUTLINE_DEFAULT      4L
#define CAPS_FONT_IMAGE_DEFAULT        8L
#define CAPS_SCALED_DEFAULT_MARKERS   64L
#define CAPS_BYTE_ALIGN_REQUIRED       0L
#define CAPS_BYTE_ALIGN_RECOMMENDED    1L
#define CAPS_BYTE_ALIGN_NOT_REQUIRED   2L
#define CAPS_RASTER_BITBLT             1L
#define CAPS_RASTER_BANDING            2L
#define CAPS_RASTER_BITBLT_SCALING     4L
#define CAPS_RASTER_SET_PEL           16L
#define CAPS_RASTER_FONTS             32L

typedef PSZ FAR *PDEVOPENDATA;

HMF  APIENTRY DevCloseDC(HDC);
HDC  APIENTRY DevOpenDC(HAB,LONG,PSZ,LONG,PDEVOPENDATA,HDC);
BOOL APIENTRY DevQueryCaps(HDC,LONG,LONG,PLONG);

#endif

#ifdef INCL_DEV

#define DEVESC_ERROR         (-1L)
#define DEVESC_NOTIMPLEMENTED  0L

#define DEVESC_QUERYESCSUPPORT      0L
#define DEVESC_GETSCALINGFACTOR     1L
#define DEVESC_QUERYVIOCELLSIZES    2L
#define DEVESC_GETCP             8000L
#define DEVESC_STARTDOC          8150L
#define DEVESC_ENDDOC            8151L
#define DEVESC_NEXTBAND          8152L
#define DEVESC_ABORTDOC          8153L
#define DEVESC_NEWFRAME         16300L
#define DEVESC_DRAFTMODE        16301L
#define DEVESC_FLUSHOUTPUT      16302L
#define DEVESC_RAWDATA          16303L
#define DEVESC_SETMODE          16304L
#define DEVESC_DBE_FIRST        24450L
#define DEVESC_DBE_LAST         24455L
#define DEVESC_CHAR_EXTRA       16998L
#define DEVESC_BREAK_EXTRA      16999L
#define DEVESC_STD_JOURNAL      32600L

#define DPDM_ERROR       (-1L)
#define DPDM_NONE          0L

#define DPDM_POSTJOBPROP   0L
#define DPDM_CHANGEPROP    1L
#define DPDM_QUERYJOBPROP  2L

#define DQHC_ERROR      (-1L)
#define HCAPS_CURRENT     1L
#define HCAPS_SELECTABLE  2L

typedef CHAR STR16[16], FAR *PSTR16;
typedef CHAR STR32[32], FAR *PSTR32;
typedef CHAR STR64[64], FAR *PSTR64;

typedef struct _VIOSIZECOUNT {
    LONG maxcount;
    LONG count;
} VIOSIZECOUNT, FAR * PVIOSIZECOUNT;

typedef struct _VIOFONTCELLSIZE {
    LONG cx;
    LONG cy;
} VIOFONTCELLSIZE, FAR * PVIOFONTCELLSIZE;

typedef struct _ESCGETCP {
    ULONG  options;
    USHORT codepage;
    USHORT fontid;
} ESCGETCP, FAR * PESCGETCP;

typedef struct _SFACTORS {
    LONG x;
    LONG y;
} SFACTORS, FAR * PSFACTORS;

typedef struct _BANDRECT {
    LONG xleft;
    LONG ybottom;
    LONG xright;
    LONG ytop;
} BANDRECT, FAR * PBANDRECT;

typedef struct _HCINFO {
    CHAR szFormname[32];
    LONG cx;
    LONG cy;
    LONG xLeftClip;
    LONG yBottomClip;
    LONG xRightClip;
    LONG yTopClip;
    LONG xPels;
    LONG yPels;
    LONG flAttributes;
} HCINFO, FAR *PHCINFO;

typedef struct _ESCSETMODE {
    ULONG  mode;
    USHORT codepage;
} ESCSETMODE, FAR * PESCSETMODE;

LONG  APIENTRY DevEscape(HDC,LONG,LONG,PBYTE,PLONG,PBYTE);
LONG  APIENTRY DevPostDeviceModes(HAB,PDRIVDATA,PSZ,PSZ,PSZ,ULONG);
BOOL  APIENTRY DevQueryDeviceNames(HAB,PSZ,PLONG,PSTR32,PSTR64,PLONG,PSTR16);
LONG  APIENTRY DevQueryHardcopyCaps(HDC,LONG,LONG,PHCINFO);

#endif

#ifdef __cplusplus
}
#endif
