# MAD Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>\master.ctl ]
[ INCLUDE <LANG_BLD>\wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 cprel2 ]
#========================
    <CPCMD> <devdir>\bin\bin\mad???.mad <relroot>\rel2\binw\
    <CPCMD> <devdir>\bin\bin\mad???.dll <relroot>\rel2\binw\
    <CPCMD> <devdir>\bin\binp\dll\mad???.dll <relroot>\rel2\binp\dll\
    <CPCMD> <devdir>\bin\binp\dll\mad???.d32 <relroot>\rel2\binp\
    <CPCMD> <devdir>\bin\binnt\mad???.dll <relroot>\rel2\binnt\
#    <CPCMD> <devdir>\bin\axpnt\mad???.dll <relroot>\rel2\axpnt\
    <CPCMD> <devdir>\bin\qnx\*.mad <relroot>\rel2\qnx\watcom\wd\

[ BLOCK <1> clean ]
#==================
     pmake -d all <2> <3> <4> <5> <6> <7> <8> <9> -h clean
