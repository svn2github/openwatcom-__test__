/*
    OS/2 Presentation Manager device support include file
    for 32-bit development.
*/


#if defined(INCL_DEV) || !defined(INCL_NOCOMMON)

#define CAPS_FAMILY                   0
#define CAPS_IO_CAPS                  1
#define CAPS_TECHNOLOGY               2
#define CAPS_DRIVER_VERSION           3
#define CAPS_WIDTH                    4
#define CAPS_HEIGHT                   5
#define CAPS_WIDTH_IN_CHARS           6
#define CAPS_HEIGHT_IN_CHARS          7
#define CAPS_HORIZONTAL_RESOLUTION    8
#define CAPS_VERTICAL_RESOLUTION      9
#define CAPS_CHAR_WIDTH              10
#define CAPS_CHAR_HEIGHT             11
#define CAPS_SMALL_CHAR_WIDTH        12
#define CAPS_SMALL_CHAR_HEIGHT       13
#define CAPS_COLORS                  14
#define CAPS_COLOR_PLANES            15
#define CAPS_COLOR_BITCOUNT          16
#define CAPS_COLOR_TABLE_SUPPORT     17
#define CAPS_MOUSE_BUTTONS           18
#define CAPS_FOREGROUND_MIX_SUPPORT  19
#define CAPS_BACKGROUND_MIX_SUPPORT  20
#define CAPS_DEVICE_WINDOWING        31
#define CAPS_ADDITIONAL_GRAPHICS     32
#define CAPS_VIO_LOADABLE_FONTS      21
#define CAPS_WINDOW_BYTE_ALIGNMENT   22
#define CAPS_BITMAP_FORMATS          23
#define CAPS_RASTER_CAPS             24
#define CAPS_MARKER_HEIGHT           25
#define CAPS_MARKER_WIDTH            26
#define CAPS_DEVICE_FONTS            27
#define CAPS_GRAPHICS_SUBSET         28
#define CAPS_GRAPHICS_VERSION        29
#define CAPS_GRAPHICS_VECTOR_SUBSET  30
#define CAPS_PHYS_COLORS             33
#define CAPS_COLOR_INDEX             34
#define CAPS_GRAPHICS_CHAR_WIDTH     35
#define CAPS_GRAPHICS_CHAR_HEIGHT    36
#define CAPS_HORIZONTAL_FONT_RES     37
#define CAPS_VERTICAL_FONT_RES       38
#define CAPS_DEVICE_FONT_SIM         39
#define CAPS_LINEWIDTH_THICK         40
#define CAPS_DEVICE_POLYSET_POINTS   41

#define CAPS_IO_DUMMY              1
#define CAPS_IO_SUPPORTS_OP        2
#define CAPS_IO_SUPPORTS_IP        3
#define CAPS_IO_SUPPORTS_IO        4

#define CAPS_TECH_UNKNOWN          0
#define CAPS_TECH_VECTOR_PLOTTER   1
#define CAPS_TECH_RASTER_DISPLAY   2
#define CAPS_TECH_RASTER_PRINTER   3
#define CAPS_TECH_RASTER_CAMERA    4
#define CAPS_TECH_POSTSCRIPT       5

#define CAPS_COLTABL_RGB_8         1
#define CAPS_COLTABL_RGB_8_PLUS    2
#define CAPS_COLTABL_TRUE_MIX      4
#define CAPS_COLTABL_REALIZE       8

#define CAPS_FM_OR              0x0001
#define CAPS_FM_OVERPAINT       0x0002
#define CAPS_FM_XOR             0x0008
#define CAPS_FM_LEAVEALONE      0x0010
#define CAPS_FM_AND             0x0020
#define CAPS_FM_GENERAL_BOOLEAN 0x0040

#define CAPS_BM_OR              0x0001
#define CAPS_BM_OVERPAINT       0x0002
#define CAPS_BM_XOR             0x0008
#define CAPS_BM_LEAVEALONE      0x0010
#define CAPS_BM_AND             0x0020
#define CAPS_BM_GENERAL_BOOLEAN 0x0040
#define CAPS_BM_SRCTRANSPARENT  0x0080
#define CAPS_BM_DESTTRANSPARENT 0x0100

#define DEV_ERROR                 0
#define DEV_OK                    1
#define DEV_BAD_PARAMETERS        2
#define DEV_WARNING               3
#define DEV_PROP_BUF_TOO_SMALL    4
#define DEV_ITEM_BUF_TOO_SMALL    5
#define DEV_INV_INP_JOBPROPERTIES 6

#define DEVESC_QUERYESCSUPPORT          0
#define DEVESC_GETSCALINGFACTOR         1
#define DEVESC_QUERYVIOCELLSIZES        2
#define DEVESC_GETCP                 8000
#define DEVESC_SETABORTPROC          8001
#define DEVESC_QUERYPDL              8002
#define DEVESC_STARTDOC              8150
#define DEVESC_ENDDOC                8151
#define DEVESC_NEXTBAND              8152
#define DEVESC_ABORTDOC              8153
#define DEVESC_GETJOBID              8160
#define DEVESC_QUERY_RASTER          8161
#define DEVESC_QUERYSIZE             8162
#define DEVESC_QUERYJOBPROPERTIES    8163
#define DEVESC_SETJOBPROPERTIES      8164
#define DEVESC_DEFAULTJOBPROPERTIES  8165
#define DEVESC_CHANGEOUTPUTPORT      8166
#define DEVESC_NEWFRAME             16300
#define DEVESC_DRAFTMODE            16301
#define DEVESC_FLUSHOUTPUT          16302
#define DEVESC_RAWDATA              16303
#define DEVESC_SETMODE              16304
#define DEVESC_SEP                  16305
#define DEVESC_MACRO                16307
#define DEVESC_BEGIN_BITBLT         16309
#define DEVESC_END_BITBLT           16310
#define DEVESC_SEND_COMPDATA        16311
#define DEVESC_DBE_FIRST            24450
#define DEVESC_DBE_LAST             24455
#define DEVESC_CHAR_EXTRA           16998
#define DEVESC_BREAK_EXTRA          16999
#define DEVESC_STD_JOURNAL          32600
#define DEVESC_SETPS                49149
#define DEVESC_STARTDOC_WPROP       49150
#define DEVESC_NEWFRAME_WPROP       49151

#define DRIVER_NAME    1
#define DRIVER_DATA    2
#define DATA_TYPE      3
#define COMMENT        4
#define PROC_NAME      5
#define PROC_PARAMS    6
#define SPL_PARAMS     7
#define NETWORK_PARAMS 8

#define OD_SCREEN           0
#define OD_QUEUED           2
#define OD_DIRECT           5
#define OD_INFO             6
#define OD_METAFILE         7
#define OD_MEMORY           8
#define OD_METAFILE_NOQUERY 9

#define DPDM_ERROR      (-1)
#define DPDM_NONE         0

#define DPDM_POSTJOBPROP  0
#define DPDM_CHANGEPROP   1
#define DPDM_QUERYJOBPROP 2

typedef CHAR STR16[16], *PSTR16;
typedef CHAR STR32[32], *PSTR32;
typedef CHAR STR64[64], *PSTR64;

#define DQHC_ERROR                    (-1)

#define HCAPS_CURRENT                   1
#define HCAPS_SELECTABLE                2


typedef PSZ *PDEVOPENDATA;

typedef struct _VIOSIZECOUNT {
    LONG maxcount;
    LONG count;
} VIOSIZECOUNT, *PVIOSIZECOUNT;

typedef struct _VIOFONTCELLSIZE {
    LONG cx;
    LONG cy;
} VIOFONTCELLSIZE, *PVIOFONTCELLSIZE;

typedef struct _SFACTORS {
    LONG x;
    LONG y;
} SFACTORS, *PSFACTORS;

typedef struct _BANDRECT {
    LONG xleft;
    LONG ybottom;
    LONG xright;
    LONG ytop;
} BANDRECT, *PBANDRECT;

typedef struct _DRIVDATA {
    LONG cb;
    LONG lVersion;
    CHAR szDeviceName[32];
    CHAR abGeneralData[1];
} DRIVDATA, *PDRIVDATA;

typedef struct _DEVOPENSTRUC {
    PSZ       pszLogAddress;
    PSZ       pszDriverName;
    PDRIVDATA pdriv;
    PSZ       pszDataType;
    PSZ       pszComment;
    PSZ       pszQueueProcName;
    PSZ       pszQueueProcParams;
    PSZ       pszSpoolerParams;
    PSZ       pszNetworkParams;
} DEVOPENSTRUC, *PDEVOPENSTRUC;

HMF    APIENTRY DevCloseDC(HDC hdc);
LONG   APIENTRY DevEscape(HDC hdc, LONG lCode, LONG lInCount, PBYTE pbInData,
                   PLONG plOutCount, PBYTE pbOutData);
HDC    APIENTRY DevOpenDC(HAB hab, LONG lType, PCSZ pszToken, LONG lCount,
                   PDEVOPENDATA pdopData, HDC hdcComp);
LONG   APIENTRY DevPostDeviceModes(HAB hab, PDRIVDATA pdrivDriverData, PCSZ pszDriverName,
                   PCSZ pszDeviceName, PCSZ pszName, ULONG flOptions);
BOOL   APIENTRY DevQueryCaps(HDC hdc, LONG lStart, LONG lCount, PLONG alArray);

#endif

