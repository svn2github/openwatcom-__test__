plustest_name = cool
!include ../../environ.mif

objs = &
   associat.obj base_bnn.obj base_bnt.obj base_has.obj base_lis.obj &
   base_m_v.obj base_mat.obj base_que.obj base_sta.obj base_vec.obj &
   bignum.obj binary_n.obj binary_t.obj bit_set.obj bit_tabl.obj &
   calendar.obj char.obj complex.obj country.obj d_node.obj date_tim.obj &
   gen_stri.obj hash_tab.obj list.obj m_vector.obj matrix.obj n_node.obj &
   n_tree.obj nt_state.obj pair.obj property.obj quaterni.obj queue.obj &
   random.obj rational.obj regexp.obj set.obj stack.obj string.obj &
   test.obj timer.obj timezone.obj value.obj vector.obj

!ifdef test1
test_cflags = -ot-op-d1
!else ifdef test2
test_cflags = -ot-op-d1-xds
!else ifdef test3
test_cflags = -op-d2-xds
!else
test_cflags = -op-d2
!endif

test_cflags += -zq -I../.. -w0

test_cflags_i86 = -ml -zm -s
   
.c: ..
.c.obj:
    $(wpp_$(arch)) $[@ $(test_cflags) $(test_cflags_$(arch))
    
test : .symbolic ../cool.lib
    %make global
    %append $(log_file) PASS $(%__CWD__)
    
..\cool.lib : $(objs) cool.lbc
    $(librarian_$(arch)) -n -q -b -p=512 $^@ @cool.lbc
    
cool.lbc : makefile
    %create $^@
    @for %i in ($(objs)) do @%append $^@ +%i
    
global : .symbolic
    %make common_clean
