
cc_blas		= $(cc_iquads)
cpp_blas	= $(cpp_iquads)
fc_blas		= $(fc_iquads)
ar_blas		= $(ar_iquads)
install_blas	= $(install_iquads)

cflags_blas	= $(cflags_iquads)
cppflags_blas	= $(cppflags_iquads)
fflags_blas	= $(fflags_iquads)

copt_blas	= $(copt_iquads)
cppopt_blas	= $(cppopt_iquads)
fopt_blas	= $(fopt_iquads)

cppheads_blas	= $(iquads_src)/blas/blas_interface.h

cppsrcs_blas	= $(iquads_src)/blas/blas_interface.cpp

fsrcs_blas	= $(iquads_src)/blas/ax_b.f\
		  $(iquads_src)/blas/mat_x_mat.f\
		  $(iquads_src)/blas/symdiag.f
		  
cppobjs_blas	= $(cppsrcs_blas:.cpp=.o)
fobjs_blas	= $(fsrcs_blas:.f=.o)

target_blas	= $(iquads_src)/blas/libiquads_blas_interface.a
target_shared_blas	= $(iquads_src)/blas/libiquads_blas_interface.so

all_blas: release_blas

debug_blas:   cppopt_blas += -g\
	  -Wextra -Wcast-align \
	  -Wdisabled-optimization \
	  -Wfloat-equal -Wformat=2 \
	  -Wformat-nonliteral -Wformat-security  \
	  -Wformat-y2k \
	  -Wimport  -Winit-self  -Winline \
	  -Winvalid-pch   \
	  -Wmissing-field-initializers -Wmissing-format-attribute   \
	  -Wmissing-include-dirs -Wmissing-noreturn \
	  -Wpacked  -Wpointer-arith \
	  -Wredundant-decls \
	  -Wstack-protector \
	  -Wstrict-aliasing=2 -Wswitch-default \
	  -Wswitch-enum \
	  -Wunreachable-code \
	  -Wvariadic-macros \
	  -Wwrite-strings
debug_blas: fopt_blas += -g
debug_blas: copt_blas += -g
debug_blas: target_blas target_shared_blas

clean_blas:
	rm $(iquads_src)/blas/*.o; rm $(target_blas) $(target_shared_blas)

release_blas: ccopt_blas +=
release_blas: cppopt_blas +=
release_blas: fopt_blas   +=
release_blas: target_blas target_shared_blas

standalone_blas: ccopt_blas += -static 
standalone_blas: cppopt_blas += -static 
standalone_blas: fopt_blas += -static 
#standalone, currently deprecated, we don't have static libary of boost ...
standalone_blas: 

target_blas:	$(cppobjs_blas) $(fobjs_blas)
	$(ar_blas) $(target_blas) $(cppobjs_blas) $(fobjs_blas); $(install_blas) $(target_blas) $(iquads_lib)

target_shared_blas:	$(cppobjs_blas) $(fobjs_blas)
	$(cc_blas) -shared -o $(target_shared_blas) $(cppobjs_blas) $(fobjs_blas); $(install_blas) $(target_shared_blas) $(iquads_lib)

$(iquads_src)/blas/blas_interface.o: $(iquads_src)/blas/blas_interface.cpp
	$(cpp_blas) -o $(iquads_src)/blas/blas_interface.o -c $(cppopt_blas) $(cppflags_blas) $(iquads_src)/blas/blas_interface.cpp

$(iquads_src)/blas/ax_b.o: $(iquads_src)/blas/ax_b.f
	$(fc_blas) -o $(iquads_src)/blas/ax_b.o -c $(fflags_blas) $(fopt_blas) $(iquads_src)/blas/ax_b.f

$(iquads_src)/blas/mat_x_mat.o: $(iquads_src)/blas/mat_x_mat.f
	$(fc_blas) -o $(iquads_src)/blas/mat_x_mat.o -c $(fflags_blas) $(fopt_blas) $(iquads_src)/blas/mat_x_mat.f

$(iquads_src)/blas/symdiag.o: $(iquads_src)/blas/symdiag.f
	$(fc_blas) -o $(iquads_src)/blas/symdiag.o -c $(fflags_blas) $(fopt_blas) $(iquads_src)/blas/symdiag.f
