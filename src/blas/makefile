iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

cc_blas		= gcc
cpp_blas	= g++
fc_blas		= gfortran 
ar_blas		= ar -r 

cflags_blas	= -I$(iquads_src) -I/usr/include
cppflags_blas	= -std=c++11 -I$(iquads_src) -I/usr/include
cppopt_blas	= 
fopt_blas	=

cppheads_blas	= $(iquads_src)/blas/blas_interface.h

cppsrcs_blas	= $(iquads_src)/blas/blas_interface.cpp

fsrcs_blas	= $(iquads_src)/blas/ax_b.f\
		  $(iquads_src)/blas/mat_x_mat.f\
		  $(iquads_src)/blas/symdiag.f
		  
cppobjs_blas	= $(cppsrcs_blas:.cpp=.o)
fobjs_blas	= $(fsrcs_blas:.f=.o)

target_blas	= $(iquads_src)/blas/libiquads_blas_interface.a

#all_blas: release_blas

debug_blas:   cppopt_blas += -g -O0\
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
debug_blas: fc_blas += -g -O0
debug_blas: target_blas

clean_blas:
	rm $(iquads_src)/blas/*.o; rm $(target_blas)

release_blas: cppopt_blas +=  -O3 
release_blas: fopt_blas   +=  -O3
release_blas: target_blas

standalone_blas: cppopt_blas += -static 
#standalone: we don't have static libary of boost ...
standalone_blas: target

target_blas:	$(cppobjs_blas) $(fobjs_blas)
	$(ar_blas) $(target_blas) $(cppobjs_blas) $(fobjs_blas)

$(iquads_src)/blas/blas_interface.o: $(iquads_src)/blas/blas_interface.cpp
	$(cpp_blas) -o $(iquads_src)/blas/blas_interface.o -c $(cppopt_blas) $(cppflags_blas) $(iquads_src)/blas/blas_interface.cpp

$(iquads_src)/blas/ax_b.o: $(iquads_src)/blas/ax_b.f
	$(fc_blas) -o $(iquads_src)/blas/ax_b.o -c $(fopt_blas) $(iquads_src)/blas/ax_b.f

$(iquads_src)/blas/mat_x_mat.o: $(iquads_src)/blas/mat_x_mat.f
	$(fc_blas) -o $(iquads_src)/blas/mat_x_mat.o -c $(fopt_blas) $(iquads_src)/blas/mat_x_mat.f

$(iquads_src)/blas/symdiag.o: $(iquads_src)/blas/symdiag.f
	$(fc_blas) -o $(iquads_src)/blas/symdiag.o -c $(fopt_blas) $(iquads_src)/blas/symdiag.f
