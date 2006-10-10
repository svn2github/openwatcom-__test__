/*
    OS/2 Base DOS include file for 32-bit development.
*/

#ifndef __BSEDOS_H__
#define __BSEDOS_H__

#ifdef INCL_DOS
    #define INCL_DOSDATETIME
    #define INCL_DOSDEVICES
    #define INCL_DOSEXCEPTIONS
    #define INCL_DOSFILEMGR
    #define INCL_DOSMEMMGR
    #define INCL_DOSMISC
    #define INCL_DOSMODULEMGR
    #define INCL_DOSMONITORS
    #define INCL_DOSMVDM
    #define INCL_DOSNLS
    #define INCL_DOSNMPIPES
    #define INCL_DOSPROCESS
    #define INCL_DOSPROFILE
    #define INCL_DOSQUEUES
    #define INCL_DOSRESOURCES
    #define INCL_DOSSEMAPHORES
    #define INCL_DOSSESMGR
#endif

#define CCHMAXPATH          260
#define CCHMAXPATHCOMP      256

#if defined(INCL_DOSPROCESS) || !defined(INCL_NOCOMMON)

#define EXIT_THREAD      0
#define EXIT_PROCESS     1

APIRET APIENTRY DosBeep(ULONG,ULONG);
VOID   APIENTRY DosExit(ULONG,ULONG);

#endif

#ifdef INCL_DOSPROCESS

#define DosCwait          DosWaitChild
#define DosSetPrty        DosSetPriority

#define EXEC_SYNC          0
#define EXEC_ASYNC         1
#define EXEC_ASYNCRESULT   2
#define EXEC_TRACE         3
#define EXEC_BACKGROUND    4
#define EXEC_LOAD          5
#define EXEC_ASYNCRESULTDB 6

#define PRTYC_NOCHANGE         0
#define PRTYC_IDLETIME         1
#define PRTYC_REGULAR          2
#define PRTYC_TIMECRITICAL     3
#define PRTYC_FOREGROUNDSERVER 4

#define PRTYS_PROCESS     0
#define PRTYS_PROCESSTREE 1
#define PRTYS_THREAD      2

#define PRTYD_MINIMUM     (-31)
#define PRTYD_MAXIMUM     31

#define EXLST_ADD        1
#define EXLST_REMOVE     2
#define EXLST_EXIT       3

#define DKP_PROCESSTREE  0
#define DKP_PROCESS      1

#define CREATE_READY     0
#define CREATE_SUSPENDED 1
#define STACK_SPARSE     0
#define STACK_COMMITTED  2

#define PT_FULLSCREEN    0
#define PT_REALMODE      1
#define PT_WINDOWABLEVIO 2
#define PT_PM            3
#define PT_DETACHED      4

#define PS_EXITLIST      1

#define TC_EXIT          0
#define TC_HARDERROR     1
#define TC_TRAP          2
#define TC_KILLPROCESS   3
#define TC_EXCEPTION     4

#define DCWA_PROCESS     0
#define DCWA_PROCESSTREE 1

#define DCWW_WAIT        0
#define DCWW_NOWAIT      1

#define AFNTY_THREAD     0
#define AFNTY_SYSTEM     1

typedef VOID APIENTRY FNTHREAD (ULONG);
typedef FNTHREAD *PFNTHREAD;
typedef VOID APIENTRY FNEXITLIST (ULONG);
typedef FNEXITLIST *PFNEXITLIST;

typedef struct _RESULTCODES {
    ULONG codeTerminate;
    ULONG codeResult;
} RESULTCODES, *PRESULTCODES;

typedef struct _THREADCREATE {
    ULONG     cbSize;
    PTID      pTid;
    PFNTHREAD pfnStart;
    ULONG     lParam;
    ULONG     lFlag;
    PBYTE     pStack;
    ULONG     cbStack;
} THREADCREATE, *PTHREADCREATE;

typedef struct _MPAFFINITY {
    ULONG mask[2];
} MPAFFINITY, *PMPAFFINITY;

typedef struct _PIB {
    ULONG pib_ulpid;
    ULONG pib_ulppid;
    ULONG pib_hmte;
    PCHAR pib_pchcmd;
    PCHAR pib_pchenv;
    ULONG pib_flstatus;
    ULONG pib_ultype;
} PIB, *PPIB;

typedef struct _TIB2 {
    ULONG  tib2_ultid;
    ULONG  tib2_ulpri;
    ULONG  tib2_version;
    USHORT tib2_usMCCount;
    USHORT tib2_fMCForceFlag;
} TIB2, *PTIB2;

typedef struct _TIB {
    PVOID tib_pexchain;
    PVOID tib_pstack;
    PVOID tib_pstacklimit;
    PTIB2 tib_ptib2;
    ULONG tib_version;
    ULONG tib_ordinal;
} TIB, *PTIB;

#ifndef DBG_INCL_DOSDEBUG

#define DBG_INCL_DOSDEBUG

#define DBG_C_Null            0
#define DBG_C_ReadMem         1
#define DBG_C_ReadMem_I       1
#define DBG_C_ReadMem_D       2
#define DBG_C_ReadReg         3
#define DBG_C_WriteMem        4
#define DBG_C_WriteMem_I      4
#define DBG_C_WriteMem_D      5
#define DBG_C_WriteReg        6
#define DBG_C_Go              7
#define DBG_C_Term            8
#define DBG_C_SStep           9
#define DBG_C_Stop            10
#define DBG_C_Freeze          11
#define DBG_C_Resume          12
#define DBG_C_NumToAddr       13
#define DBG_C_ReadCoRegs      14
#define DBG_C_WriteCoRegs     15
#define DBG_C_ThrdStat        17
#define DBG_C_MapROAlias      18
#define DBG_C_MapRWAlias      19
#define DBG_C_UnMapAlias      20
#define DBG_C_Connect         21
#define DBG_C_ReadMemBuf      22
#define DBG_C_WriteMemBuf     23
#define DBG_C_SetWatch        24
#define DBG_C_ClearWatch      25
#define DBG_C_RangeStep       26
#define DBG_C_Continue        27
#define DBG_C_AddrToObject    28
#define DBG_C_XchgOpcode      29
#define DBG_C_LinToSel        30
#define DBG_C_SelToLin        31
#define DBG_C_RegisterSemList 32
#define DBG_C_Attach          33
#define DBG_C_Detach          34
#define DBG_C_RegDebug        35
#define DBG_C_QueryDebug      36

#define JIT_REG_INHERIT   0x00010000
#define JIT_REG_NOINHERIT 0x00020000
#define JIT_REG_DETACH    0x00030000
#define JIT_REG_FG        0x00040000
#define DBGQ_JIT_GLOBAL   0x10000000
#define DBGQ_JIT_PERPROC  0x20000000

#define DBG_N_Success      0
#define DBG_N_Error        (-1L)
#define DBG_N_ProcTerm     (-6L)
#define DBG_N_Exception    (-7L)
#define DBG_N_ModuleLoad   (-8L)
#define DBG_N_CoError      (-9L)
#define DBG_N_ThreadTerm   (-10L)
#define DBG_N_AsyncStop    (-11L)
#define DBG_N_NewProc      (-12L)
#define DBG_N_AliasFree    (-13L)
#define DBG_N_Watchpoint   (-14L)
#define DBG_N_ThreadCreate (-15L)
#define DBG_N_ModuleFree   (-16L)
#define DBG_N_RangeStep    (-17L)

#define DBG_CO_387      1
#define DBG_D_Thawed    0
#define DBG_D_Frozen    1
#define DBG_L_386       1
#define DBG_LEN_387     108
#define DBG_T_Runnable  0
#define DBG_T_Suspended 1
#define DBG_T_Blocked   2
#define DBG_T_CritSec   3
#define DBG_W_Global    1
#define DBG_W_Local     2
#define DBG_W_Execute   0x00010000
#define DBG_W_Write     0x00020000
#define DBG_W_ReadWrite 0x00030000
#define DBG_O_OBJMTE    0x10000000

#define DBG_X_PRE_FIRST_CHANCE 0
#define DBG_X_FIRST_CHANCE     1
#define DBG_X_LAST_CHANCE      2
#define DBG_X_STACK_INVALID    3

typedef struct _uDB {
    unsigned long  Pid;
    unsigned long  Tid;
    long           Cmd;
    long           Value;
    unsigned long  Addr;
    unsigned long  Buffer;
    unsigned long  Len;
    unsigned long  Index;
    unsigned long  MTE;
    unsigned long  EAX;
    unsigned long  ECX;
    unsigned long  EDX;
    unsigned long  EBX;
    unsigned long  ESP;
    unsigned long  EBP;
    unsigned long  ESI;
    unsigned long  EDI;
    unsigned long  EFlags;
    unsigned long  EIP;
    unsigned long  CSLim;
    unsigned long  CSBase;
    unsigned char  CSAcc;
    unsigned char  CSAtr;
    unsigned short CS;
    unsigned long  DSLim;
    unsigned long  DSBase;
    unsigned char  DSAcc;
    unsigned char  DSAtr;
    unsigned short DS;
    unsigned long  ESLim;
    unsigned long  ESBase;
    unsigned char  ESAcc;
    unsigned char  ESAtr;
    unsigned short ES;
    unsigned long  FSLim;
    unsigned long  FSBase;
    unsigned char  FSAcc;
    unsigned char  FSAtr;
    unsigned short FS;
    unsigned long  GSLim;
    unsigned long  GSBase;
    unsigned char  GSAcc;
    unsigned char  GSAtr;
    unsigned short GS;
    unsigned long  SSLim;
    unsigned long  SSBase;
    unsigned char  SSAcc;
    unsigned char  SSAtr;
    unsigned short SS;
} uDB_t;

typedef struct _TStat {
    unsigned char  DbgState;
    unsigned char  TState;
    unsigned short TPriority;
} TStat_t;

#endif

APIRET APIENTRY DosAllocThreadLocalMemory(ULONG,PULONG*);
APIRET APIENTRY DosCreateThread(PTID,PFNTHREAD,ULONG,ULONG,ULONG);
APIRET APIENTRY DosCreateThread2(PTHREADCREATE);
APIRET APIENTRY DosDebug(PVOID);
APIRET APIENTRY DosEnterCritSec(VOID);
APIRET APIENTRY DosExecPgm(PCHAR,LONG,ULONG,PCSZ,PCSZ,PRESULTCODES,PCSZ);
APIRET APIENTRY DosExitCritSec(VOID);
APIRET APIENTRY DosExitList(ULONG,PFNEXITLIST);
APIRET APIENTRY DosFreeThreadLocalMemory(PULONG);
APIRET APIENTRY DosGetInfoBlocks(PTIB*,PPIB*);
APIRET APIENTRY DosKillProcess(ULONG,PID);
APIRET APIENTRY DosKillThread(TID);
APIRET APIENTRY DosQueryThreadAffinity(ULONG,PMPAFFINITY);
APIRET APIENTRY DosResumeThread(TID);
APIRET APIENTRY DosSetPriority(ULONG,ULONG,LONG,ULONG);
APIRET APIENTRY DosSetThreadAffinity(PMPAFFINITY);
APIRET APIENTRY DosSleep(ULONG);
APIRET APIENTRY DosSuspendThread(TID);
APIRET APIENTRY DosWaitChild(ULONG,ULONG,PRESULTCODES,PPID,PID);
APIRET APIENTRY DosWaitThread(PTID,ULONG);

#endif

#if defined(INCL_DOSFILEMGR) || !defined(INCL_NOCOMMON)

#define DosBufReset    DosResetBuffer
#define DosChDir       DosSetCurrentDir
#define DosChgFilePtr  DosSetFilePtr
#define DosFindFirst2  DosFindFirst
#define DosMkDir       DosCreateDir
#define DosMkDir2      DosCreateDir
#define DosNewSize     DosSetFileSize
#define DosOpen2       DosOpen
#define DosProtectChgFilePtr DosProtectSetFilePtr
#define DosProtectQFileInfo DosProtectQueryFileInfo
#define DosProtectQFHandState DosProtectQueryFHState
#define DosProtectNewSize DosProtectSetFileSize
#define DosProtectSetFHandState DosProtectSetFHState
#define DosQCurDir     DosQueryCurrentDir
#define DosQCurDisk    DosQueryCurrentDisk
#define DosQFileInfo   DosQueryFileInfo
#define DosQFHandState DosQueryFHState
#define DosQFSAttach   DosQueryFSAttach
#define DosQFSInfo     DosQueryFSInfo
#define DosQHandType   DosQueryHType
#define DosQPathInfo   DosQueryPathInfo
#define DosQVerify     DosQueryVerify
#define DosRmDir       DosDeleteDir
#define DosSelectDisk  DosSetDefaultDisk
#define DosSetFHandState DosSetFHState

#define FILE_BEGIN    0
#define FILE_CURRENT  1
#define FILE_END      2

#define HDIR_SYSTEM   1
#define HDIR_CREATE   (-1)

#define DCPY_EXISTING 1
#define DCPY_APPEND   2
#define DCPY_FAILEAS  4

#define FILE_NORMAL    0x0000
#define FILE_READONLY  0x0001
#define FILE_HIDDEN    0x0002
#define FILE_SYSTEM    0x0004
#define FILE_DIRECTORY 0x0010
#define FILE_ARCHIVED  0x0020
#define FILE_IGNORE    0x10000

#define MUST_HAVE_READONLY  ((FILE_READONLY  << 8) | FILE_READONLY)
#define MUST_HAVE_HIDDEN    ((FILE_HIDDEN    << 8) | FILE_HIDDEN)
#define MUST_HAVE_SYSTEM    ((FILE_SYSTEM    << 8) | FILE_SYSTEM)
#define MUST_HAVE_DIRECTORY ((FILE_DIRECTORY << 8) | FILE_DIRECTORY)
#define MUST_HAVE_ARCHIVED  ((FILE_ARCHIVED  << 8) | FILE_ARCHIVED)

#define FILE_EXISTED   1
#define FILE_CREATED   2
#define FILE_TRUNCATED 3

#define FILE_OPEN     0x0001
#define FILE_TRUNCATE 0x0002
#define FILE_CREATE   0x0010

#define OPEN_ACTION_FAIL_IF_EXISTS    0
#define OPEN_ACTION_OPEN_IF_EXISTS    1
#define OPEN_ACTION_REPLACE_IF_EXISTS 2

#define OPEN_ACTION_FAIL_IF_NEW     0x0000
#define OPEN_ACTION_CREATE_IF_NEW   0x0010

#define OPEN_ACCESS_READONLY        0x0000
#define OPEN_ACCESS_WRITEONLY       0x0001
#define OPEN_ACCESS_READWRITE       0x0002
#define OPEN_SHARE_DENYREADWRITE    0x0010
#define OPEN_SHARE_DENYWRITE        0x0020
#define OPEN_SHARE_DENYREAD         0x0030
#define OPEN_SHARE_DENYNONE         0x0040
#define OPEN_FLAGS_NOINHERIT        0x0080
#define OPEN_FLAGS_NO_LOCALITY      0x0000
#define OPEN_FLAGS_SEQUENTIAL       0x0100
#define OPEN_FLAGS_RANDOM           0x0200
#define OPEN_FLAGS_RANDOMSEQUENTIAL 0x0300
#define OPEN_FLAGS_NO_CACHE         0x1000
#define OPEN_FLAGS_FAIL_ON_ERROR    0x2000
#define OPEN_FLAGS_WRITE_THROUGH    0x4000
#define OPEN_FLAGS_DASD             0x8000
#define OPEN_FLAGS_NONSPOOLED       0x00040000
#define OPEN_SHARE_DENYLEGACY       0x10000000
#define OPEN_FLAGS_PROTECTED_HANDLE 0x40000000

#define SEARCH_PATH          0
#define SEARCH_CUR_DIRECTORY 1
#define SEARCH_ENVIRONMENT   2
#define SEARCH_IGNORENETERRS 4

#define FIL_STANDARD           1
#define FIL_QUERYEASIZE        2
#define FIL_QUERYEASFROMLIST   3
#define FIL_QUERYFULLNAME      5
#define FIL_STANDARDL         11
#define FIL_QUERYEASIZEL      12
#define FIL_QUERYEASFROMLISTL 13

#define FIO_LOCK      0
#define FIO_UNLOCK    1
#define FIO_SEEK      2
#define FIO_READ      3
#define FIO_WRITE     4

#define FIO_NOSHARE   0
#define FIO_SHAREREAD 1

#define FSIL_ALLOC    1
#define FSIL_VOLSER   2

#define FHT_DISKFILE  0
#define FHT_CHRDEV    1
#define FHT_PIPE      2

#define FHB_DSKREMOTE    0x8000
#define FHB_CHRDEVREMOTE 0x8000
#define FHB_PIPEREMOTE   0x8000

#define FS_ATTACH      0
#define FS_DETACH      1
#define FS_SPOOLATTACH 2
#define FS_SPOOLDETACH 3

#define FSCTL_HANDLE   1
#define FSCTL_PATHNAME 2
#define FSCTL_FSDNAME  3

#define FSCTL_ERROR_INFO          1
#define FSCTL_MAX_EASIZE          2
#define FSCTL_GET_NEXT_ROUTE_NAME 3
#define FSCTL_DAEMON_QUERY        4

#define FSCTL_QUERY_COMPLETE 0
#define FSCTL_QUERY_AGAIN    1

#define FSAIL_QUERYNAME 1
#define FSAIL_DEVNUMBER 2
#define FSAIL_DRVNUMBER 3

#define FSAT_CHARDEV    1
#define FSAT_PSEUDODEV  2
#define FSAT_LOCALDRV   3
#define FSAT_REMOTEDRV  4

#define HANDTYPE_FILE       0x0000
#define HANDTYPE_DEVICE     0x0001
#define HANDTYPE_PIPE       0x0002
#define HANDTYPE_PROTECTED  0x4000
#define HANDTYPE_NETWORK    0x8000

#define EAT_APPTYP_PMAPI    0x00
#define EAT_APPTYP_DOS      0x01
#define EAT_APPTYP_PMW      0x02
#define EAT_APPTYP_NOPMW    0x03
#define EAT_APPTYP_EXETYPE  0x03
#define EAT_APPTYP_RESERVED ~(EAT_APPTYP_EXETYPE)

#define EAT_BINARY   0xFFFE
#define EAT_ASCII    0xFFFD
#define EAT_BITMAP   0xFFFB
#define EAT_METAFILE 0xFFFA
#define EAT_ICON     0xFFF9
#define EAT_EA       0xFFEE
#define EAT_MVMT     0xFFDF
#define EAT_MVST     0xFFDE
#define EAT_ASN1     0xFFDD

#define FEA_NEEDEA 0x80

#define DSPI_WRTTHRU 0x10

#define LISTIO_ORDERED   1
#define LISTIO_UNORDERED 2
#define LISTIO_READ      4
#define LISTIO_WRITE     8

#define ENUMEA_LEVEL_NO_VALUE 1

#define ENUMEA_REFTYPE_FHANDLE 0
#define ENUMEA_REFTYPE_PATH    1
#define ENUMEA_REFTYPE_MAX     ENUMEA_REFTYPE_PATH

typedef LHANDLE HDIR, *PHDIR;
typedef ULONG FHLOCK, *PFHLOCK;

typedef struct _FILELOCK {
    LONG lOffset;
    LONG lRange;
} FILELOCK, *PFILELOCK;

typedef struct _FILELOCKL {
    LONGLONG lOffset;
    LONGLONG lRange;
} FILELOCKL, *PFILELOCKL;

typedef struct _FDATE {
    USHORT day:5;
    USHORT month:4;
    USHORT year:7;
} FDATE, *PFDATE;

typedef struct _FTIME {
    USHORT twosecs:5;
    USHORT minutes:6;
    USHORT hours:5;
} FTIME, *PFTIME;

typedef struct _FILEFINDBUF {
    FDATE  fdateCreation;
    FTIME  ftimeCreation;
    FDATE  fdateLastAccess;
    FTIME  ftimeLastAccess;
    FDATE  fdateLastWrite;
    FTIME  ftimeLastWrite;
    ULONG  cbFile;
    ULONG  cbFileAlloc;
    USHORT attrFile;
    UCHAR  cchName;
    CHAR   achName[CCHMAXPATHCOMP];
} FILEFINDBUF, *PFILEFINDBUF;

typedef _Packed struct _FILEFINDBUF2 {
    FDATE  fdateCreation;
    FTIME  ftimeCreation;
    FDATE  fdateLastAccess;
    FTIME  ftimeLastAccess;
    FDATE  fdateLastWrite;
    FTIME  ftimeLastWrite;
    ULONG  cbFile;
    ULONG  cbFileAlloc;
    USHORT attrFile;
    ULONG  cbList;
    UCHAR  cchName;
    CHAR   achName[CCHMAXPATHCOMP];
} FILEFINDBUF2, *PFILEFINDBUF2;

typedef struct _FILEFINDBUF3 {
    ULONG oNextEntryOffset;
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
    UCHAR cchName;
    CHAR  achName[CCHMAXPATHCOMP];
} FILEFINDBUF3, *PFILEFINDBUF3;

typedef struct _FILEFINDBUF4 {
    ULONG oNextEntryOffset;
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
    ULONG cbList;
    UCHAR cchName;
    CHAR  achName[CCHMAXPATHCOMP];
} FILEFINDBUF4, *PFILEFINDBUF4;

typedef struct _FILEFINDBUF3L {
    ULONG    oNextEntryOffset;
    FDATE    fdateCreation;
    FTIME    ftimeCreation;
    FDATE    fdateLastAccess;
    FTIME    ftimeLastAccess;
    FDATE    fdateLastWrite;
    FTIME    ftimeLastWrite;
    LONGLONG cbFile;
    LONGLONG cbFileAlloc;
    ULONG    attrFile;
    UCHAR    cchName;
    CHAR     achName[CCHMAXPATHCOMP];
} FILEFINDBUF3L, *PFILEFINDBUF3L;

typedef struct _FILEFINDBUF4L {
    ULONG    oNextEntryOffset;
    FDATE    fdateCreation;
    FTIME    ftimeCreation;
    FDATE    fdateLastAccess;
    FTIME    ftimeLastAccess;
    FDATE    fdateLastWrite;
    FTIME    ftimeLastWrite;
    LONGLONG cbFile;
    LONGLONG cbFileAlloc;
    ULONG    attrFile;
    ULONG    cbList;
    UCHAR    cchName;
    CHAR     achName[CCHMAXPATHCOMP];
} FILEFINDBUF4L, *PFILEFINDBUF4L;

typedef struct _FILESTATUS {
    FDATE  fdateCreation;
    FTIME  ftimeCreation;
    FDATE  fdateLastAccess;
    FTIME  ftimeLastAccess;
    FDATE  fdateLastWrite;
    FTIME  ftimeLastWrite;
    ULONG  cbFile;
    ULONG  cbFileAlloc;
    USHORT attrFile;
} FILESTATUS, *PFILESTATUS;

typedef _Packed struct _FILESTATUS2 {
    FDATE  fdateCreation;
    FTIME  ftimeCreation;
    FDATE  fdateLastAccess;
    FTIME  ftimeLastAccess;
    FDATE  fdateLastWrite;
    FTIME  ftimeLastWrite;
    ULONG  cbFile;
    ULONG  cbFileAlloc;
    USHORT attrFile;
    ULONG  cbList;
} FILESTATUS2, *PFILESTATUS2;

typedef struct _FILESTATUS3 {
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
} FILESTATUS3, *PFILESTATUS3;

typedef struct _FILESTATUS4 {
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
    ULONG cbList;
} FILESTATUS4, *PFILESTATUS4;

typedef struct _FILESTATUS3L {
    FDATE    fdateCreation;
    FTIME    ftimeCreation;
    FDATE    fdateLastAccess;
    FTIME    ftimeLastAccess;
    FDATE    fdateLastWrite;
    FTIME    ftimeLastWrite;
    LONGLONG cbFile;
    LONGLONG cbFileAlloc;
    ULONG    attrFile;
} FILESTATUS3L, *PFILESTATUS3L;

typedef struct _FILESTATUS4L {
    FDATE    fdateCreation;
    FTIME    ftimeCreation;
    FDATE    fdateLastAccess;
    FTIME    ftimeLastAccess;
    FDATE    fdateLastWrite;
    FTIME    ftimeLastWrite;
    LONGLONG cbFile;
    LONGLONG cbFileAlloc;
    ULONG    attrFile;
    ULONG    cbList;
} FILESTATUS4L, *PFILESTATUS4L;

typedef struct _FSALLOCATE {
    ULONG idFileSystem;
    ULONG cSectorUnit;
    ULONG cUnit;
    ULONG cUnitAvail;
    USHORT cbSector;
} FSALLOCATE, *PFSALLOCATE;

typedef struct _GEA {
    BYTE cbName;
    CHAR szName[1];
} GEA, *PGEA;

typedef struct _GEALIST {
    ULONG cbList;
    GEA list[1];
} GEALIST, *PGEALIST;

typedef struct _FEA {
    BYTE fEA;
    BYTE cbName;
    USHORT cbValue;
} FEA, *PFEA;

typedef struct _FEALIST {
    ULONG cbList;
    FEA list[1];
} FEALIST, *PFEALIST;

typedef struct _EAOP {
    PGEALIST fpGEAList;
    PFEALIST fpFEAList;
    ULONG    oError;
} EAOP, *PEAOP;

typedef struct _GEA2 {
    ULONG oNextEntryOffset;
    BYTE  cbName;
    CHAR  szName[1];
} GEA2, *PGEA2;

typedef struct _GEA2LIST {
    ULONG cbList;
    GEA2  list[1];
} GEA2LIST, *PGEA2LIST;

typedef struct _FEA2 {
    ULONG  oNextEntryOffset;
    BYTE   fEA;
    BYTE   cbName;
    USHORT cbValue;
    CHAR   szName[1];
} FEA2, *PFEA2;

typedef struct _FEA2LIST {
    ULONG cbList;
    FEA2  list[1];
} FEA2LIST, *PFEA2LIST;

typedef struct _EAOP2 {
    PGEA2LIST fpGEA2List;
    PFEA2LIST fpFEA2List;
    ULONG     oError;
} EAOP2, *PEAOP2;

typedef struct _EASIZEBUF {
    USHORT cbMaxEASize;
    ULONG  cbMaxEAListSize;
} EASIZEBUF, *PEASIZEBUF;

typedef struct _ROUTENAMEBUF {
    ULONG hRouteHandle;
    UCHAR szRouteName;
} ROUTENAMEBUF, *PROUTENAMEBUF;

typedef struct _FSDTHREAD {
    USHORT usFunc;
    USHORT usStackSize;
    ULONG  ulPriorityClass;
    LONG   lPriorityLevel;
} FSDTHREAD;

typedef struct _FSDDAEMON {
    USHORT    usNumThreads;
    USHORT    usMoreFlag;
    USHORT    usCallInstance;
    FSDTHREAD tdThrds[16];
} FSDDAEMON;

typedef struct _FSQBUFFER {
    USHORT iType;
    USHORT cbName;
    UCHAR  szName[1];
    USHORT cbFSDName;
    UCHAR  szFSDName[1];
    USHORT cbFSAData;
    UCHAR  rgFSAData[1];
} FSQBUFFER, *PFSQBUFFER;

typedef struct _FSQBUFFER2 {
    USHORT iType;
    USHORT cbName;
    USHORT cbFSDName;
    USHORT cbFSAData;
    UCHAR  szName[1];
    UCHAR  szFSDName[1];
    UCHAR  rgFSAData[1];
} FSQBUFFER2, *PFSQBUFFER2;

typedef struct _SPOOLATTACH {
    USHORT hNmPipe;
    ULONG  ulKey;
} SPOOLATTACH, *PSPOOLATTACH;

typedef struct _VOLUMELABEL {
    BYTE cch;
    CHAR szVolLabel[12];
} VOLUMELABEL, *PVOLUMELABEL;

typedef struct _FSINFO {
    FDATE fdateCreation;
    FTIME ftimeCreation;
    VOLUMELABEL vol;
} FSINFO, *PFSINFO;

typedef struct _LISTIO_CB {
    HFILE hFile;
    ULONG CmdFlag;
    LONG  Offset;
    PVOID pBuffer;
    ULONG NumBytes;
    ULONG Actual;
    ULONG RetCode;
    ULONG Reserved;
    ULONG Reserved2[3];
    ULONG Reserved3[2];
} LISTIO, *PLISTIO;

typedef struct _LISTIO_CBL {
    HFILE    hFile;
    ULONG    CmdFlag;
    LONGLONG Offset;
    PVOID    pBuffer;
    ULONG    NumBytes;
    ULONG    Actual;
    ULONG    RetCode;
    ULONG    Reserved;
    ULONG    Reserved2[3];
    ULONG    Reserved3[2];
} LISTIOL, *PLISTIOL;

typedef struct _DENA1 {
    UCHAR  reserved;
    UCHAR  cbName;
    USHORT cbValue;
    UCHAR  szName[1];
} DENA1, *PDENA1;

typedef FEA2  DENA2;
typedef PFEA2 PDENA2;

APIRET APIENTRY DosCancelLockRequest(HFILE,PFILELOCK);
APIRET APIENTRY DosCancelLockRequestL(HFILE,PFILELOCKL);
APIRET APIENTRY DosClose(HFILE);
APIRET APIENTRY DosCopy(PCSZ,PCSZ,ULONG);
APIRET APIENTRY DosCreateDir(PCSZ,PEAOP2);
APIRET APIENTRY DosDelete(PCSZ);
APIRET APIENTRY DosDeleteDir(PCSZ);
APIRET APIENTRY DosDupHandle(HFILE,PHFILE);
APIRET APIENTRY DosEditName(ULONG,PCSZ,PCSZ,PBYTE,ULONG);
APIRET APIENTRY DosEnumAttribute(ULONG,PVOID,ULONG,PVOID,ULONG,PULONG,ULONG);
APIRET APIENTRY DosFindClose(HDIR);
APIRET APIENTRY DosFindFirst(PCSZ,PHDIR,ULONG,PVOID,ULONG,PULONG,ULONG);
APIRET APIENTRY DosFindNext(HDIR,PVOID,ULONG,PULONG);
APIRET APIENTRY DosForceDelete(PCSZ);
APIRET APIENTRY DosFSAttach(PCSZ,PCSZ,PVOID,ULONG,ULONG);
APIRET APIENTRY DosFSCtl(PVOID,ULONG,PULONG,PVOID,ULONG,PULONG,ULONG,PCSZ,HFILE,ULONG);
APIRET APIENTRY DosListIO(ULONG,ULONG,PLISTIO);
APIRET APIENTRY DosListIOL(LONG,LONG,PVOID);
APIRET APIENTRY DosMove(PCSZ,PCSZ);
APIRET APIENTRY DosOpen(PCSZ,PHFILE,PULONG,ULONG,ULONG,ULONG,ULONG,PEAOP2);
APIRET APIENTRY DosOpenL(PCSZ,PHFILE,PULONG,LONGLONG,ULONG,ULONG,ULONG,PEAOP2);
APIRET APIENTRY DosProtectClose(HFILE,FHLOCK);
APIRET APIENTRY DosProtectEnumAttribute(ULONG,PVOID,ULONG,PVOID,ULONG,PULONG,ULONG,FHLOCK);
APIRET APIENTRY DosProtectOpen(PCSZ,PHFILE,PULONG,ULONG,ULONG,ULONG,ULONG,PEAOP2,PFHLOCK);
APIRET APIENTRY DosProtectOpenL(PCSZ,PHFILE,PULONG,LONGLONG,ULONG,ULONG,ULONG,PEAOP2,PFHLOCK);
APIRET APIENTRY DosProtectQueryFHState(HFILE,PULONG,FHLOCK);
APIRET APIENTRY DosProtectQueryFileInfo(HFILE,ULONG,PVOID,ULONG,FHLOCK);
APIRET APIENTRY DosProtectRead(HFILE,PVOID,ULONG,PULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFHState(HFILE,ULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFileInfo(HFILE,ULONG,PVOID,ULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFileLocks(HFILE,PFILELOCK,PFILELOCK,ULONG,ULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFileLocksL(HFILE,PFILELOCKL,PFILELOCKL,ULONG,ULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFilePtr(HFILE,LONG,ULONG,PULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFilePtrL(HFILE,LONGLONG,ULONG,PLONGLONG,FHLOCK);
APIRET APIENTRY DosProtectSetFileSize(HFILE,ULONG,FHLOCK);
APIRET APIENTRY DosProtectSetFileSizeL(HFILE,LONGLONG,FHLOCK);
APIRET APIENTRY DosProtectWrite(HFILE,ULONG,ULONG,PULONG,FHLOCK);
APIRET APIENTRY DosQueryCurrentDir(ULONG,PBYTE,PULONG);
APIRET APIENTRY DosQueryCurrentDisk(PULONG,PULONG);
APIRET APIENTRY DosQueryFHState(HFILE,PULONG);
APIRET APIENTRY DosQueryFileInfo(HFILE,ULONG,PVOID,ULONG);
APIRET APIENTRY DosQueryFSAttach(PCSZ,ULONG,ULONG,PFSQBUFFER2,PULONG);
APIRET APIENTRY DosQueryFSInfo(ULONG,ULONG,PVOID,ULONG);
APIRET APIENTRY DosQueryHType(HFILE,PULONG,PULONG);
APIRET APIENTRY DosQueryPathInfo(PCSZ,ULONG,PVOID,ULONG);
APIRET APIENTRY DosQueryVerify(BOOL32*);
APIRET APIENTRY DosRead(HFILE,PVOID,ULONG,PULONG);
APIRET APIENTRY DosResetBuffer(HFILE);
APIRET APIENTRY DosSetCurrentDir(PCSZ);
APIRET APIENTRY DosSetDefaultDisk(ULONG);
APIRET APIENTRY DosSetFHState(HFILE,ULONG);
APIRET APIENTRY DosSetFileInfo(HFILE,ULONG,PVOID,ULONG);
APIRET APIENTRY DosSetFileLocks(HFILE,PFILELOCK,PFILELOCK,ULONG,ULONG);
APIRET APIENTRY DosSetFileLocksL(HFILE,PFILELOCKL,PFILELOCKL,ULONG,ULONG);
APIRET APIENTRY DosSetFilePtr(HFILE,LONG,ULONG,PULONG);
APIRET APIENTRY DosSetFilePtrL(HFILE,LONGLONG,ULONG,PLONGLONG);
APIRET APIENTRY DosSetFileSize(HFILE,ULONG);
APIRET APIENTRY DosSetFileSizeL(HFILE,LONGLONG);
APIRET APIENTRY DosSetFSInfo(ULONG,ULONG,PVOID,ULONG);
APIRET APIENTRY DosSetMaxFH(ULONG);
APIRET APIENTRY DosSetPathInfo(PCSZ,ULONG,PVOID,ULONG,ULONG);
APIRET APIENTRY DosSetRelMaxFH(PLONG,PULONG);
APIRET APIENTRY DosSetVerify(BOOL32);
APIRET APIENTRY DosShutdown(ULONG);
APIRET APIENTRY DosWrite(HFILE,PVOID,ULONG,PULONG);

#endif

#if defined(INCL_DOSMEMMGR) || !defined(INCL_NOCOMMON)

#define DosSubAlloc     DosSubAllocMem
#define DOSSUBALLOC     DosSubAllocMem
#define DosSubFree      DosSubFreeMem
#define DOSSUBFREE      DosSubFreeMem
#define DosSubSet       DosSubSetMem
#define DOSSUBSET       DosSubSetMem
#define DosSubUnset     DosSubUnsetMem
#define DOSSUBUNSET     DosSubUnsetMem

#define PAG_READ      0x00000001
#define PAG_WRITE     0x00000002
#define PAG_EXECUTE   0x00000004
#define PAG_GUARD     0x00000008
#define PAG_COMMIT    0x00000010
#define PAG_DECOMMIT  0x00000020
#define PAG_DEFAULT   0x00000400
#define PAG_SHARED    0x00002000
#define PAG_FREE      0x00004000
#define PAG_BASE      0x00010000

#define OBJ_TILE      0x00000040
#define OBJ_PROTECTED 0x00000080
#define OBJ_GETTABLE  0x00000100
#define OBJ_GIVEABLE  0x00000200
#define OBJ_ANY       0x00000400

#define DOSSUB_INIT       1
#define DOSSUB_GROW       2
#define DOSSUB_SPARSE_OBJ 4
#define DOSSUB_SERIALIZE  8

#define PAG_NPOUT       0x00000000
#define PAG_PRESENT     0x00000001
#define PAG_NPIN        0x00000002
#define PAG_PRESMASK    0x00000003
#define PAG_INVALID     0x00000000
#define PAG_RESIDENT    0x00000010
#define PAG_SWAPPABLE   0x00000020
#define PAG_DISCARDABLE 0x00000030
#define PAG_TYPEMASK    0x00000030

#define fPERM         (PAG_EXECUTE | PAG_READ | PAG_WRITE)
#define fSHARE        (OBJ_GETTABLE | OBJ_GIVEABLE)
#define fALLOC        (OBJ_TILE | PAG_COMMIT | fPERM)
#define fALLOCSHR     (OBJ_TILE | PAG_COMMIT | fSHARE | fPERM)

APIRET APIENTRY DosAllocMem(PPVOID,ULONG,ULONG);
APIRET APIENTRY DosAllocSharedMem(PPVOID,PCSZ,ULONG,ULONG);
APIRET APIENTRY DosFreeMem(PVOID);
APIRET APIENTRY DosGetNamedSharedMem(PPVOID,PCSZ,ULONG);
APIRET APIENTRY DosGetSharedMem(PVOID,ULONG);
APIRET APIENTRY DosGiveSharedMem(PVOID pb, PID pid, ULONG flag);
APIRET APIENTRY DosQueryMem(PVOID,PULONG,PULONG);
APIRET APIENTRY DosSetMem(PVOID,ULONG,ULONG);
APIRET APIENTRY DosSubAllocMem(PVOID,PPVOID,ULONG);
APIRET APIENTRY DosSubFreeMem(PVOID,PVOID,ULONG);
APIRET APIENTRY DosSubSetMem(PVOID,ULONG,ULONG);
APIRET APIENTRY DosSubUnsetMem(PVOID);

#endif

#ifdef INCL_DOSMODULEMGR

#define PT_16BIT 0
#define PT_32BIT 1

#define HW_CFG_MCA             0x00000001
#define HW_CFG_EISA            0x00000002
#define HW_CFG_ABIOS_SUPPORTED 0x00000004
#define HW_CFG_ABIOS_PRESENT   0x00000008
#define HW_CFG_PCI             0x00000010
#define HW_CFG_IBM_ABIOS       0x00000000
#define HW_CFG_OEM_ABIOS       0x00000020
#define HW_CFG_PENTIUM_CPU     0x00000040

APIRET APIENTRY DosFreeModule(HMODULE hmod);
APIRET APIENTRY DosLoadModule(PSZ,ULONG,PCSZ,PHMODULE);
APIRET APIENTRY DosQueryABIOSSupport(ULONG);
APIRET APIENTRY DosQueryModFromEIP(PHMODULE,PULONG,ULONG,PCHAR,PULONG,ULONG);
APIRET APIENTRY DosQueryModuleHandle(PCSZ,PHMODULE);
APIRET APIENTRY DosQueryModuleName(HMODULE,ULONG,PCHAR);
APIRET APIENTRY DosQueryProcAddr(HMODULE,ULONG,PCSZ,PFN*);
APIRET APIENTRY DosQueryProcType(HMODULE,ULONG,PCSZ,PULONG);
APIRET APIENTRY DosReplaceModule(PCSZ,PCSZ,PCSZ);

#endif

#ifdef INCL_DOSNMPIPES

#define NP_STATE_DISCONNECTED 1
#define NP_STATE_LISTENING    2
#define NP_STATE_CONNECTED    3
#define NP_STATE_CLOSING      4

#define NP_ACCESS_INBOUND      0x0000
#define NP_ACCESS_OUTBOUND     0x0001
#define NP_ACCESS_DUPLEX       0x0002
#define NP_INHERIT             0x0000
#define NP_NOINHERIT           0x0080
#define NP_WRITEBEHIND         0x0000
#define NP_NOWRITEBEHIND       0x4000

#define NP_READMODE_BYTE       0x0000
#define NP_READMODE_MESSAGE    0x0100
#define NP_TYPE_BYTE           0x0000
#define NP_TYPE_MESSAGE        0x0400
#define NP_END_CLIENT          0x0000
#define NP_END_SERVER          0x4000
#define NP_WAIT                0x0000
#define NP_NOWAIT              0x8000
#define NP_UNLIMITED_INSTANCES 0x00FF

#define NP_DEFAULT_WAIT    0
#define NP_INDEFINITE_WAIT (-1)

typedef LHANDLE HPIPE, *PHPIPE;

typedef struct _AVAILDATA {
    USHORT cbpipe;
    USHORT cbmessage;
} AVAILDATA, *PAVAILDATA;

typedef struct _PIPEINFO {
   USHORT cbOut;
   USHORT cbIn;
   BYTE   cbMaxInst;
   BYTE   cbCurInst;
   BYTE   cbName;
   CHAR   szName[1];
} PIPEINFO, *PPIPEINFO;

typedef struct _PIPESEMSTATE {
   BYTE   fStatus;
   BYTE   fFlag;
   USHORT usKey;
   USHORT usAvail;
} PIPESEMSTATE, *PPIPESEMSTATE;

APIRET APIENTRY DosCallNPipe(PCSZ,PVOID,ULONG,PVOID,ULONG,PULONG,ULONG);
APIRET APIENTRY DosConnectNPipe(HPIPE);
APIRET APIENTRY DosCreateNPipe(PCSZ,PHPIPE,ULONG,ULONG,ULONG,ULONG,ULONG);
APIRET APIENTRY DosDisConnectNPipe(HPIPE);
APIRET APIENTRY DosPeekNPipe(HPIPE,PVOID,ULONG,PULONG,PAVAILDATA,PULONG);
APIRET APIENTRY DosQueryNPHState(HPIPE,PULONG);
APIRET APIENTRY DosQueryNPipeInfo(HPIPE,ULONG,PVOID,ULONG);
APIRET APIENTRY DosQueryNPipeSemState(HSEM,PPIPESEMSTATE,ULONG);
APIRET APIENTRY DosSetNPHState(HPIPE,ULONG);
APIRET APIENTRY DosSetNPipeSem(HPIPE,HSEM,ULONG);
APIRET APIENTRY DosTransactNPipe(HPIPE,PVOID,ULONG,PVOID,ULONG,PULONG);
APIRET APIENTRY DosWaitNPipe(PCSZ,ULONG);

#endif

#ifdef INCL_DOSQUEUES

#define QUE_FIFO              0
#define QUE_LIFO              1
#define QUE_PRIORITY          2
#define QUE_NOCONVERT_ADDRESS 0
#define QUE_CONVERT_ADDRESS   4

typedef LHANDLE HQUEUE, *PHQUEUE;

typedef struct _REQUESTDATA {
    PID   pid;
    ULONG ulData;
} REQUESTDATA, *PREQUESTDATA;

APIRET APIENTRY DosCloseQueue(HQUEUE);
APIRET APIENTRY DosCreatePipe(PHFILE,PHFILE,ULONG);
APIRET APIENTRY DosCreateQueue(PHQUEUE,ULONG,PCSZ);
APIRET APIENTRY DosOpenQueue(PPID,PHQUEUE,PCSZ);
APIRET APIENTRY DosPeekQueue(HQUEUE,PREQUESTDATA,PULONG,PPVOID,PULONG,BOOL32,PBYTE,HEV);
APIRET APIENTRY DosPurgeQueue(HQUEUE);
APIRET APIENTRY DosQueryQueue(HQUEUE,PULONG);
APIRET APIENTRY DosReadQueue(HQUEUE,PREQUESTDATA,PULONG,PPVOID,ULONG,BOOL32,PBYTE,HEV);
APIRET APIENTRY DosWriteQueue(HQUEUE,ULONG,ULONG,PVOID,ULONG);

#endif

#ifdef INCL_DOSSEMAPHORES

#define DC_SEM_SHARED   1
#define DCMW_WAIT_ANY   2
#define DCMW_WAIT_ALL   4

#define DCE_POSTONE     0x0800
#define DCE_AUTORESET   0x1000

#define SEM_IMMEDIATE_RETURN 0
#define SEM_INDEFINITE_WAIT  (-1)

typedef struct _SEMRECORD {
    HSEM  hsemCur;
    ULONG ulUser;
} SEMRECORD, *PSEMRECORD;

APIRET APIENTRY DosAddMuxWaitSem(HMUX,PSEMRECORD);
APIRET APIENTRY DosCloseEventSem(HEV);
APIRET APIENTRY DosCloseMutexSem(HMTX);
APIRET APIENTRY DosCloseMuxWaitSem(HMUX);
APIRET APIENTRY DosCreateEventSem(PCSZ,PHEV,ULONG,BOOL32);
APIRET APIENTRY DosCreateMutexSem(PCSZ,PHMTX,ULONG,BOOL32);
APIRET APIENTRY DosCreateMuxWaitSem(PCSZ,PHMUX,ULONG,PSEMRECORD,ULONG);
APIRET APIENTRY DosDeleteMuxWaitSem(HMUX,HSEM);
APIRET APIENTRY DosOpenEventSem(PCSZ,PHEV);
APIRET APIENTRY DosOpenMutexSem(PCSZ,PHMTX);
APIRET APIENTRY DosOpenMuxWaitSem(PCSZ,PHMUX);
APIRET APIENTRY DosPostEventSem(HEV);
APIRET APIENTRY DosQueryEventSem(HEV,PULONG);
APIRET APIENTRY DosQueryMutexSem(HMTX,PPID,PTID,PULONG);
APIRET APIENTRY DosQueryMuxWaitSem(HMUX,PULONG,PSEMRECORD,PULONG);
APIRET APIENTRY DosReleaseMutexSem(HMTX);
APIRET APIENTRY DosRequestMutexSem(HMTX,ULONG);
APIRET APIENTRY DosResetEventSem(HEV,PULONG);
APIRET APIENTRY DosWaitEventSem(HEV,ULONG);
APIRET APIENTRY DosWaitMuxWaitSem(HMUX,ULONG,PULONG);

#endif

#ifdef INCL_DOSMONITORS

#define DosMonClose DOS16MONCLOSE
#define DosMonOpen  DOS16MONOPEN
#define DosMonRead  DOS16MONREAD
#define DosMonReg   DOS16MONREG
#define DosMonWrite DOS16MONWRITE

typedef SHANDLE  HMONITOR;
typedef HMONITOR *PHMONITOR;

USHORT APIENTRY16 DosMonClose(HMONITOR);
USHORT APIENTRY16 DosMonOpen(PSZ,PHMONITOR);
USHORT APIENTRY16 DosMonRead(PBYTE,USHORT,PBYTE,PUSHORT);
USHORT APIENTRY16 DosMonReg(HMONITOR,PBYTE,PBYTE,USHORT,USHORT);
USHORT APIENTRY16 DosMonWrite(PBYTE,PBYTE,USHORT);

#endif

#ifdef INCL_DOSNLS

#define DosCaseMap     DosMapCase
#define DosGetCollate  DosQueryCollate
#define DosGetCp       DosQueryCp
#define DosGetCtryInfo DosQueryCtryInfo
#define DosGetDBCSEv   DosQueryDBCSEnv
#define DosSetProcCp   DosSetProcessCp

typedef struct _COUNTRYCODE {
    ULONG  country;
    ULONG  codepage;
} COUNTRYCODE, *PCOUNTRYCODE;

typedef struct _COUNTRYINFO {
    ULONG  country;
    ULONG  codepage;
    ULONG  fsDateFmt;
    CHAR   szCurrency[5];
    CHAR   szThousandsSeparator[2];
    CHAR   szDecimal[2];
    CHAR   szDateSeparator[2];
    CHAR   szTimeSeparator[2];
    UCHAR  fsCurrencyFmt;
    UCHAR  cDecimalPlace;
    UCHAR  fsTimeFmt;
    USHORT abReserved1[2];
    CHAR   szDataSeparator[2];
    USHORT abReserved2[5];
} COUNTRYINFO, *PCOUNTRYINFO;

APIRET APIENTRY DosMapCase(ULONG,PCOUNTRYCODE,PCHAR);
APIRET APIENTRY DosQueryCollate(ULONG,PCOUNTRYCODE,PCHAR,PULONG);
APIRET APIENTRY DosQueryCp(ULONG,PULONG,PULONG);
APIRET APIENTRY DosQueryCtryInfo(ULONG,PCOUNTRYCODE,PCOUNTRYINFO,PULONG);
APIRET APIENTRY DosQueryDBCSEnv(ULONG,PCOUNTRYCODE,PCHAR);
APIRET APIENTRY DosSetProcessCp(ULONG);

#endif

#ifdef INCL_DOSEXCEPTIONS

#define SIG_UNSETFOCUS 0
#define SIG_SETFOCUS   1

#include <bsexcpt.h>

APIRET APIENTRY DosAcknowledgeSignalException(ULONG);
APIRET APIENTRY DosEnterMustComplete(PULONG);
APIRET APIENTRY DosExitMustComplete(PULONG);
APIRET APIENTRY DosQueryThreadContext(TID,ULONG,PCONTEXTRECORD);
APIRET APIENTRY DosRaiseException(PEXCEPTIONREPORTRECORD);
APIRET APIENTRY DosSendSignalException(PID,ULONG);
APIRET APIENTRY DosSetExceptionHandler(PEXCEPTIONREGISTRATIONRECORD);
APIRET APIENTRY DosSetSignalExceptionFocus(BOOL32,PULONG);
APIRET APIENTRY DosUnsetExceptionHandler(PEXCEPTIONREGISTRATIONRECORD);
APIRET APIENTRY DosUnwindException(PEXCEPTIONREGISTRATIONRECORD,PVOID,PEXCEPTIONREPORTRECORD);

#endif

#if defined(INCL_DOSRESOURCES) || !defined(INCL_NOCOMMON)

#define RT_POINTER      1
#define RT_BITMAP       2
#define RT_MENU         3
#define RT_DIALOG       4
#define RT_STRING       5
#define RT_FONTDIR      6
#define RT_FONT         7
#define RT_ACCELTABLE   8
#define RT_RCDATA       9
#define RT_MESSAGE      10
#define RT_DLGINCLUDE   11
#define RT_VKEYTBL      12
#define RT_KEYTBL       13
#define RT_CHARTBL      14
#define RT_DISPLAYINFO  15
#define RT_FKASHORT     16
#define RT_FKALONG      17
#define RT_HELPTABLE    18
#define RT_HELPSUBTABLE 19
#define RT_FDDIR        20
#define RT_FD           21
#define RT_MAX          22
#define RT_RESNAMES     255

#define RF_ORDINALID 0x80000000

#endif

#ifdef INCL_DOSRESOURCES

#define DosGetResource2 DosGetResource

APIRET APIENTRY DosFreeResource(PVOID);
APIRET APIENTRY DosGetResource(HMODULE,ULONG,ULONG,PPVOID);
APIRET APIENTRY DosQueryResourceSize(HMODULE,ULONG,ULONG,PULONG);

#endif

#if defined(INCL_DOSDATETIME) || !defined(INCL_NOCOMMON)

typedef struct _DATETIME {
    UCHAR  hours;
    UCHAR  minutes;
    UCHAR  seconds;
    UCHAR  hundredths;
    UCHAR  day;
    UCHAR  month;
    USHORT year;
    SHORT  timezone;
    UCHAR  weekday;
} DATETIME, *PDATETIME;

APIRET APIENTRY DosGetDateTime(PDATETIME);
APIRET APIENTRY DosSetDateTime(PDATETIME);

#endif

#ifdef INCL_DOSDATETIME

#define DosTimerAsync   DosAsyncTimer
#define DosTimerStart   DosStartTimer
#define DosTimerStop    DosStopTimer

typedef LHANDLE HTIMER;
typedef HTIMER  *PHTIMER;

APIRET APIENTRY DosAsyncTimer(ULONG,HSEM,PHTIMER);
APIRET APIENTRY DosStartTimer(ULONG,HSEM,PHTIMER);
APIRET APIENTRY DosStopTimer(HTIMER);

#endif

#ifdef INCL_DOSMISC

#define DDP_DISABLEPROCDUMP 0
#define DDP_ENABLEPROCDUMP  1
#define DDP_PERFORMPROCDUMP 2

#define FERR_DISABLEHARDERR   0
#define FERR_ENABLEHARDERR    1
#define FERR_ENABLEEXCEPTION  0
#define FERR_DISABLEEXCEPTION 2

#define QSV_MAX_PATH_LENGTH        1
#define QSV_MAX_TEXT_SESSIONS      2
#define QSV_MAX_PM_SESSIONS        3
#define QSV_MAX_VDM_SESSIONS       4
#define QSV_BOOT_DRIVE             5
#define QSV_DYN_PRI_VARIATION      6
#define QSV_MAX_WAIT               7
#define QSV_MIN_SLICE              8
#define QSV_MAX_SLICE              9
#define QSV_PAGE_SIZE             10
#define QSV_VERSION_MAJOR         11
#define QSV_VERSION_MINOR         12
#define QSV_VERSION_REVISION      13
#define QSV_MS_COUNT              14
#define QSV_TIME_LOW              15
#define QSV_TIME_HIGH             16
#define QSV_TOTPHYSMEM            17
#define QSV_TOTRESMEM             18
#define QSV_TOTAVAILMEM           19
#define QSV_MAXPRMEM              20
#define QSV_MAXSHMEM              21
#define QSV_TIMER_INTERVAL        22
#define QSV_MAX_COMP_LENGTH       23
#define QSV_FOREGROUND_FS_SESSION 24
#define QSV_FOREGROUND_PROCESS    25
#define QSV_NUMPROCESSORS         26
#define QSV_MAXHPRMEM             27
#define QSV_MAXHSHMEM             28
#define QSV_MAXPROCESSES          29
#define QSV_VIRTUALADDRESSLIMIT   30
#define QSV_INT10ENABLED          31
#define QSV_MAX                   QSV_INT10ENABLED

#define DSP_IMPLIEDCUR   1
#define DSP_PATHREF      2
#define DSP_IGNORENETERR 4

#define SPU_DISABLESUPPRESSION 0
#define SPU_ENABLESUPPRESSION  1
#define SPU_NOLOGCHANGE        2

#define BEGIN_LIBPATH 1
#define END_LIBPATH   2
#define LIBPATHSTRICT 3

APIRET APIENTRY DosErrClass(ULONG,PULONG,PULONG,PULONG);
APIRET APIENTRY DosError(ULONG);
APIRET APIENTRY DosGetMessage(PCHAR*,ULONG,PCHAR,ULONG,ULONG,PCSZ,PULONG);
APIRET APIENTRY DosInsertMessage(PCHAR*,ULONG,PCSZ,ULONG,PCHAR,ULONG,PULONG);
APIRET APIENTRY DosPutMessage(HFILE,ULONG,PCHAR);
APIRET APIENTRY DosQueryExtLIBPATH(PSZ,ULONG);
APIRET APIENTRY DosQueryMessageCP(PCHAR,ULONG,PCSZ,PULONG);
APIRET APIENTRY DosQuerySysInfo(ULONG,ULONG,PVOID,ULONG);
APIRET APIENTRY DosScanEnv(PCSZ,PSZ*);
APIRET APIENTRY DosSearchPath(ULONG,PCSZ,PCSZ,PBYTE,ULONG);
APIRET APIENTRY DosSetExtLIBPATH(PCSZ,ULONG);
APIRET APIENTRY DosSuppressPopUps(ULONG,CHAR);

#endif

#if defined(INCL_DOSSESMGR) || defined(INCL_DOSFILEMGR)

#define FAPPTYP_NOTSPEC         0x0000
#define FAPPTYP_NOTWINDOWCOMPAT 0x0001
#define FAPPTYP_WINDOWCOMPAT    0x0002
#define FAPPTYP_WINDOWAPI       0x0003
#define FAPPTYP_BOUND           0x0008
#define FAPPTYP_DLL             0x0010
#define FAPPTYP_DOS             0x0020
#define FAPPTYP_PHYSDRV         0x0040
#define FAPPTYP_VIRTDRV         0x0080
#define FAPPTYP_PROTDLL         0x0100
#define FAPPTYP_WINDOWSREAL     0x0200
#define FAPPTYP_WINDOWSPROT     0x0400
#define FAPPTYP_WINDOWSPROT31   0x1000
#define FAPPTYP_32BIT           0x4000
#define FAPPTYP_EXETYPE         0x0003

#endif

#ifdef INCL_DOSSESMGR

#define SSF_RELATED_INDEPENDENT 0
#define SSF_RELATED_CHILD       1

#define SSF_FGBG_FORE          0
#define SSF_FGBG_BACK          1

#define SSF_TRACEOPT_NONE      0
#define SSF_TRACEOPT_TRACE     1
#define SSF_TRACEOPT_TRACEALL  2

#define SSF_INHERTOPT_SHELL    0
#define SSF_INHERTOPT_PARENT   1

#define SSF_TYPE_DEFAULT       0
#define SSF_TYPE_FULLSCREEN    1
#define SSF_TYPE_WINDOWABLEVIO 2
#define SSF_TYPE_PM            3
#define SSF_TYPE_VDM           4
#define SSF_TYPE_GROUP         5
#define SSF_TYPE_DLL           6
#define SSF_TYPE_WINDOWEDVDM   7
#define SSF_TYPE_PDD           8
#define SSF_TYPE_VDD           9

#define SSF_CONTROL_VISIBLE     0x0000
#define SSF_CONTROL_INVISIBLE   0x0001
#define SSF_CONTROL_MAXIMIZE    0x0002
#define SSF_CONTROL_MINIMIZE    0x0004
#define SSF_CONTROL_NOAUTOCLOSE 0x0008
#define SSF_CONTROL_SETPOS      0x8000

#define SET_SESSION_UNCHANGED      0
#define SET_SESSION_SELECTABLE     1
#define SET_SESSION_NON_SELECTABLE 2
#define SET_SESSION_BOND           1
#define SET_SESSION_NO_BOND        2

#define STOP_SESSION_SPECIFIED     0
#define STOP_SESSION_ALL           1

typedef struct _STATUSDATA {
    USHORT Length;
    USHORT SelectInd;
    USHORT BondInd;
} STATUSDATA, *PSTATUSDATA;

typedef struct _STARTDATA {
    USHORT Length;
    USHORT Related;
    USHORT FgBg;
    USHORT TraceOpt;
    PSZ    PgmTitle;
    PSZ    PgmName;
    PBYTE  PgmInputs;
    PBYTE  TermQ;
    PBYTE  Environment;
    USHORT InheritOpt;
    USHORT SessionType;
    PSZ    IconFile;
    ULONG  PgmHandle;
    USHORT PgmControl;
    USHORT InitXPos;
    USHORT InitYPos;
    USHORT InitXSize;
    USHORT InitYSize;
    USHORT Reserved;
    PSZ    ObjectBuffer;
    ULONG  ObjectBuffLen;
} STARTDATA, *PSTARTDATA;

APIRET APIENTRY DosQueryAppType(PCSZ,PULONG);
APIRET APIENTRY DosSelectSession(ULONG);
APIRET APIENTRY DosSetSession(ULONG,PSTATUSDATA);
APIRET APIENTRY DosStartSession(PSTARTDATA,PULONG,PPID);
APIRET APIENTRY DosStopSession(ULONG,ULONG);

#endif

#ifdef INCL_DOSDEVICES

#define DEVINFO_PRINTER     0
#define DEVINFO_RS232       1
#define DEVINFO_FLOPPY      2
#define DEVINFO_COPROCESSOR 3
#define DEVINFO_SUBMODEL    4
#define DEVINFO_MODEL       5
#define DEVINFO_ADAPTER     6

#define INFO_COUNT_PARTITIONABLE_DISKS 1
#define INFO_GETIOCTLHANDLE            2
#define INFO_FREEIOCTLHANDLE           3

APIRET APIENTRY DosDevConfig(PVOID,ULONG);
APIRET APIENTRY DosDevIOCtl(HFILE,ULONG,ULONG,PVOID,ULONG,PULONG,PVOID,ULONG,PULONG);
APIRET APIENTRY DosPhysicalDisk(ULONG,PVOID,ULONG,PVOID,ULONG);

#endif

#ifdef INCL_DOSMVDM

typedef LHANDLE HVDD, *PHVDD;

APIRET APIENTRY DosCloseVDD(HVDD);
APIRET APIENTRY DosOpenVDD(PCSZ,PHVDD);
APIRET APIENTRY DosQueryDOSProperty(SGID,PCSZ,ULONG,PCSZ);
APIRET APIENTRY DosRequestVDD(HVDD,SGID,ULONG,ULONG,PVOID,ULONG,PVOID);
APIRET APIENTRY DosSetDOSProperty(SGID,PCSZ,ULONG,PCSZ);

#endif

#ifdef INCL_DOSPROFILE

#define PROF_ORDINAL 133

#define PROF_SYSTEM  0
#define PROF_USER    1
#define PROF_USEDD   2
#define PROF_KERNEL  4
#define PROF_VERBOSE 8
#define PROF_ENABLE  16

#define PROF_ALLOC         0
#define PROF_CLEAR         1
#define PROF_ON            2
#define PROF_OFF           3
#define PROF_DUMP          4
#define PROF_FREE          5
#define PROF_SHIFT         2
#define PROF_MOD_NAME_SIZE 10
#define PROF_END_OF_DATA   13

#define QS_PROCESS   0x0001
#define QS_SEMAPHORE 0x0002
#define QS_MTE       0x0004
#define QS_FILESYS   0x0008
#define QS_SHMEMORY  0x0010
#define QS_DISK      0x0020
#define QS_HWCONFIG  0x0040
#define QS_NAMEDPIPE 0x0080
#define QS_THREAD    0x0100
#define QS_MODVER    0x0200

#define QS_SUPPORTED (QS_PROCESS|QS_SEMAPHORE|QS_MTE|QS_FILESYS|QS_SHMEMORY|QS_MODVER)

#define QS_SYSSEM_WAITING           0x01
#define QS_SYSSEM_MUXWAITING        0x02
#define QS_SYSSEM_OWNER_DIED        0x04
#define QS_SYSSEM_EXCLUSIVE         0x08
#define QS_SYSSEM_NAME_CLEANUP      0x10
#define QS_SYSSEM_THREAD_OWNER_DIED 0x20
#define QS_SYSSEM_EXITLIST_OWNER    0x40

#define QS_DC_SEM_SHARED 0x0001
#define QS_DCMW_WAIT_ANY 0x0002
#define QS_DCMW_WAIT_ALL 0x0004
#define QS_DCM_MUTEX_SEM 0x0008
#define QS_DCE_EVENT_SEM 0x0010
#define QS_DCMW_MUX_SEM  0x0020
#define QS_DC_SEM_PM     0x0040
#define QS_DE_POSTED     0x0040
#define QS_DM_OWNER_DIED 0x0080
#define QS_DMW_MTX_MUX   0x0100
#define QS_DHO_SEM_OPEN  0x0200
#define QS_DE_16BIT_MW   0x0400
#define QS_DCE_POSTONE   0x0800
#define QS_DCE_AUTORESET 0x1000

#define QS_END          0

#define PADSHORT USHORT pad_sh
#define PADCHAR  UCHAR  pad_ch

#define CMD_KI_RDCNT 0x63

typedef struct _QSGREC {
    ULONG cThrds;
    ULONG c32SSem;
    ULONG cMFTNodes;
} QSGREC;

typedef struct _QSTREC {
    ULONG     RecType;
    USHORT    tid;
    USHORT    slot;
    ULONG     sleepid;
    ULONG     priority;
    ULONG     systime;
    ULONG     usertime;
    UCHAR     state;
    PADCHAR;
    PADSHORT;
} QSTREC;

typedef struct _QSPREC {
    ULONG      RecType;
    QSTREC FAR *pThrdRec;
    USHORT     pid;
    USHORT     ppid;
    ULONG      type;
    ULONG      stat;
    ULONG      sgid;
    USHORT     hMte;
    USHORT     cTCB;
    ULONG      c32PSem;
    VOID   FAR *p32SemRec;
    USHORT     c16Sem;
    USHORT     cLib;
    USHORT     cShrMem;
    USHORT     cFH;
    USHORT FAR *p16SemRec;
    USHORT FAR *pLibRec;
    USHORT FAR *pShrMemRec;
    USHORT FAR *pFSRec;
} QSPREC;

typedef struct _QSS16REC {
    ULONG  NextRec;
    USHORT SysSemOwner ;
    UCHAR  SysSemFlag ;
    UCHAR  SysSemRefCnt ;
    UCHAR  SysSemProcCnt ;
    UCHAR  SysSemPad ;
    USHORT pad_sh;
    USHORT SemPtr;
    CHAR   SemName;
} QSS16REC;

typedef struct _QSS16HEADREC {
    ULONG SRecType;
    ULONG SpNextRec;
    ULONG S32SemRec;
    ULONG S16TblOff;
    ULONG pSem16Rec;
} QSS16HEADREC;

typedef struct _QSMREC {
    ULONG  MemNextRec;
    USHORT hmem;
    USHORT sel;
    USHORT refcnt;
    CHAR   Memname;
} QSMREC;

typedef struct _QSOPENQ {
    USHORT pidOpener;
    USHORT OpenCt;
} QSOPENQ;

typedef struct _QSEVENT {
    ULONG  *pMuxQ;
    USHORT PostCt;
} QSEVENT;

typedef struct _QSMUTEX {
    ULONG  *pMuxQ;
    USHORT ReqCt;
    USHORT SlotNum;
} QSMUTEX;

typedef struct _QSMUX {
    VOID   *pSemRec;
    USHORT cSemRec;
    USHORT WaitCt;
} QSMUX;

typedef union _QSHUN {
    QSEVENT qsSEvt;
    QSMUTEX qsSMtx;
    QSMUX   qsSMux;
} QSHUN;

typedef struct _QSS32REC {
    VOID      *pNextRec;
    USHORT    flags;
    PADSHORT;
    UCHAR     *pName;
    QSHUN     qsh;
    ULONG     blockid;
    USHORT    index;
    USHORT    OpenCt;
    QSOPENQ   OpenQ[1];
} QSS32REC;

typedef struct _QSLOBJREC {
    ULONG oaddr;
    ULONG osize;
    ULONG oflags;
} QSLOBJREC;

typedef struct _QSLREC {
    VOID      FAR *pNextRec;
    USHORT        hmte;
    USHORT        fFlat;
    ULONG         ctImpMod;
    ULONG         ctObj;
    QSLOBJREC FAR *pObjInfo;
    UCHAR     FAR *pName;
} QSLREC;

typedef _Packed struct _QSEXLREC {
    struct    _QSEXLREC *next;
    USHORT    hndmod;
    USHORT    pid;
    USHORT    type;
    ULONG     refcnt;
    ULONG     segcnt;
    VOID      *_reserved_;
    UCHAR FAR *name;
    ULONG     ModuleVersion;
    UCHAR FAR *ShortModName;
    ULONG     modref;
} QSEXLREC;

typedef struct _QSSFT {
    USHORT sfn;
    USHORT refcnt;
    USHORT flags;
    USHORT flags2;
    USHORT mode;
    USHORT mode2;
    ULONG  size;
    USHORT hVPB;
    USHORT attr;
    PADSHORT;
} QSSFT;

typedef struct _QSFREC {
    ULONG RecType;
    VOID  *pNextRec;
    ULONG ctSft;
    QSSFT *pSft;
} QSFREC;

typedef struct _QSPTRREC {
    QSGREC       *pGlobalRec;
    QSPREC       *pProcRec;
    QSS16HEADREC *p16SemRec;
    QSS32REC     *p32SemRec;
    QSMREC       *pMemRec;
    QSLREC       *pLibRec;
    QSMREC       *pShrMemRec;
    QSFREC       *pFSRec;
} QSPTRREC;

typedef struct _CPUUTIL {
    ULONG ulTimeLow;
    ULONG ulTimeHigh;
    ULONG ulIdleLow;
    ULONG ulIdleHigh;
    ULONG ulBusyLow;
    ULONG ulBusyHigh;
    ULONG ulIntrLow;
    ULONG ulIntrHigh;
} CPUUTIL, *PCPUUTIL;

APIRET APIENTRY DosAliasPerfCtrs(ULONG,ULONG,PBYTE*,PULONG);
APIRET APIENTRY DosConfigurePerf(ULONG,ULONG,ULONG,ULONG,PCSZ,BOOL32);
APIRET APIENTRY DosDeconPerf(VOID);
APIRET APIENTRY DosPerfSysCall(ULONG,ULONG,ULONG,ULONG);
APIRET APIENTRY DosQuerySysState(ULONG,ULONG,PID,TID,PVOID,ULONG);
APIRET APIENTRY DosRegisterPerfCtrs(PBYTE,PBYTE,ULONG);
APIRET APIENTRY DosTmrQueryFreq(PULONG);
APIRET APIENTRY DosTmrQueryTime(PQWORD);

#endif

#ifdef INCL_DOSSPINLOCK

#define PROC_OFFLINE 0
#define PROC_ONLINE  1

typedef ULONG HSPINLOCK, *PHSPINLOCK;

VOID   APIENTRY DosAcquireSpinLock(HSPINLOCK);
APIRET APIENTRY DosCreateSpinLock(PHSPINLOCK);
APIRET APIENTRY DosFreeSpinLock(HSPINLOCK);
APIRET APIENTRY DosGetProcessorStatus(ULONG,PULONG);
APIRET APIENTRY DosPerfSysCall(ULONG,ULONG,ULONG,ULONG);
VOID   APIENTRY DosReleaseSpinLock(HSPINLOCK);
APIRET APIENTRY DosSetProcessorStatus(ULONG,ULONG);
APIRET APIENTRY DosTestPSD(PCSZ);

#endif

#ifdef INCL_BDCALLS

#include <bdcalls.h>

#endif

#endif
