/*
    OS/2 Presentation Manager SetErrorInfo constants and function declaration.
*/

#define SEI_INCLUDED

#define SEI_BREAKPOINT   0x8000
#define SEI_NOBEEP       0x4000
#define SEI_NOPROMPT     0x2000
#define SEI_DBGRSRVD     0x1000
#define SEI_DEBUGONLY    (SEI_BREAKPOINT | SEI_NOBEEP | SEI_NOPROMPT | SEI_RESERVED)

#define SEI_STACKTRACE   0x0001
#define SEI_REGISTERS    0x0002
#define SEI_ARGCOUNT     0x0004
#define SEI_DOSERROR     0x0008
#define SEI_RESERVED     0x0FE0

ERRORID APIENTRY WinSetErrorInfo(ERRORID,ULONG,...);
