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
* Description:  DOS standard debugger access functions.
*
****************************************************************************/


#include <string.h>
#include <i86.h>
#include "tinyio.h"
#include "dbg386.h"
#include "drset.h"
#include "doshdl.h"
#include "exedos.h"
#include "exeos2.h"
#include "exephar.h"
#include "trperr.h"
#define ERR_CODES
#include "dosmsgs.h"
#undef ERR_CODES
#include "trpimp.h"
#include "ioports.h"
#include "winchk.h"
#include "madregs.h"

typedef enum {
    EXE_UNKNOWN,
    EXE_DOS,                    /* DOS */
    EXE_OS2,                    /* OS/2 */
    EXE_PHARLAP_SIMPLE,         /* PharLap Simple */
    EXE_PHARLAP_EXTENDED_286,   /* PharLap Extended 286 */
    EXE_PHARLAP_EXTENDED_386,   /* PharLap Extended 386 (may be bound) */
    EXE_RATIONAL_386,           /* Rational DOS/4G app */
    EXE_LAST_TYPE
} EXE_TYPE;

#pragma aux MoveBytes =                                         \
/*      MoveBytes( fromseg, fromoff, toseg, tooff, len );*/     \
0X1E            /* push   ds                            */      \
0X8E 0XD8       /* mov    ds,ax                         */      \
0XF3            /* rep                                  */      \
0XA4            /* movsb                                */      \
0X1F            /* pop    ds                            */      \
        parm    caller  [ ax ] [ si ] [ es ] [ di ] [ cx ]      \
        modify  [ si di ];

#pragma aux MyCS =              \
0x8c 0xc8       /* mov ax,cx */ \
        value [ax];

#pragma aux MyFlags =           \
0x9c            /* pushf    */  \
0x58            /* pop ax   */  \
        value [ax];

extern void MoveBytes();
extern unsigned short MyCS( void );
extern unsigned short MyFlags( void );


typedef _Packed struct pblock {
    addr_seg    envstring;
    addr32_ptr  commandln;
    addr32_ptr  fcb01;
    addr32_ptr  fcb02;
    addr32_ptr  startsssp;
    addr32_ptr  startcsip;
} pblock;

#define CMD_OFFSET      0x80

//
// NOTE: if you change this structure, you must update DBGTRAP.ASM
//
typedef struct watch {
    addr32_ptr  addr;
    dword       value;
    dword       linear;
    short       dregs;
    short       len;
} watch;

#define MAX_WP  32
watch   WatchPoints[ MAX_WP ];
short   WatchCount;

typedef enum {
        TRAP_SKIP = -1,
        TRAP_NONE,
        TRAP_TRACE_POINT,
        TRAP_BREAK_POINT,
        TRAP_WATCH_POINT,
        TRAP_USER,
        TRAP_TERMINATE,
        TRAP_MACH_EXCEPTION,
        TRAP_OVL_CHANGE
} trap_types;

/* user modifiable flags */
#define USR_FLAGS (FLG_C | FLG_P | FLG_A | FLG_Z | FLG_S | \
            FLG_I | FLG_D | FLG_O)

extern void             InitRedirect(void);
extern addr_seg         DbgPSP(void);
extern long             DOSLoadProg(char *, pblock *);
extern addr_seg         DOSTaskPSP(void);
extern void             EndUser(void);
extern unsigned_8       RunProg(trap_cpu_regs *, trap_cpu_regs *);
extern void             SetWatch386();
extern void             SetWatchPnt(unsigned, watch far *);
extern void             SetSingleStep(void);
extern void             SetSingle386(void);
extern void             SetDbgTask(void);
extern void             SetUsrTask(void);
extern void             InitVectors(void);
extern void             FiniVectors(void);
extern void             TrapTypeInit(void);
extern void             ClrIntVecs(void);
extern void             SetIntVecs(void);
extern void             DoRemInt(trap_cpu_regs *, unsigned);
extern unsigned         X86CPUType(void);
extern char             NPXType(void);
extern char             Have87Emu(void);
extern void             Null87Emu( void );
extern void             OvlTrap( int );
extern void             Read87State( void * );
extern void             Read87EmuState( void * );
extern void             Write87State( void * );
extern void             Write87EmuState( void * );
extern tiny_ret_t       FindFilePath( char *, char *, char * );
extern unsigned         Redirect( bool );
extern unsigned         ExceptionText( unsigned, char * );
extern unsigned         StringToFullPath( char * );
extern void             FPUContract( void * );
extern void             FPUExpand( void * );
extern int              far NoOvlsHdlr( int, void * );
extern bool             CheckOvl( addr32_ptr );
extern int              NullOvlHdlr(void);

extern word             far SegmentChain;

static tiny_handle_t    EXE;
static tiny_ftime_t     EXETime;
static tiny_fdate_t     EXEDate;
#define ReadEXE( x )    TinyRead( EXE, &x, sizeof(x) )
#define WriteEXE( x )   TinyWrite( EXE, &x, sizeof(x) )
#define SeekEXE( x )    TinySeek( EXE, x, TIO_SEEK_START )
static dword            NEOffset;
static word             NumSegments;
static dword            SegTable;
static dword            StartByte;
static byte             SavedByte;
static addr48_ptr       BadBreak;
static bool             GotABadBreak;
static int              ExceptNum;


trap_cpu_regs   TaskRegs;
char            DOS_major;
char            DOS_minor;
char            RealNPXType;
bool            BoundAppLoading;
bool            IsBreak[4];

struct {
    unsigned    Is386       : 1;
    unsigned    DRsOn       : 1;
    unsigned    com_file    : 1;
    unsigned    NoOvlMgr    : 1;
    unsigned    BoundApp    : 1;
}               Flags;


#ifdef DEBUG_ME
int out( char * str )
{
    char *p;

    p = str;
    while( *p ) ++p;
    TinyWrite( 1, str, p - str );
    return 0;
}

static char hexbuff[80];

char * hex( unsigned long num )
{
    char *p;

    p = &hexbuff[79];
    *p = 0;
    if( num == 0 ) {
      *--p = '0';
      return( p );
    }
    while( num != 0 ) {
        *--p = "0123456789abcdef"[ num & 15 ];
        num >>= 4;
    }
    return( p );

#ifndef TRACE_ME
    #undef put
    #define put( s )    out( s )
#endif
}
#else
    #define out( s ) 0
    #define put( s )
    #define hex( n ) 1
#endif

#ifndef put
    #define put( s )
#endif

unsigned ReqGet_sys_config()
{
    get_sys_config_ret  *ret;

    ret = GetOutPtr(0);
    ret->sys.os = OS_DOS;
    ret->sys.osmajor = DOS_major;
    ret->sys.osminor = DOS_minor;
    ret->sys.cpu = X86CPUType();
    if( ret->sys.cpu >= 3 ) {
        Flags.Is386 = TRUE;
    } else {
        Flags.Is386 = FALSE;
    }
    if( Have87Emu() ) {
        ret->sys.fpu = X86_EMU;
    } else if( RealNPXType != 0 ) {
        if( ret->sys.cpu >= 4 ) {
            ret->sys.fpu = ret->sys.cpu;
        } else {
            ret->sys.fpu = RealNPXType;
        }
    } else {
        ret->sys.fpu = X86_NO;
    }
    ret->sys.huge_shift = 12;
    ret->sys.mad = MAD_X86;
    return( sizeof( *ret ) );
}


unsigned ReqMap_addr()
{
    word        seg;
    int         count;
    word        *segment;
    map_addr_req        *acc;
    map_addr_ret        *ret;

    acc = GetInPtr(0);
    ret = GetOutPtr(0);
    seg = acc->in_addr.segment;
    switch( seg ) {
    case MAP_FLAT_CODE_SELECTOR:
    case MAP_FLAT_DATA_SELECTOR:
        seg = 0;
        break;
    }
    if( Flags.BoundApp ) {
        count = NumSegments - seg;
        segment = MK_FP( SegmentChain, 14 );
        while( count != 0 ) {
            segment = MK_FP( *segment, 14 );
            --count;
        }
        ret->out_addr.segment = FP_SEG( segment ) + 1;
    } else {
        ret->out_addr.segment = DOSTaskPSP() + seg;
        if( !Flags.com_file ) ret->out_addr.segment += 0x10;
    }
    ret->out_addr.offset = acc->in_addr.offset;
    ret->lo_bound = 0;
    ret->hi_bound = ~(addr48_off)0;
    return( sizeof( *ret ) );
}

//OBSOLETE - use ReqMachine_data
unsigned ReqAddr_info()
{
    addr_info_ret       *ret;

    ret = GetOutPtr( 0 );
    ret->is_32 = FALSE;
    return( sizeof( *ret ) );
}

unsigned ReqMachine_data()
{
    machine_data_ret    *ret;
    unsigned_8          *data;

    ret = GetOutPtr( 0 );
    data = GetOutPtr( sizeof( *ret ) );
    ret->cache_start = 0;
    ret->cache_end = ~(addr_off)0;
    *data = 0;
    return( sizeof( *ret ) + sizeof( *data ) );
}

unsigned ReqChecksum_mem()
{
    unsigned_8     *ptr;
    unsigned long   sum = 0;
    unsigned        len;
    checksum_mem_req    *acc;
    checksum_mem_ret    *ret;

    acc = GetInPtr(0);
    ret = GetOutPtr(0);
    ptr = MK_FP( acc->in_addr.segment, acc->in_addr.offset );
    for( len = acc->len; len != 0; --len ) {
        sum += *ptr++;
    }
    ret->result = sum;
    return( sizeof( *ret ) );
}


static bool IsInterrupt( addr48_ptr addr, unsigned length )
{
    unsigned long start, end;

    start = ((unsigned long)addr.segment << 4) + addr.offset;
    end = start + length;
    return( start < 0x400 || end < 0x400 );
}


unsigned ReqRead_mem()
{
    bool          int_tbl;
    read_mem_req        *acc;
    void          *data;
    unsigned    len;

    acc = GetInPtr(0);
    data = GetOutPtr( 0 );
    acc->mem_addr.offset &= 0xffff;
    int_tbl = IsInterrupt( acc->mem_addr, acc->len );
    if( int_tbl ) SetIntVecs();
    len = acc->len;
    if( ( acc->mem_addr.offset + len ) > 0xffff ) {
        len = 0x10000 - acc->mem_addr.offset;
    }
    MoveBytes( acc->mem_addr.segment, acc->mem_addr.offset,
               FP_SEG( data ), FP_OFF( data ), len );
    if( int_tbl ) ClrIntVecs();
    return( len );
}


unsigned ReqWrite_mem()
{
    bool          int_tbl;
    write_mem_req       *acc;
    write_mem_ret       *ret;
    unsigned      len;
    void          *data;

    acc = GetInPtr(0);
    ret = GetOutPtr(0);
    data = GetInPtr(sizeof(*acc));
    len = GetTotalSize() - sizeof(*acc);

    acc->mem_addr.offset &= 0xffff;
    int_tbl = IsInterrupt( acc->mem_addr, len );
    if( int_tbl ) SetIntVecs();
    if( ( acc->mem_addr.offset + len ) > 0xffff ) {
        len = 0x10000 - acc->mem_addr.offset;
    }
    MoveBytes( FP_SEG( data ), FP_OFF( data ),
               acc->mem_addr.segment, acc->mem_addr.offset, len );
    if( int_tbl ) ClrIntVecs();
    ret->len = len;
    return( sizeof( *ret ) );
}


unsigned ReqRead_io()
{
    read_io_req *acc;
    void        *data;
    unsigned    len;

    acc = GetInPtr(0);
    data = GetOutPtr(0);
    if( acc->len == 1 ) {
       *( (byte far *)data ) = In_b( acc->IO_offset );
       len = 1;
    } else if( acc->len == 2 ) {
       *( (word far *)data ) = In_w( acc->IO_offset );
       len = 2;
    } else if( Flags.Is386 ) {
       *( (dword far *)data ) = In_d( acc->IO_offset );
       len = 4;
    } else {
       len = 0;
    }
    return( len );
}


unsigned ReqWrite_io()
{
    write_io_req        *acc;
    write_io_ret        *ret;
    void         *data;
    unsigned            len;

    acc = GetInPtr(0);
    data = GetInPtr( sizeof( *acc ) );
    len = GetTotalSize() - sizeof( *acc );
    ret = GetOutPtr(0);
    if( len == 1 ) {
        Out_b( acc->IO_offset, *( (byte far *)data ) );
        ret->len = 1;
    } else if( len == 2 ) {
        Out_w( acc->IO_offset, *( (word far *)data ) );
        ret->len = 2;
    } else if ( Flags.Is386 ) {
        Out_d( acc->IO_offset, *( (dword far *)data ) );
        ret->len = 4;
    } else {
        ret->len = 0;
    }
    return( sizeof( *ret ) );
}

//OBSOLETE - use ReqRead_regs
unsigned ReqRead_cpu()
{
    void          *regs;
    read_cpu_ret        *ret;

    ret = GetOutPtr( 0 );
    regs = GetOutPtr( sizeof( *ret ) );
    ret->cpu = TaskRegs;
    return( sizeof( *ret ) );
}

//OBSOLETE - use ReqRead_regs
unsigned ReqRead_fpu()
{
    void *regs;

    regs = GetOutPtr(0);
    if( Have87Emu() ) {
        Read87EmuState( regs );
    } else if( RealNPXType != 0 ) {
        Read87State( regs );
    } else {
        return( 0 );
    }
    FPUExpand( regs );
    return( sizeof( trap_fpu_regs ) );
}

//OBSOLETE - use ReqWrite_regs
unsigned ReqWrite_cpu()
{
    trap_cpu_regs *regs;

    regs = GetInPtr(sizeof(write_cpu_req));
    TaskRegs = *regs;
    return( 0 );
}

//OBSOLETE - use ReqWrite_regs
unsigned ReqWrite_fpu()
{
    void *regs;

    regs = GetInPtr(sizeof(write_fpu_req));
    FPUContract( regs );
    if( Have87Emu() ) {
        Write87EmuState( regs );
    } else if( RealNPXType != 0 ) {
        Write87State( regs );
    }
    return( 0 );
}

unsigned ReqRead_regs( void )
{
    mad_registers       *mr;

    mr = GetOutPtr(0);
    mr->x86.cpu = *(struct x86_cpu *)&TaskRegs;
    if( Have87Emu() ) {
        Read87EmuState( &mr->x86.fpu );
    } else if( RealNPXType != 0 ) {
        Read87State( &mr->x86.fpu );
    } else {
        memset( &mr->x86.fpu, 0, sizeof( mr->x86.fpu ) );
    }
    FPUExpand( &mr->x86.fpu );
    return( sizeof( mr->x86 ) );
}

unsigned ReqWrite_regs( void )
{
    mad_registers       *mr;

    mr = GetInPtr(sizeof(write_regs_req));
    *(struct x86_cpu *)&TaskRegs = mr->x86.cpu;
    FPUContract( &mr->x86.fpu );
    if( Have87Emu() ) {
        Write87EmuState( &mr->x86.fpu );
    } else if( RealNPXType != 0 ) {
        Write87State( &mr->x86.fpu );
    }
    return( 0 );
}

static EXE_TYPE CheckEXEType( char *name )
{
    tiny_ret_t  rc;
    union {
        tiny_ret_t          rc;
        tiny_file_stamp_t   stamp;
    }           exe_time;
    word        value;
    byte        breakpt;
    static dos_exe_header head;
    static os2_exe_header os2_head;

    Flags.com_file = FALSE;
    EXE = 0;
    rc = TinyOpen( name, TIO_READ_WRITE );
    if( TINY_ERROR( rc ) ) return( EXE_UNKNOWN );
    EXE = rc;
    exe_time.rc = TinyGetFileStamp( EXE );
    EXETime = exe_time.stamp.time;
    EXEDate = exe_time.stamp.date;
    if( ReadEXE( head ) < 0 ) return( EXE_UNKNOWN );    /* MZ Signature */
    switch( head.signature ) {
    case SIMPLE_SIGNATURE: // mp
    case REX_SIGNATURE: // mq
    case EXTENDED_SIGNATURE: // 'P3'
        return( EXE_PHARLAP_SIMPLE );
    case DOS_SIGNATURE:
        if( head.reloc_offset != OS2_EXE_HEADER_FOLLOWS ) return( EXE_DOS );
        if( SeekEXE( OS2_NE_OFFSET ) < 0 ) return( EXE_UNKNOWN );/* offset of new exe */
        if( ReadEXE( NEOffset ) < 0 ) return( EXE_UNKNOWN );
        if( SeekEXE( NEOffset ) < 0 ) return( EXE_UNKNOWN );
        if( ReadEXE( os2_head ) < 0 ) return( EXE_UNKNOWN );/* NE Signature */
        if( os2_head.signature == RAT_SIGNATURE_WORD ) return( EXE_RATIONAL_386 );
        if( os2_head.signature != OS2_SIGNATURE_WORD ) return( EXE_UNKNOWN );
        NumSegments = os2_head.segments;
        SegTable = NEOffset + os2_head.segment_off;
        if( os2_head.align == 0 ) os2_head.align = 9;
        SeekEXE( SegTable+(os2_head.entrynum-1)*8 );
        ReadEXE( value );
        StartByte = ( (long)value << os2_head.align ) + os2_head.IP;
        SeekEXE( StartByte );
        ReadEXE( SavedByte );
        breakpt = 0xCC;
        SeekEXE( StartByte );
        rc = WriteEXE( breakpt );
        return( EXE_OS2 );
    default:
        Flags.com_file = TRUE;
        return( EXE_UNKNOWN );
    }
}

static char DosExtList[] = { ".com\0.exe\0" };

unsigned ReqProg_load()
{
    addr_seg    psp;
    pblock      parmblock;
    long        rc;
    char        *parm;
    char        *src;
    char        *dst;
    char        exe_name[128];
    char        ch;
    EXE_TYPE    exe;
    prog_load_ret       *ret;
    char        *end;

    ExceptNum = -1;
    ret = GetOutPtr( 0 );
    memset( &TaskRegs, 0, sizeof( TaskRegs ) );
    TaskRegs.EFL = MyFlags() & ~USR_FLAGS;
    /* build a DOS command line parameter in our PSP command area */
    Flags.BoundApp = FALSE;
    psp = DbgPSP();
    parm = GetInPtr( sizeof( prog_load_req ) );
    if( FindFilePath( parm, exe_name, DosExtList ) != 0 ) {
        exe_name[0] = '\0';
    }
    while( *parm != '\0' ) ++parm;
    src = ++parm;
    dst = MK_FP( psp, CMD_OFFSET+1 );
    end = (char *)GetInPtr( GetTotalSize()-1 );
    for( ;; ) {
        if( src > end ) break;
        ch = *src;
        if( ch == '\0' ) ch = ' ';
        *dst = ch;
        ++dst;
        ++src;
    }
    if( src > parm ) --dst;
    *dst = '\r';
    parm = MK_FP( psp, CMD_OFFSET );
    *parm = FP_OFF( dst ) - (CMD_OFFSET+1);
    parmblock.envstring = NULL;
    parmblock.commandln.segment = psp;
    parmblock.commandln.offset =  CMD_OFFSET;
    parmblock.fcb01.segment = psp;
    parmblock.fcb02.segment = psp;
    parmblock.fcb01.offset  = 0X005C;
    parmblock.fcb02.offset  = 0X006C;
    exe = CheckEXEType( exe_name );
    if( EXE != 0 ) {
        TinyClose( EXE );
        EXE = 0;
    }
    switch( exe ) {
    case EXE_RATIONAL_386:
        ret->err = ERR_RATIONAL_EXE;
        return( sizeof( *ret ) );
    case EXE_PHARLAP_SIMPLE:
        ret->err = ERR_PHARLAP_EXE;
        return( sizeof( *ret ) );
    }
    SegmentChain = 0;
    BoundAppLoading = FALSE;
    rc = DOSLoadProg( exe_name, &parmblock );
    if( rc >= 0 ) {
        rc = 0;
        TaskRegs.SS = parmblock.startsssp.segment;
        /* for some insane reason DOS returns a starting SP two less then
           normal */
        TaskRegs.ESP = parmblock.startsssp.offset + 2;
        TaskRegs.CS = parmblock.startcsip.segment;
        TaskRegs.EIP = parmblock.startcsip.offset;
        psp = DOSTaskPSP();
    } else {
        psp = TinyAllocBlock( TinyAllocBlock( 0xffff ) );
        TinyFreeBlock( psp );
        TaskRegs.SS = psp + 0x10;
        TaskRegs.ESP = 0xfffe;
        TaskRegs.CS = psp + 0x10;
        TaskRegs.EIP = 0x100;
    }
    TaskRegs.DS = psp;
    TaskRegs.ES = psp;
    if( rc == 0 ) {
        if( Flags.NoOvlMgr || !CheckOvl( parmblock.startcsip ) ) {
            if( exe == EXE_OS2 ) {
                BoundAppLoading = TRUE;
                RunProg( &TaskRegs, &TaskRegs );
                parm = MK_FP(TaskRegs.CS, TaskRegs.EIP);
                if( *parm == 0xCC ) {
                    *parm = SavedByte;
                }
                BoundAppLoading = FALSE;
                rc = TinyOpen( exe_name, TIO_READ_WRITE );
                if( !TINY_ERROR( rc ) ) {
                    EXE = rc;
                    SeekEXE( StartByte );
                    WriteEXE( SavedByte );
                    TinySetFileStamp( EXE, EXETime, EXEDate );
                    TinyClose( EXE );
                    EXE = 0;
                    rc = 0;
                    Flags.BoundApp = TRUE;
                }
            }
        }
    }
    ret->err = rc;
    ret->task_id = psp;
    ret->flags = 0;
    ret->mod_handle = 0;
    return( sizeof( *ret ) );
}


unsigned ReqProg_kill()
{
    prog_kill_ret       *ret;

out( "in AccKillProg\r\n" );
    ret = GetOutPtr( 0 );
    InitRedirect();
    if( DOSTaskPSP() != NULL ) {
out( "enduser\r\n" );
        EndUser();
out( "done enduser\r\n" );
    }
out( "null87emu\r\n" );
    Null87Emu();
    NullOvlHdlr();
    ExceptNum = -1;
    ret->err = 0;
out( "done AccKillProg\r\n" );
    return( sizeof( *ret ) );
}


unsigned ReqSet_watch()
{
    watch               *curr;
    set_watch_req       *wp;
    set_watch_ret       *wr;
    int                 i,needed;

    wp = GetInPtr( 0 );
    wr = GetOutPtr( 0 );
    wr->err = 1;
    wr->multiplier = 0;
    if( WatchCount < MAX_WP ) {
        wr->err = 0;
        curr = WatchPoints + WatchCount;
        curr->addr.segment = wp->watch_addr.segment;
        curr->addr.offset = wp->watch_addr.offset;
        curr->value = *(dword far *)MK_FP( wp->watch_addr.segment, wp->watch_addr.offset );
        curr->linear = ( (unsigned long)wp->watch_addr.segment << 4 ) + wp->watch_addr.offset;
        curr->len = wp->size;
        curr->linear &= ~(curr->len-1);
        curr->dregs = ( wp->watch_addr.offset & (curr->len-1) ) ? 2 : 1;
        ++WatchCount;
        if( Flags.DRsOn ) {
            needed = 0;
            for( i = 0; i < WatchCount; ++i ) {
                needed += WatchPoints[ i ].dregs;
            }
            if( needed <= 4 ) wr->multiplier |= USING_DEBUG_REG;
        }
    }
    wr->multiplier |= 200;
    return( sizeof( *wr ) );
}

unsigned ReqClear_watch()
{
    WatchCount = 0;
    return( 0 );
}

unsigned ReqSet_break()
{
    char        *loc;
    set_break_req       *acc;
    set_break_ret       *ret;

    acc = GetInPtr( 0 );
    ret = GetOutPtr( 0 );

    loc = MK_FP( acc->break_addr.segment, acc->break_addr.offset );
    ret->old = *loc;
    *loc = 0xCC;
    if( *loc != 0xCC ) {
        BadBreak = acc->break_addr;
        GotABadBreak = TRUE;
    }
    return( sizeof( *ret ) );
}


unsigned ReqClear_break()
{
    clear_break_req     *bp;

    bp = GetInPtr( 0 );
    *(char far *)MK_FP( bp->break_addr.segment, bp->break_addr.offset ) = bp->old;
    GotABadBreak = FALSE;
    return( 0 );
}

static unsigned long SetDRn( int i, unsigned long linear, long type )
{
    switch( i ) {
    case 0:
        SetDR0( linear );
        break;
    case 1:
        SetDR1( linear );
        break;
    case 2:
        SetDR2( linear );
        break;
    case 3:
        SetDR3( linear );
        break;
    }
    return( ( type << DR7_RWLSHIFT(i) )
//          | ( DR7_GEMASK << DR7_GLSHIFT(i) ) | DR7_GE
          | ( DR7_LEMASK << DR7_GLSHIFT(i) ) | DR7_LE );
}


static int ClearDebugRegs( int trap )
{
    long        dr6;
    int         i;

    if( Flags.DRsOn ) {
        out( "tr=" ); out( hex( trap ) );
        out( " dr6=" ); out( hex( GetDR6() ) );
        out( "\r\n" );
        if( trap == TRAP_WATCH_POINT ) { /* could be a 386 break point */
            dr6 = GetDR6();
            if( ( ( dr6 & DR6_B0 ) && IsBreak[0] )
             || ( ( dr6 & DR6_B1 ) && IsBreak[1] )
             || ( ( dr6 & DR6_B2 ) && IsBreak[2] )
             || ( ( dr6 & DR6_B3 ) && IsBreak[3] ) ) {
                 trap = TRAP_BREAK_POINT;
             }
        }
        for( i = 0; i < 4; ++i ) {
            IsBreak[ i ] = FALSE;
        }
        SetDR6( 0 );
        SetDR7( 0 );
    }
    return( trap );
}


static bool SetDebugRegs()
{
    int                 needed;
    int                 i;
    int                 dr;
    unsigned long       dr7;
    unsigned long       linear;
    watch               *wp;
    bool                watch386;

    if( !Flags.DRsOn ) return( FALSE );
    needed = 0;
    for( i = WatchCount, wp = WatchPoints; i != 0; --i, ++wp ) {
        needed += wp->dregs;
    }
    dr  = 0;
    dr7 = 0;
    if( needed > 4 ) {
        watch386 = FALSE;
    } else {
        for( i = WatchCount, wp = WatchPoints; i != 0; --i, ++wp ) {
            dr7 |= SetDRn( dr, wp->linear, DRLen( wp->len ) | DR7_BWR );
            ++dr;
            if( wp->dregs == 2 ) {
                dr7 |= SetDRn( dr, wp->linear+4, DRLen( wp->len ) | DR7_BWR );
                ++dr;
            }
            watch386 = TRUE;
        }
    }
    if( GotABadBreak && dr < 4 ) {
        linear = ( (unsigned long)BadBreak.segment << 4 ) + BadBreak.offset;
        dr7 |= SetDRn( dr, linear, DR7_L1 | DR7_BINST );
        IsBreak[ dr ] = TRUE;
        ++dr;
    }
    SetDR7( dr7 );
    return( watch386 );
}

static unsigned MapReturn( int trap )
{
    switch( trap ) {
    case TRAP_TRACE_POINT:      return( COND_TRACE );
    case TRAP_BREAK_POINT:      return( COND_BREAK );
    case TRAP_WATCH_POINT:      return( COND_WATCH );
    case TRAP_USER:             return( COND_USER );
    case TRAP_TERMINATE:        return( COND_TERMINATE );
    case TRAP_MACH_EXCEPTION:
        ExceptNum = 0;
        return( COND_EXCEPTION );
    case TRAP_OVL_CHANGE:       return( COND_SECTIONS );
    }
    return( 0 );
}

static unsigned ProgRun( bool step )
{
    bool        watch386;
    prog_go_ret *ret;

    ret = GetOutPtr( 0 );
    if( Flags.DRsOn ) {
        SetSingle386();
    } else {
        SetSingleStep();
    }
    if( step ) {
        TaskRegs.EFL |= FLG_T;
    } else  {
        watch386 = SetDebugRegs();
        if( WatchCount != 0 && !watch386 ) {
            if( Flags.DRsOn ) {
                SetWatch386( WatchCount, WatchPoints );
            } else {
                SetWatchPnt( WatchCount, WatchPoints );
            }
            TaskRegs.EFL |= FLG_T;
        }
    }
    out( "in CS:EIP=" ); out( hex( TaskRegs.CS ) ); out(":" ); out( hex( TaskRegs.EIP ) );
    out( " SS:ESP=" ); out( hex( TaskRegs.SS ) ); out(":" ); out( hex( TaskRegs.ESP ) );
    out( "\r\n" );
    ret->conditions = MapReturn( ClearDebugRegs( RunProg( &TaskRegs, &TaskRegs ) ) );
    ret->conditions |= COND_CONFIG;
    out( "cond=" ); out( hex( ret->conditions ) );
    out( " CS:EIP=" ); out( hex( TaskRegs.CS ) ); out(":" ); out( hex( TaskRegs.EIP ) );
    out( " SS:ESP=" ); out( hex( TaskRegs.SS ) ); out(":" ); out( hex( TaskRegs.ESP ) );
    out( "\r\n" );
    ret->stack_pointer.segment = TaskRegs.SS;
    ret->stack_pointer.offset  = TaskRegs.ESP;
    ret->program_counter.segment = TaskRegs.CS;
    ret->program_counter.offset  = TaskRegs.EIP;
    TaskRegs.EFL &= ~FLG_T;
    WatchCount = 0;
    return( sizeof( *ret ) );
}

unsigned ReqProg_go()
{
    return( ProgRun( FALSE ) );
}

unsigned ReqProg_step()
{
    return( ProgRun( TRUE ) );
}

unsigned ReqGet_next_alias()
{
    get_next_alias_ret  *ret;

    ret = GetOutPtr( 0 );
    ret->seg = 0;
    ret->alias = 0;
    return( sizeof( *ret ) );
}

unsigned ReqGet_lib_name()
{
    char                *ch;
    get_lib_name_ret    *ret;

    ret = GetOutPtr( 0 );
    ret->handle = 0;
    ch = GetOutPtr( sizeof( *ret ) );
    *ch = '\0';
    return( sizeof( *ret ) + 1 );
}

unsigned ReqGet_err_text()
{
    static const char *const DosErrMsgs[] = {
#include "dosmsgs.h"
    };
    get_err_text_req    *acc;
    char           *err_txt;

    acc = GetInPtr( 0 );
    err_txt = GetOutPtr( 0 );
    if( (unsigned_16)acc->err > ( (sizeof(DosErrMsgs)/sizeof(char *)-1) ) ) {
        strcpy( err_txt, TRP_ERR_unknown_system_error );
    } else {
        strcpy( err_txt, DosErrMsgs[ (unsigned_16)acc->err ] );
    }
    return( strlen( err_txt ) + 1 );
}

unsigned ReqGet_message_text()
{
    get_message_text_ret        *ret;
    char                        *err_txt;

    ret = GetOutPtr( 0 );
    err_txt = GetOutPtr( sizeof(*ret) );
    if( ExceptNum == -1 ) {
        err_txt[0] = '\0';
    } else {
        ExceptionText( ExceptNum, err_txt );
        ExceptNum = -1;
    }
    ret->flags = MSG_NEWLINE | MSG_ERROR;
    return( sizeof( *ret ) + strlen( err_txt ) + 1 );
}

char *GetExeExtensions()
{
    return( DosExtList );
}

#pragma off(unreferenced);
trap_version TRAPENTRY TrapInit( char *parm, char *err, bool remote )
#pragma on(unreferenced);
{
    trap_version ver;

out( "in TrapInit\r\n" );
out( "    checking environment:\r\n" );
    if( parm[0] == 'D' || parm[0] == 'd' ) {
        Flags.DRsOn = FALSE;
        ++parm;
    } else if( out( "    CPU type\r\n" ) || X86CPUType() < 3 ) {
        Flags.DRsOn = FALSE;
    } else if( out( "    WinEnh\r\n" ) || ( EnhancedWinCheck() & 0x7f ) ) {
        /* Enhanced Windows 3.0 VM kernel messes up handling of debug regs */
        Flags.DRsOn = FALSE;
    } else if( out( "    DOSEMU\r\n" ) || DOSEMUCheck() ) {
        /* no fiddling with debug regs in Linux DOSEMU either */
        Flags.DRsOn = FALSE;
    } else {
        Flags.DRsOn = TRUE;
    }
    if( parm[0] == 'O' || parm[0] == 'o' ) {
        Flags.NoOvlMgr = TRUE;
    }
out( "    done checking environment\r\n" );
    err[0] = '\0'; /* all ok */
    /* NPXType initializes '87, so check for it before a program
       starts using the thing */
    RealNPXType = NPXType();
    InitVectors();
    if( DOS_major >= 20 ) {
        /* In an OS/2 2.0 DOS box. It doesn't let us fiddle the debug
        registers. The check is done here because InitVectors is the
        routine that sets up DOS_major */
        Flags.DRsOn = FALSE;
    }
    Null87Emu();
    NullOvlHdlr();
    TrapTypeInit();
    InitRedirect();
    ExceptNum = -1;
    WatchCount = 0;
    ver.major = TRAP_MAJOR_VERSION;
    ver.minor = TRAP_MINOR_VERSION;
    ver.remote = FALSE;
out( "done TrapInit\r\n" );
    return( ver );
}

void TRAPENTRY TrapFini()
{
out( "in TrapFini\r\n" );
    FiniVectors();
out( "done TrapFini\r\n" );
}
