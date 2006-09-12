/*
    New Executable (NE) format.
*/

#ifndef __NEWEXE__
#define __NEWEXE__

#ifdef __cplusplus
extern "C" {
#endif

#define EMAGIC      0x5A4D
#define ENEWEXE     sizeof(struct exe_hdr)

#define ENEWHDR     0x003C
#define ERESWDS     0x0010
#define ERES1WDS    0x0004
#define ERES2WDS    0x000A
#define ECP         0x0004
#define ECBLP       0x0002
#define EMINALLOC   0x000A

#define E_MAGIC(x)      (x).e_magic
#define E_CBLP(x)       (x).e_cblp
#define E_CP(x)         (x).e_cp
#define E_CRLC(x)       (x).e_crlc
#define E_CPARHDR(x)    (x).e_cparhdr
#define E_MINALLOC(x)   (x).e_minalloc
#define E_MAXALLOC(x)   (x).e_maxalloc
#define E_SS(x)         (x).e_ss
#define E_SP(x)         (x).e_sp
#define E_CSUM(x)       (x).e_csum
#define E_IP(x)         (x).e_ip
#define E_CS(x)         (x).e_cs
#define E_LFARLC(x)     (x).e_lfarlc
#define E_OVNO(x)       (x).e_ovno
#define E_RES(x)        (x).e_res
#define E_OEMID(x)      (x).e_oemid
#define E_OEMINFO(x)    (x).e_oeminfo
#define E_RES2(x)       (x).e_res2
#define E_LFANEW(x)     (x).e_lfanew

#define NEMAGIC         0x454E
#define NERESBYTES      8
#define NECRC           8

#define ne_pWinFileStruc (ne_magic + 0x0a)
#define ne_cbModName     0
#define ne_pWinModName   8

#define NE_MAGIC(x)         (x).ne_magic
#define NE_VER(x)           (x).ne_ver
#define NE_REV(x)           (x).ne_rev
#define NE_ENTTAB(x)        (x).ne_enttab
#define NE_CBENTTAB(x)      (x).ne_cbenttab
#define NE_CRC(x)           (x).ne_crc
#define NE_FLAGS(x)         (x).ne_flags
#define NE_AUTODATA(x)      (x).ne_autodata
#define NE_HEAP(x)          (x).ne_heap
#define NE_STACK(x)         (x).ne_stack
#define NE_CSIP(x)          (x).ne_csip
#define NE_SSSP(x)          (x).ne_sssp
#define NE_CSEG(x)          (x).ne_cseg
#define NE_CMOD(x)          (x).ne_cmod
#define NE_CBNRESTAB(x)     (x).ne_cbnrestab
#define NE_SEGTAB(x)        (x).ne_segtab
#define NE_RSRCTAB(x)       (x).ne_rsrctab
#define NE_RESTAB(x)        (x).ne_restab
#define NE_MODTAB(x)        (x).ne_modtab
#define NE_IMPTAB(x)        (x).ne_imptab
#define NE_NRESTAB(x)       (x).ne_nrestab
#define NE_CMOVENT(x)       (x).ne_cmovent
#define NE_ALIGN(x)         (x).ne_align
#define NE_CRES(x)          (x).ne_cres
#define NE_RES(x)           (x).ne_res
#define NE_EXETYP(x)        (x).ne_exetyp
#define NE_FLAGSOTHERS(x)   (x).ne_flagsothers

#define NE_USAGE(x)     (WORD)*((WORD *)(x)+1)
#define NE_PNEXTEXE(x)  (WORD)(x).ne_cbenttab
#define NE_ONEWEXE(x)   (WORD)(x).ne_crc
#define NE_PFILEINFO(x) (WORD)((DWORD)(x).ne_crc >> 16)

#define NE_UNKNOWN      0x0
#define NE_OS2          0x1
#define NE_WINDOWS      0x2
#define NE_DOS4         0x3
#define NE_DEV386       0x4

#define NENOTP          0x8000
#define NENOTMPSAFE     0x4000
#define NEIERR          0x2000
#define NEBOUND         0x0800
#define NEAPPTYP        0x0700
#define NENOTWINCOMPAT  0x0100
#define NEWINCOMPAT     0x0200
#define NEWINAPI        0x0300
#define NEFLTP          0x0080
#define NEI386          0x0040
#define NEI286          0x0020
#define NEI086          0x0010
#define NEPROT          0x0008
#define NEPPLI          0x0004
#define NEINST          0x0002
#define NESOLO          0x0001

#define NELONGNAMES     0x01
#define NEWINISPROT     0x02
#define NEWINGETPROPFON 0x04
#define NEWLOAPPL       0x80

#define NS_SECTOR(x)    (x).ns_sector
#define NS_CBSEG(x)     (x).ns_cbseg
#define NS_FLAGS(x)     (x).ns_flags
#define NS_MINALLOC(x)  (x).ns_minalloc

#define NSTYPE          0x0007

#if (EXE386 == 0)
#define NSCODE          0x0000
#define NSDATA          0x0001
#define NSITER          0x0008
#define NSMOVE          0x0010
#define NSSHARED        0x0020
#define NSPRELOAD       0x0040
#define NSEXRD          0x0080

#define NSRELOC         0x0100
#define NSCONFORM       0x0200
#define NSEXPDOWN       0x0200
#define NSDPL           0x0C00
#define SHIFTDPL        10
#define NSDISCARD       0x1000
#define NS32BIT         0x2000
#define NSHUGE          0x4000

#define NSGDT           0x8000
#define NSPURE          NSSHARED
#define NSALIGN         9
#define NSLOADED        0x0004
#endif

struct exe_hdr {
    unsigned short  e_magic;
    unsigned short  e_cblp;
    unsigned short  e_cp;
    unsigned short  e_crlc;
    unsigned short  e_cparhdr;
    unsigned short  e_minalloc;
    unsigned short  e_maxalloc;
    unsigned short  e_ss;
    unsigned short  e_sp;
    unsigned short  e_csum;
    unsigned short  e_ip;
    unsigned short  e_cs;
    unsigned short  e_lfarlc;
    unsigned short  e_ovno;
    unsigned short  e_res[ERES1WDS];
    unsigned short  e_oemid;
    unsigned short  e_oeminfo;
    unsigned short  e_res2[ERES2WDS];
    long            e_lfanew;
};

struct new_exe {
    unsigned short  ne_magic;
    unsigned char   ne_ver;
    unsigned char   ne_rev;
    unsigned short  ne_enttab;
    unsigned short  ne_cbenttab;
    long            ne_crc;
    unsigned short  ne_flags;
    unsigned short  ne_autodata;
    unsigned short  ne_heap;
    unsigned short  ne_stack;
    long            ne_csip;
    long            ne_sssp;
    unsigned short  ne_cseg;
    unsigned short  ne_cmod;
    unsigned short  ne_cbnrestab;
    unsigned short  ne_segtab;
    unsigned short  ne_rsrctab;
    unsigned short  ne_restab;
    unsigned short  ne_modtab;
    unsigned short  ne_imptab;
    long            ne_nrestab;
    unsigned short  ne_cmovent;
    unsigned short  ne_align;
    unsigned short  ne_cres;
    unsigned char   ne_exetyp;
    unsigned char   ne_flagsothers;
    char            ne_res[NERESBYTES];
};

struct new_seg {
    unsigned short  ns_sector;
    unsigned short  ns_cbseg;
    unsigned short  ns_flags;
    unsigned short  ns_minalloc;
};

struct new_seg1 {
    unsigned short  ns1_sector;
    unsigned short  ns1_cbseg;
    unsigned short  ns1_flags;
    unsigned short  ns1_minalloc;
    unsigned short  ns1_handle;
};

#pragma pack(push,1)

struct new_segdata {
    union {
        struct {
            unsigned short      ns_niter;
            unsigned short      ns_nbytes;
            char                ns_iterdata;
        } ns_iter;
        struct {
            char                ns_data;
        } ns_noniter;
    } ns_union;
};

struct new_rlcinfo {
    unsigned short  nr_nreloc;
};

struct new_rlc {
    char            nr_stype;
    char            nr_flags;
    unsigned short  nr_soff;
    union {
        struct {
            char            nr_segno;
            char            nr_res;
            unsigned short  nr_entry;
          } nr_intref;
        struct {
            unsigned short  nr_mod;
            unsigned short  nr_proc;
          } nr_import;
        struct {
            unsigned short  nr_ostype;
            unsigned short  nr_osres;
          } nr_osfix;
      } nr_union;
};

#define NR_STYPE(x)     (x).nr_stype
#define NR_FLAGS(x)     (x).nr_flags
#define NR_SOFF(x)      (x).nr_soff
#define NR_SEGNO(x)     (x).nr_union.nr_intref.nr_segno
#define NR_RES(x)       (x).nr_union.nr_intref.nr_res
#define NR_ENTRY(x)     (x).nr_union.nr_intref.nr_entry
#define NR_MOD(x)       (x).nr_union.nr_import.nr_mod
#define NR_PROC(x)      (x).nr_union.nr_import.nr_proc
#define NR_OSTYPE(x)    (x).nr_union.nr_osfix.nr_ostype
#define NR_OSRES(x)     (x).nr_union.nr_osfix.nr_osres

#define NRSTYP      0x0f
#define NRSBYT      0x00
#define NRSSEG      0x02
#define NRSPTR      0x03
#define NRSOFF      0x05
#define NRPTR48     0x06
#define NROFF32     0x07
#define NRSOFF32    0x08

#define NRADD       0x04
#define NRRTYP      0x03
#define NRRINT      0x00
#define NRRORD      0x01
#define NRRNAM      0x02
#define NRROSF      0x03
#define NRICHAIN    0x08

#if (EXE386 == 0)

#define RS_LEN(x)       (x).rs_len
#define RS_STRING(x)    (x).rs_string
#define RS_ALIGN(x)     (x).rs_align

#define RT_ID(x)        (x).rt_id
#define RT_NRES(x)      (x).rt_nres
#define RT_PROC(x)      (x).rt_proc

#define RN_OFFSET(x)    (x).rn_offset
#define RN_LENGTH(x)    (x).rn_length
#define RN_FLAGS(x)     (x).rn_flags
#define RN_ID(x)        (x).rn_id
#define RN_HANDLE(x)    (x).rn_handle
#define RN_USAGE(x)     (x).rn_usage

#define RSORDID     0x8000

#define RNMOVE      0x0010
#define RNPURE      0x0020
#define RNPRELOAD   0x0040
#define RNDISCARD   0xF000

struct rsrc_string {
    char    rs_len;
    char    rs_string[1];
};

struct rsrc_typeinfo {
    unsigned short  rt_id;
    unsigned short  rt_nres;
    long            rt_proc;
};

struct rsrc_nameinfo {
    unsigned short  rn_offset;
    unsigned short  rn_length;
    unsigned short  rn_flags;
    unsigned short  rn_id;
    unsigned short  rn_handle;
    unsigned short  rn_usage;
};

struct new_rsrc {
    unsigned short          rs_align;
    struct rsrc_typeinfo    rs_typeinfo;
};

#endif

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

#endif
