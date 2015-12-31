
cc_matrix	= $(cc_iquads)
cpp_matrix	= $(cpp_iquads)
fc_matrix	= $(fc_iquads)
ar_matrix	= $(ar_iquads)
install_matrix	= $(install_iquads)

cflags_matrix	= $(cflags_iquads)
cppflags_matrix	= $(cppflags_iquads)
fflags_matrix	= $(fflags_iquads)

copt_matrix	= $(copt_iquads)
cppopt_matrix	= $(cppopt_iquads)
fopt_matrix	= $(fopt_iquads)

cppheads_matrix	= $(iquads_src)/matrix/array_matrix_template.hpp\
		  $(iquads_src)/matrix/array_matrix_instant.hpp\
		  $(iquads_src)/matrix/vector_matrix_template.hpp\
		  $(iquads_src)/matrix/vector_matrix_instant.hpp\
		  $(iquads_src)/matrix/matrix_typedef.hpp\
		  $(iquads_src)/matrix/matrix_function.hpp

cppsrcs_matrix	= $(iquads_src)/matrix/matrix_function.cpp
		  
cppobjs_matrix	= $(cppsrcs_matrix:.cpp=.o)\

target_matrix	= $(iquads_src)/matrix/libiquads_matrix.a

target_shared_matrix = $(iquads_src)/matrix/libiquads_matrix.so

all_matrix: release_matrix

debug_matrix: 	cppopt_matrix += -g\
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
debug_matrix:	copt_matrix += -g
debug_matrix:	fopt_matrix += -g
debug_matrix: target_matrix target_shared_matrix

ass_matrix_o:
	$(cpp_matrix)  -c -O3 $(cppopt_matrix) -g -Wa,-ahl $(cppflags_matrix) $(iquads_src)/matrix/matrix_function.cpp > $(iquads_src)/matrix/matrix_function.s

release_matrix: cppopt_matrix += 
release_matrix: copt_matrix += 
release_matrix: fopt_matrix += 
release_matrix: target_matrix target_shared_matrix

standalone_matrix: cppopt_matrix += -static
#standalone, current deprecated we don't have static libary of boost ...
standalone_matrix: target_matrix target_shared_matrix

clean_matrix:
	rm $(cppobjs_matrix); rm $(target_matrix) $(target_shared_matrix)

target_matrix:	$(cppobjs_matrix)
	$(ar_matrix) $(target_matrix) $(cppobjs_matrix); $(install_matrix) $(target_matrix) $(iquads_lib)

target_shared_matrix: $(cppobjs_matrix)
	g++ -shared -o $(target_shared_matrix) $(cppobjs_matrix); $(install_matrix) $(target_shared_matrix) $(iquads_lib)

$(iquads_src)/matrix/matrix_function.o: $(iquads_src)/matrix/matrix_function.cpp
	$(cpp_matrix) -o $(iquads_src)/matrix/matrix_function.o -c $(cppopt_matrix) $(cppflags_matrix) $(iquads_src)/matrix/matrix_function.cpp

