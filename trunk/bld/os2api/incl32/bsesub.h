/*
    OS/2 Base subsystems include file for 32-bit development.
*/

#ifdef INCL_SUB
    #define INCL_KBD
    #define INCL_MOU
    #define INCL_VIO
#endif

#ifdef INCL_KBD

#define KbdCharIn          KBD16CHARIN
#define KbdClose           KBD16CLOSE
#define KbdDeRegister      KBD16DEREGISTER
#define KbdFlushBuffer     KBD16FLUSHBUFFER
#define KbdFreeFocus       KBD16FREEFOCUS
#define KbdGetCp           KBD16GETCP
#define KbdGetFocus        KBD16GETFOCUS
#define KbdGetHWID         KBD16GETHWID
#define KbdGetStatus       KBD16GETSTATUS
#define KbdOpen            KBD16OPEN
#define KbdPeek            KBD16PEEK
#define KbdRegister        KBD16REGISTER
#define KbdSetCp           KBD16SETCP
#define KbdSetCustXt       KBD16SETCUSTXT
#define KbdSetFgnd         KBD16SETFGND
#define KbdSetHWID         KBD16SETHWID
#define KbdSetStatus       KBD16SETSTATUS
#define KbdStringIn        KBD16STRINGIN
#define KbdSynch           KBD16SYNCH
#define KbdXlate           KBD16XLATE

#define KR_KBDCHARIN       0x00000001
#define KR_KBDPEEK         0x00000002
#define KR_KBDFLUSHBUFFER  0x00000004
#define KR_KBDGETSTATUS    0x00000008
#define KR_KBDSETSTATUS    0x00000010
#define KR_KBDSTRINGIN     0x00000020
#define KR_KBDOPEN         0x00000040
#define KR_KBDCLOSE        0x00000080
#define KR_KBDGETFOCUS     0x00000100
#define KR_KBDFREEFOCUS    0x00000200
#define KR_KBDGETCP        0x00000400
#define KR_KBDSETCP        0x00000800
#define KR_KBDXLATE        0x00001000
#define KR_KBDSETCUSTXT    0x00002000

#define IO_WAIT   0
#define IO_NOWAIT 1

#define KBDTRF_SHIFT_KEY_IN       0x01
#define KBDTRF_CONVERSION_REQUEST 0x20
#define KBDTRF_FINAL_CHAR_IN      0x40
#define KBDTRF_INTERIM_CHAR_IN    0x80

typedef SHANDLE HKBD;
typedef HKBD    *PHKBD;

typedef struct _KBDKEYINFO {
    UCHAR  chChar;
    UCHAR  chScan;
    UCHAR  fbStatus;
    UCHAR  bNlsShift;
    USHORT fsState;
    ULONG  time;
}KBDKEYINFO, *PKBDKEYINFO;

typedef struct _KBDHWID {
    USHORT length;
    USHORT kbd_id;
    USHORT reserved1;
    USHORT reserved2;
}KBDHWID, *PKBDHWID;

typedef struct _KBDINFO {
    USHORT cb;
    USHORT fsMask;
    USHORT chTurnAround;
    USHORT fsInterim;
    USHORT fsState;
} KBDINFO, *PKBDINFO;

typedef struct _STRINGINBUF {
    USHORT cb;
    USHORT cchIn;
} STRINGINBUF, *PSTRINGINBUF;

typedef struct _KBDTRANS {
    UCHAR  chChar;
    UCHAR  chScan;
    UCHAR  fbStatus;
    UCHAR  bNlsShift;
    USHORT fsState;
    ULONG  time;
    USHORT fsDD;
    USHORT fsXlate;
    USHORT fsShift;
    USHORT sZero;
} KBDTRANS, *PKBDTRANS;

USHORT APIENTRY16 KbdCharIn(PKBDKEYINFO CharData, USHORT IOWait, HKBD KbdHandle);
USHORT APIENTRY16 KbdClose(HKBD KbdHandle);
USHORT APIENTRY16 KbdDeRegister(VOID);
USHORT APIENTRY16 KbdFlushBuffer(HKBD KbdHandle);
USHORT APIENTRY16 KbdFreeFocus(HKBD KbdHandle);
USHORT APIENTRY16 KbdGetCp(ULONG Reserved, PUSHORT CodePageID, HKBD KbdHandle);
USHORT APIENTRY16 KbdGetFocus(USHORT IOWait, HKBD KbdHandle);
USHORT APIENTRY16 KbdGetHWId(PKBDHWID KeyboardID, HKBD KbdHandle);
USHORT APIENTRY16 KbdGetStatus(PKBDINFO Structure, HKBD KbdHandle);
USHORT APIENTRY16 KbdOpen(PHKBD KbdHandle);
USHORT APIENTRY16 KbdPeek(PKBDKEYINFO CharData, HKBD KbdHandle);
USHORT APIENTRY16 KbdRegister(PSZ ModuleName, PSZ EntryPoint, ULONG FunctionMask);
USHORT APIENTRY16 KbdSetCp(USHORT Reserved, USHORT CodePageID, HKBD KbdHandle);
USHORT APIENTRY16 KbdSetCustXt(PUSHORT Xlatetable, HKBD KbdHandle);
USHORT APIENTRY16 KbdSetFgnd(VOID);
USHORT APIENTRY16 KbdSetStatus(PKBDINFO Structure, HKBD KbdHandle);
USHORT APIENTRY16 KbdStringIn(PCH CharBuffer, PSTRINGINBUF Length, USHORT IOWait, HKBD KbdHandle);
USHORT APIENTRY16 KbdSynch(USHORT IOWait);
USHORT APIENTRY16 KbdXlate(PKBDTRANS XlateRecord, HKBD KbdHandle);

#endif

#ifdef INCL_MOU

#define MouClose            MOU16CLOSE
#define MouDeRegister       MOU16DEREGISTER
#define MouDrawPtr          MOU16DRAWPTR
#define MouFlushQue         MOU16FLUSHQUE
#define MouGetDevStatus     MOU16GETDEVSTATUS
#define MouGetEventMask     MOU16GETEVENTMASK
#define MouGetNumButtons    MOU16GETNUMBUTTONS
#define MouGetNumMickeys    MOU16GETNUMMICKEYS
#define MouGetNumQueEl      MOU16GETNUMQUEEL
#define MouGetPtrPos        MOU16GETPTRPOS
#define MouGetPtrShape      MOU16GETPTRSHAPE
#define MouGetScaleFact     MOU16GETSCALEFACT
#define MouGetThreshold     MOU16GETTHRESHOLD
#define MouInitReal         MOU16INITREAL
#define MouOpen             MOU16OPEN
#define MouReadEventQue     MOU16READEVENTQUE
#define MouRegister         MOU16REGISTER
#define MouRemovePtr        MOU16REMOVEPTR
#define MouSetDevStatus     MOU16SETDEVSTATUS
#define MouSetEventMask     MOU16SETEVENTMASK
#define MouSetPtrPos        MOU16SETPTRPOS
#define MouSetPtrShape      MOU16SETPTRSHAPE
#define MouSetScaleFact     MOU16SETSCALEFACT
#define MouSetThreshold     MOU16SETTHRESHOLD
#define MouSynch            MOU16SYNCH

#define MR_MOUGETNUMBUTTONS 0x00000001
#define MR_MOUGETNUMMICKEYS 0x00000002
#define MR_MOUGETDEVSTATUS  0x00000004
#define MR_MOUGETNUMQUEEL   0x00000008
#define MR_MOUREADEVENTQUE  0x00000010
#define MR_MOUGETSCALEFACT  0x00000020
#define MR_MOUGETEVENTMASK  0x00000040
#define MR_MOUSETSCALEFACT  0x00000080
#define MR_MOUSETEVENTMASK  0x00000100
#define MR_MOUOPEN          0x00000800
#define MR_MOUCLOSE         0x00001000
#define MR_MOUGETPTRSHAPE   0x00002000
#define MR_MOUSETPTRSHAPE   0x00004000
#define MR_MOUDRAWPTR       0x00008000
#define MR_MOUREMOVEPTR     0x00010000
#define MR_MOUGETPTRPOS     0x00020000
#define MR_MOUSETPTRPOS     0x00040000
#define MR_MOUINITREAL      0x00080000
#define MR_MOUSETDEVSTATUS  0x00100000

#define MHK_BUTTON1 1
#define MHK_BUTTON2 2
#define MHK_BUTTON3 4

#define MOU_NODRAW  1
#define MOU_DRAW    0
#define MOU_MICKEYS 2
#define MOU_PELS    0

#define MOU_NOWAIT 0
#define MOU_WAIT   1

#define MOUSE_MOTION               0x0001
#define MOUSE_MOTION_WITH_BN1_DOWN 0x0002
#define MOUSE_BN1_DOWN             0x0004
#define MOUSE_MOTION_WITH_BN2_DOWN 0x0008
#define MOUSE_BN2_DOWN             0x0010
#define MOUSE_MOTION_WITH_BN3_DOWN 0x0020
#define MOUSE_BN3_DOWN             0x0040

typedef SHANDLE  HMOU;
typedef HMOU     *PHMOU;

typedef struct _MOUQUEINFO {
    USHORT cEvents;
    USHORT cmaxEvents;
} MOUQUEINFO, *PMOUQUEINFO;

typedef struct _PTRLOC {
    USHORT row;
    USHORT col;
} PTRLOC, *PPTRLOC;

typedef struct _PTRSHAPE {
    USHORT cb;
    USHORT col;
    USHORT row;
    USHORT colHot;
    USHORT rowHot;
} PTRSHAPE, *PPTRSHAPE;

typedef struct _SCALEFACT {
    USHORT rowScale;
    USHORT colScale;
} SCALEFACT, *PSCALEFACT;

typedef struct _MOUEVENTINFO {
    USHORT fs;
    ULONG  time;
    USHORT row;
    USHORT col;
} MOUEVENTINFO, *PMOUEVENTINFO;

typedef struct _NOPTRRECT {
    USHORT row;
    USHORT col;
    USHORT cRow;
    USHORT cCol;
} NOPTRRECT, *PNOPTRRECT;

USHORT APIENTRY16 MouClose(HMOU DeviceHandle);
USHORT APIENTRY16 MouDeRegister(VOID);
USHORT APIENTRY16 MouDrawPtr(HMOU DeviceHandle);
USHORT APIENTRY16 MouFlushQue(HMOU DeviceHandle);
USHORT APIENTRY16 MouGetDevStatus(PUSHORT DeviceStatus, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetEventMask(PUSHORT EventMask, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetNumButtons(PUSHORT NumberOfButtons, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetNumMickeys(PUSHORT NumberOfMickeys, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetNumQueEl(PMOUQUEINFO QueDataRecord, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetPtrPos(PPTRLOC PtrPos, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetPtrShape(PBYTE PtrBuffer, PPTRSHAPE PtrDefRec, HMOU DeviceHandle);
USHORT APIENTRY16 MouGetScaleFact(PSCALEFACT ScaleStruct, HMOU DeviceHandle);
USHORT APIENTRY16 MouInitReal(PSZ DriverName);
USHORT APIENTRY16 MouOpen(PSZ DriverName, PHMOU DeviceHandle);
USHORT APIENTRY16 MouReadEventQue(PMOUEVENTINFO Buffer, PUSHORT ReadType, HMOU DeviceHandle);
USHORT APIENTRY16 MouRegister(PSZ ModuleName, PSZ EntryName, ULONG Mask);
USHORT APIENTRY16 MouRemovePtr(PNOPTRRECT PtrArea, HMOU DeviceHandle);
USHORT APIENTRY16 MouSetDevStatus(PUSHORT DeviceStatus, HMOU DeviceHandle);
USHORT APIENTRY16 MouSetEventMask(PUSHORT EventMask, HMOU DeviceHandle);
USHORT APIENTRY16 MouSetPtrPos(PPTRLOC PtrPos, HMOU DeviceHandle);
USHORT APIENTRY16 MouSetPtrShape(PBYTE PtrBuffer, PPTRSHAPE PtrDefRec, HMOU DeviceHandle);
USHORT APIENTRY16 MouSetScaleFact(PSCALEFACT ScaleStruct, HMOU DeviceHandle);
USHORT APIENTRY16 MouSynch(USHORT IOWait);

#endif

#ifdef INCL_VIO

#define VioDeRegister      VIO16DEREGISTER
#define VioEndPopUp        VIO16ENDPOPUP
#define VioGetAnsi         VIO16GETANSI
#define VioGetBuf          VIO16GETBUF
#define VioGetConfig       VIO16GETCONFIG
#define VioGetCp           VIO16GETCP
#define VioGetCurPos       VIO16GETCURPOS
#define VioGetCurType      VIO16GETCURTYPE
#define VioGetFont         VIO16GETFONT
#define VioGetMode         VIO16GETMODE
#define VioGetPhysBuf      VIO16GETPHYSBUF
#define VioGetState        VIO16GETSTATE
#define VioModeUndo        VIO16MODEUNDO
#define VioModeWait        VIO16MODEWAIT
#define VioPopUp           VIO16POPUP
#define VioPrtSc           VIO16PRTSC
#define VioPrtScToggle     VIO16PRTSCTOGGLE
#define VioReadCellStr     VIO16READCELLSTR
#define VioReadCharStr     VIO16READCHARSTR
#define VioRedrawSize      VIO16REDRAWSIZE
#define VioRegister        VIO16REGISTER
#define VioSavRedrawUndo   VIO16SAVREDRAWUNDO
#define VioSavRedrawWait   VIO16SAVREDRAWWAIT
#define VioScrLock         VIO16SCRLOCK
#define VioScrUnLock       VIO16SCRUNLOCK
#define VioScrollDn        VIO16SCROLLDN
#define VioScrollLf        VIO16SCROLLLF
#define VioScrollRt        VIO16SCROLLRT
#define VioScrollUp        VIO16SCROLLUP
#define VioSetAnsi         VIO16SETANSI
#define VioSetCp           VIO16SETCP
#define VioSetCurPos       VIO16SETCURPOS
#define VioSetCurType      VIO16SETCURTYPE
#define VioSetFont         VIO16SETFONT
#define VioSetMode         VIO16SETMODE
#define VioSetState        VIO16SETSTATE
#define VioShowBuf         VIO16SHOWBUF
#define VioWrtCellStr      VIO16WRTCELLSTR
#define VioWrtCharStr      VIO16WRTCHARSTR
#define VioWrtCharStrAtt   VIO16WRTCHARSTRATT
#define VioWrtNAttr        VIO16WRTNATTR
#define VioWrtNCell        VIO16WRTNCELL
#define VioWrtNChar        VIO16WRTNCHAR
#define VioWrtTTY          VIO16WRTTTY

#define VR_VIOGETCURPOS    0x00000001
#define VR_VIOGETCURTYPE   0x00000002
#define VR_VIOGETMODE      0x00000004
#define VR_VIOGETBUF       0x00000008
#define VR_VIOGETPHYSBUF   0x00000010
#define VR_VIOSETCURPOS    0x00000020
#define VR_VIOSETCURTYPE   0x00000040
#define VR_VIOSETMODE      0x00000080
#define VR_VIOSHOWBUF      0x00000100
#define VR_VIOREADCHARSTR  0x00000200
#define VR_VIOREADCELLSTR  0x00000400
#define VR_VIOWRTNCHAR     0x00000800
#define VR_VIOWRTNATTR     0x00001000
#define VR_VIOWRTNCELL     0x00002000
#define VR_VIOWRTTTY       0x00004000
#define VR_VIOWRTCHARSTR   0x00008000

#define VR_VIOWRTCHARSTRATT  0x00010000
#define VR_VIOWRTCELLSTR     0x00020000
#define VR_VIOSCROLLUP       0x00040000
#define VR_VIOSCROLLDN       0x00080000
#define VR_VIOSCROLLLF       0x00100000
#define VR_VIOSCROLLRT       0x00200000
#define VR_VIOSETANSI        0x00400000
#define VR_VIOGETANSI        0x00800000
#define VR_VIOPRTSC          0x01000000
#define VR_VIOSCRLOCK        0x02000000
#define VR_VIOSCRUNLOCK      0x04000000
#define VR_VIOSAVREDRAWWAIT  0x08000000
#define VR_VIOSAVREDRAWUNDO  0x10000000
#define VR_VIOPOPUP          0x20000000
#define VR_VIOENDPOPUP       0x40000000
#define VR_VIOPRTSCTOGGLE    0x80000000

#define VGMT_OTHER         1
#define VGMT_GRAPHICS      2
#define VGMT_DISABLEBURST  4

#define VSRWI_SAVEANDREDRAW 0
#define VSRWI_REDRAW        1

#define VSRWN_SAVE          0
#define VSRWN_REDRAW        1

#define UNDOI_GETOWNER      0
#define UNDOI_RELEASEOWNER  1

#define UNDOK_ERRORCODE     0
#define UNDOK_TERMINATE     1

#define LOCKIO_NOWAIT 0
#define LOCKIO_WAIT   1

#define LOCK_SUCCESS  0
#define LOCK_FAIL     1

#define VP_NOWAIT      0
#define VP_WAIT        1
#define VP_OPAQUE      0
#define VP_TRANSPARENT 2

#define VMWR_POPUP 0
#define VMWN_POPUP 0

typedef SHANDLE  HVIO;
typedef HVIO     *PHVIO;

typedef struct _VIOCONFIGINFO {
    USHORT  cb;
    USHORT  adapter;
    USHORT  display;
    ULONG   cbMemory;
    USHORT  Configuration;
    USHORT  VDHVersion;
    USHORT  Flags;
    ULONG   HWBufferSize;
    ULONG   FullSaveSize;
    ULONG   PartSaveSize;
    USHORT  EMAdaptersOFF;
    USHORT  EMDisplaysOFF;
} VIOCONFIGINFO, *PVIOCONFIGINFO;

typedef struct _VIOCURSORINFO {
    USHORT   yStart;
    USHORT   cEnd;
    USHORT   cx;
    USHORT   attr;
} VIOCURSORINFO, *PVIOCURSORINFO;

typedef struct _VIOFONTINFO {
    USHORT  cb;
    USHORT  type;
    USHORT  cxCell;
    USHORT  cyCell;
    PVOID   pbData;
    USHORT  cbData;
} VIOFONTINFO, *PVIOFONTINFO;

typedef struct _VIOMODEINFO {
    USHORT cb;
    UCHAR  fbType;
    UCHAR  color;
    USHORT col;
    USHORT row;
    USHORT hres;
    USHORT vres;
    UCHAR  fmt_ID;
    UCHAR  attrib;
    ULONG  buf_addr;
    ULONG  buf_length;
    ULONG  full_length;
    ULONG  partial_length;
    PCH    ext_data_addr;
} VIOMODEINFO, *PVIOMODEINFO;

typedef struct _VIOPHYSBUF {
    PBYTE    pBuf;
    ULONG    cb;
    SEL      asel[1];
} VIOPHYSBUF, *PVIOPHYSBUF;

typedef struct _VIOPALSTATE {
    USHORT  cb;
    USHORT  type;
    USHORT  iFirst;
    USHORT  acolor[1];
} VIOPALSTATE, *PVIOPALSTATE;

typedef struct _VIOOVERSCAN {
    USHORT  cb;
    USHORT  type;
    USHORT  color;
} VIOOVERSCAN, *PVIOOVERSCAN;

typedef struct _VIOINTENSITY {
    USHORT  cb;
    USHORT  type;
    USHORT  fs;
} VIOINTENSITY, *PVIOINTENSITY;

typedef struct _VIOCOLORREG {
    USHORT  cb;
    USHORT  type;
    USHORT  firstcolorreg;
    USHORT  numcolorregs;
    PCH     colorregaddr;
} VIOCOLORREG, *PVIOCOLORREG;

typedef struct _VIOSETULINELOC {
    USHORT  cb;
    USHORT  type;
    USHORT  scanline;
} VIOSETULINELOC, *PVIOSETULINELOC;

typedef struct _VIOSETTARGET {
    USHORT  cb;
    USHORT  type;
    USHORT  defaultalgorithm;
} VIOSETTARGET, *PVIOSETTARGET;

USHORT APIENTRY16 VioDeRegister(VOID);
USHORT APIENTRY16 VioEndPopUp(HVIO VioHandle);
USHORT APIENTRY16 VioGetAnsi(PUSHORT Indicator, HVIO VioHandle);
USHORT APIENTRY16 VioGetBuf(PULONG LVBPtr, PUSHORT Length, HVIO VioHandle);
USHORT APIENTRY16 VioGetConfig(USHORT ConfigID, PVIOCONFIGINFO ConfigData, HVIO VioHandle);
USHORT APIENTRY16 VioGetCp(USHORT Reserved, PUSHORT CodePageID, HVIO VioHandle);
USHORT APIENTRY16 VioGetCurPos(PUSHORT Row, PUSHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioGetCurType(PVIOCURSORINFO CursorData, HVIO VioHandle);
USHORT APIENTRY16 VioGetMode(PVIOMODEINFO ModeData, HVIO VioHandle);
USHORT APIENTRY16 VioGetPhysBuf(PVIOPHYSBUF Structure, USHORT Reserved);
USHORT APIENTRY16 VioGetState(PVOID RequestBlock, HVIO VioHandle);
USHORT APIENTRY16 VioGlobalReg(PSZ ModuleName, PSZ EntryPoint, ULONG FunctionMask1,
                       ULONG FunctionMask2, LONG Reserved);
USHORT APIENTRY16 VioModeUndo(USHORT OwnerIndic, USHORT KillIndic, USHORT Reserved);
USHORT APIENTRY16 VioModeWait(USHORT RequestType, PUSHORT NotifyType, USHORT Reserved);
USHORT APIENTRY16 VioPopUp(PUSHORT Options, HVIO VioHandle);
USHORT APIENTRY16 VioPrtSc(HVIO VioHandle);
USHORT APIENTRY16 VioPrtScToggle(HVIO VioHandle);
USHORT APIENTRY16 VioReadCellStr(PCH CellStr, PUSHORT Length, USHORT Row,
                       USHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioReadCharStr(PCH CharStr, PUSHORT Length, USHORT Row,
                       USHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioRegister(PSZ ModuleName, PSZ EntryPoint, ULONG FunctionMask1,
                       ULONG FunctionMask2);
USHORT APIENTRY16 VioSavRedrawUndo(USHORT OwnerIndic, USHORT KillIndic, HVIO VioHandle);
USHORT APIENTRY16 VioSavRedrawWait(USHORT SavRedrawIndic, PUSHORT NotifyType, HVIO VioHandle);
USHORT APIENTRY16 VioScrLock(USHORT WaitFlag, PUCHAR Status, HVIO VioHandle);
USHORT APIENTRY16 VioScrollDn(USHORT TopRow, USHORT LeftCol, USHORT BotRow, USHORT RightCol,
                       USHORT Lines, PBYTE Cell, HVIO VioHandle);
USHORT APIENTRY16 VioScrollLf(USHORT TopRow, USHORT LeftCol, USHORT BotRow, USHORT RightCol,
                       USHORT Lines, PBYTE Cell, HVIO VioHandle);
USHORT APIENTRY16 VioScrollRt(USHORT TopRow, USHORT LeftCol, USHORT BotRow, USHORT RightCol,
                       USHORT Lines, PBYTE Cell, HVIO VioHandle);
USHORT APIENTRY16 VioScrollUp(USHORT TopRow, USHORT LeftCol, USHORT BotRow, USHORT RightCol,
                       USHORT Lines, PBYTE Cell, HVIO VioHandle);
USHORT APIENTRY16 VioScrUnLock(HVIO VioHandle);
USHORT APIENTRY16 VioSetAnsi(USHORT Indicator, HVIO VioHandle);
USHORT APIENTRY16 VioSetCp(USHORT Reserved, USHORT CodePageID, HVIO VioHandle);
USHORT APIENTRY16 VioSetCurPos(USHORT Row, USHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioSetCurType(PVIOCURSORINFO CursorData, HVIO VioHandle);
USHORT APIENTRY16 VioSetFont(PVIOFONTINFO RequestBlock, HVIO VioHandle);
USHORT APIENTRY16 VioSetMode(PVIOMODEINFO ModeData, HVIO VioHandle);
USHORT APIENTRY16 VioSetState(PVOID RequestBlock, HVIO VioHandle);
USHORT APIENTRY16 VioShowBuf(USHORT Offset, USHORT Length, HVIO VioHandle);
USHORT APIENTRY16 VioWrtCellStr(PCH CellStr, USHORT Length, USHORT Row, USHORT Column,
                       HVIO VioHandle);
USHORT APIENTRY16 VioWrtCharStr(PCH CharStr, USHORT Length, USHORT Row, USHORT Column,
                       HVIO VioHandle);
USHORT APIENTRY16 VioWrtCharStrAtt(PCH CharStr, USHORT Length, USHORT Row, USHORT Column,
                       PBYTE Attr, HVIO VioHandle);
USHORT APIENTRY16 VioWrtNAttr(PBYTE Attr, USHORT Times, USHORT Row, USHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioWrtNCell(PBYTE Cell, USHORT Times, USHORT Row, USHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioWrtNChar(PBYTE Cell, USHORT Times, USHORT Row, USHORT Column, HVIO VioHandle);
USHORT APIENTRY16 VioWrtTTY(PCH CharStr, USHORT Length, HVIO VioHandle);

#endif
