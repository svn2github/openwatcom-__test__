#pmake: build flat cpu_386 os_nt dynamic profile
#
# iostmt3r.lib -- register based multi-thread 32-bit IOSTREAM library
#
processor  = 386
system     = winnt
model      = mf
convention = register
linkage    = dynamic
mthreaded  = 1
fs_registration = yes
profile    = 1
lib_page_size = -p=32
define_library_include = $(cpplib_dir)/iostream/iostream.mif
!include $(cpplib_dir)/mklib.mif
