#ifndef	_INC_TOOLHELP
#define	_INC_TOOLHELP

#ifndef	_INC_WINDOWS
#include <windows.h>
#endif

#ifdef	__cplusplus
extern	"C" {
#endif

#pragma pack(push,1)

#define	MAX_DATA	11
#define	MAX_PATH	255
#define	MAX_MODULE_NAME	8 + 1
#define	MAX_CLASSNAME	255
#define	GLOBAL_ALL	0
#define	GLOBAL_LRU	1
#define	GLOBAL_FREE	2
#define	GT_UNKNOWN	0
#define	GT_DGROUP	1
#define	GT_DATA	2
#define	GT_CODE	3
#define	GT_TASK	4
#define	GT_RESOURCE	5
#define	GT_MODULE	6
#define	GT_FREE	7
#define	GT_INTERNAL	8
#define	GT_SENTINEL	9
#define	GT_BURGERMASTER	10
#define	GD_USERDEFINED	0
#define	GD_CURSORCOMPONENT	1
#define	GD_BITMAP	2
#define	GD_ICONCOMPONENT	3
#define	GD_MENU	4
#define	GD_DIALOG	5
#define	GD_STRING	6
#define	GD_FONTDIR	7
#define	GD_FONT	8
#define	GD_ACCELERATORS	9
#define	GD_RCDATA	10
#define	GD_ERRTABLE	11
#define	GD_CURSOR	12
#define	GD_ICON	14
#define	GD_NAMETABLE	15
#define	GD_MAX_RESOURCE	15
#define	GF_PDB_OWNER	0x0100
#define	NORMAL_HEAP	0
#define	USER_HEAP	1
#define	GDI_HEAP	2
#define	LF_FIXED	1
#define	LF_FREE	2
#define	LF_MOVEABLE	4
#define	LT_NORMAL	0
#define	LT_FREE	0xff
#define	LT_GDI_PEN	1
#define	LT_GDI_BRUSH	2
#define	LT_GDI_FONT	3
#define	LT_GDI_PALETTE	4
#define	LT_GDI_BITMAP	5
#define	LT_GDI_RGN	6
#define	LT_GDI_DC	7
#define	LT_GDI_DISABLED_DC	8
#define	LT_GDI_METADC	9
#define	LT_GDI_METAFILE	10
#define	LT_GDI_MAX	LT_GDI_METAFILE
#define	LT_USER_CLASS	1
#define	LT_USER_WND	2
#define	LT_USER_STRING	3
#define	LT_USER_MENU	4
#define	LT_USER_CLIP	5
#define	LT_USER_CBOX	6
#define	LT_USER_PALETTE	7
#define	LT_USER_ED	8
#define	LT_USER_BWL	9
#define	LT_USER_OWNERDRAW	10
#define	LT_USER_SPB	11
#define	LT_USER_CHECKPOINT	12
#define	LT_USER_DCE	13
#define	LT_USER_MWP	14
#define	LT_USER_PROP	15
#define	LT_USER_LBIV	16
#define	LT_USER_MISC	17
#define	LT_USER_ATOMS	18
#define	LT_USER_LOCKINPUTSTATE	19
#define	LT_USER_HOOKLIST	20
#define	LT_USER_USERSEEUSERDOALLOC	21
#define	LT_USER_HOTKEYLIST	22
#define	LT_USER_POPUPMENU	23
#define	LT_USER_HANDLETABLE	32
#define	LT_USER_MAX	LT_USER_HANDLETABLE
#define	FRAME_FAR	0
#define	FRAME_NEAR	1
#define	INT_DIV0	0
#define	INT_1	1
#define	INT_3	3
#define	INT_UDINSTR	6
#define	INT_STKFAULT	12
#define	INT_GPFAULT	13
#define	INT_BADPAGEFAULT	14
#define	INT_CTLALTSYSRQ	256
#define	NFY_UNKNOWN	0
#define	NFY_LOADSEG	1
#define	NFY_FREESEG	2
#define	NFY_STARTDLL	3
#define	NFY_STARTTASK	4
#define	NFY_EXITTASK	5
#define	NFY_DELMODULE	6
#define	NFY_RIP	7
#define	NFY_TASKIN	8
#define	NFY_TASKOUT	9
#define	NFY_INCHAR	10
#define	NFY_OUTSTR	11
#define	NFY_LOGERROR	12
#define	NFY_LOGPARAMERROR	13
#define	NF_NORMAL	0
#define	NF_TASKSWITCH	1
#define	NF_RIP	2
#define	UAE_BOX	0
#define	NO_UAE_BOX	1

typedef	struct tagGLOBALINFO {
	DWORD	dwSize;
	WORD	wcItems;
	WORD	wcItemsFree;
	WORD	wcItemsLRU;
} GLOBALINFO,FAR *LPGLOBALINFO;
typedef	struct tagGLOBALENTRY {
	DWORD	dwSize;
	DWORD	dwAddress;
	DWORD	dwBlockSize;
	HGLOBAL	hBlock;
	WORD	wcLock;
	WORD	wcPageLock;
	WORD	wFlags;
	BOOL	wHeapPresent;
	HGLOBAL	hOwner;
	WORD	wType;
	WORD	wData;
	DWORD	dwNext;
	DWORD	dwNextAlt;
} GLOBALENTRY,FAR *LPGLOBALENTRY;
typedef	struct tagLOCALINFO {
	DWORD	dwSize;
	WORD	wcItems;
} LOCALINFO,FAR *LPLOCALINFO;
typedef	struct tagLOCALENTRY {
	DWORD	dwSize;
	HLOCAL	hHandle;
	WORD	wAddress;
	WORD	wSize;
	WORD	wFlags;
	WORD	wcLock;
	WORD	wType;
	WORD	hHeap;
	WORD	wHeapType;
	WORD	wNext;
} LOCALENTRY,FAR *LPLOCALENTRY;
typedef	struct tagSTACKTRACEENTRY {
	DWORD	dwSize;
	HTASK	hTask;
	WORD	wSS;
	WORD	wBP;
	WORD	wCS;
	WORD	wIP;
	HMODULE	hModule;
	WORD	wSegment;
	WORD	wFlags;
} STACKTRACEENTRY,FAR *LPSTACKTRACEENTRY;
typedef	struct tagMODULEENTRY {
	DWORD	dwSize;
	char	szModule[MAX_MODULE_NAME + 1];
	HMODULE	hModule;
	WORD	wcUsage;
	char	szExePath[MAX_PATH + 1];
	WORD	wNext;
} MODULEENTRY,FAR *LPMODULEENTRY;
typedef	struct tagTASKENTRY {
	DWORD	dwSize;
	HTASK	hTask;
	HTASK	hTaskParent;
	HINSTANCE	hInst;
	HMODULE	hModule;
	WORD	wSS;
	WORD	wSP;
	WORD	wStackTop;
	WORD	wStackMinimum;
	WORD	wStackBottom;
	WORD	wcEvents;
	HGLOBAL	hQueue;
	char	szModule[MAX_MODULE_NAME + 1];
	WORD	wPSPOffset;
	HANDLE	hNext;
} TASKENTRY,FAR *LPTASKENTRY;
typedef	struct tagCLASSENTRY {
	DWORD	dwSize;
	HMODULE	hInst;
	char	szClassName[MAX_CLASSNAME + 1];
	WORD	wNext;
} CLASSENTRY,FAR *LPCLASSENTRY;
typedef	struct tagMEMMANINFO {
	DWORD	dwSize;
	DWORD	dwLargestFreeBlock;
	DWORD	dwMaxPagesAvailable;
	DWORD	dwMaxPagesLockable;
	DWORD	dwTotalLinearSpace;
	DWORD	dwTotalUnlockedPages;
	DWORD	dwFreePages;
	DWORD	dwTotalPages;
	DWORD	dwFreeLinearSpace;
	DWORD	dwSwapFilePages;
	WORD	wPageSize;
} MEMMANINFO,FAR *LPMEMMANINFO;
typedef	struct tagSYSHEAPINFO {
	DWORD	dwSize;
	WORD	wUserFreePercent;
	WORD	wGDIFreePercent;
	HGLOBAL	hUserSegment;
	HGLOBAL	hGDISegment;
} SYSHEAPINFO,FAR *LPSYSHEAPINFO;
typedef	struct tagNFYLOADSEG {
	DWORD	dwSize;
	WORD	wSelector;
	WORD	wSegNum;
	WORD	wType;
	WORD	wcInstance;
	LPCSTR	lpstrModuleName;
} NFYLOADSEG;
typedef	struct tagNFYSTARTDLL {
	DWORD	dwSize;
	HMODULE	hModule;
	WORD	wCS;
	WORD	wIP;
} NFYSTARTDLL;
typedef	struct tagNFYRIP {
	DWORD	dwSize;
	WORD	wIP;
	WORD	wCS;
	WORD	wSS;
	WORD	wBP;
	WORD	wExitCode;
} NFYRIP;
typedef	struct tagNFYLOGERROR {
	DWORD	dwSize;
	UINT	wErrCode;
	LPVOID lpInfo;
} NFYLOGERROR;
typedef	struct tagNFYLOGPARAMERROR {
	DWORD	dwSize;
	UINT	wErrCode;
	FARPROC	lpfnErrorAddr;
	void FAR* FAR *lpBadParam;
} NFYLOGPARAMERROR;
typedef	struct tagTIMERINFO {
	DWORD	dwSize;
	DWORD	dwmsSinceStart;
	DWORD	dwmsThisVM;
} TIMERINFO,FAR *LPTIMERINFO;
typedef	BOOL (CALLBACK *LPFNNOTIFYCALLBACK)(WORD,DWORD);

BOOL	WINAPI GlobalInfo(LPGLOBALINFO);
BOOL	WINAPI GlobalFirst(LPGLOBALENTRY,WORD);
BOOL	WINAPI GlobalNext(LPGLOBALENTRY,WORD);
BOOL	WINAPI GlobalEntryHandle(LPGLOBALENTRY,HGLOBAL);
BOOL	WINAPI GlobalEntryModule(LPGLOBALENTRY,HMODULE,WORD);
WORD	WINAPI GlobalHandleToSel(HGLOBAL);
BOOL	WINAPI LocalInfo(LPLOCALINFO,HGLOBAL);
BOOL	WINAPI LocalFirst(LPLOCALENTRY,HGLOBAL);
BOOL	WINAPI LocalNext(LPLOCALENTRY);
BOOL	WINAPI StackTraceFirst(LPSTACKTRACEENTRY,HTASK);
BOOL	WINAPI StackTraceCSIPFirst(LPSTACKTRACEENTRY,WORD,WORD,WORD,WORD);
BOOL	WINAPI StackTraceNext(LPSTACKTRACEENTRY);
BOOL	WINAPI ModuleFirst(LPMODULEENTRY);
BOOL	WINAPI ModuleNext(LPMODULEENTRY);
HMODULE	WINAPI ModuleFindName(LPMODULEENTRY,LPCSTR);
HMODULE	WINAPI ModuleFindHandle(LPMODULEENTRY,HMODULE);
BOOL	WINAPI TaskFirst(LPTASKENTRY);
BOOL	WINAPI TaskNext(LPTASKENTRY);
BOOL	WINAPI TaskFindHandle(LPTASKENTRY,HTASK);
DWORD	WINAPI TaskSetCSIP(HTASK,WORD,WORD);
DWORD	WINAPI TaskGetCSIP(HTASK);
BOOL	WINAPI TaskSwitch(HTASK,DWORD);
BOOL	WINAPI ClassFirst(LPCLASSENTRY);
BOOL	WINAPI ClassNext(LPCLASSENTRY);
BOOL	WINAPI MemManInfo(LPMEMMANINFO);
BOOL	WINAPI SystemHeapInfo(LPSYSHEAPINFO);
BOOL	WINAPI InterruptRegister(HTASK,FARPROC);
BOOL	WINAPI InterruptUnRegister(HTASK);
BOOL	WINAPI NotifyRegister(HTASK,LPFNNOTIFYCALLBACK,WORD);
BOOL	WINAPI NotifyUnRegister(HTASK);
void	WINAPI TerminateApp(HTASK,WORD);
DWORD	WINAPI MemoryRead(WORD,DWORD,LPVOID,DWORD);
DWORD	WINAPI MemoryWrite(WORD,DWORD,LPVOID,DWORD);
BOOL	WINAPI TimerCount(LPTIMERINFO);

#pragma pack(pop)

#ifdef	__cplusplus
}
#endif

#endif
