iquads_root	= $(DEV_ROOT)/iquads/
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/

cc_matrix	= gcc
cpp_matrix	= g++
ar_matrix	= ar -r 

cflags_matrix	= -I$(iquads_src) -I/usr/include
cppflags_matrix	= -std=c++11 -I$(iquads_src) -I/usr/include
cppopt_matrix	= 

cppheads_matrix	= $(iquads_src)/matrix/array_matrix_template.hpp\
		  $(iquads_src)/matrix/array_matrix_instant.hpp\
		  $(iquads_src)/matrix/vector_matrix_template.hpp\
		  $(iquads_src)/matrix/vector_matrix_instant.hpp\
		  $(iquads_src)/matrix/matrix_typedef.hpp\
		  $(iquads_src)/matrix/matrix_function.hpp

cppsrcs_matrix	= $(iquads_src)/matrix/matrix_function.cpp
		  
cppobjs_matrix	= $(cppsrcs_matrix:.cpp=.o)\

target_matrix	= $(iquads_src)/matrix/libiquads_matrix.a

all_matrix: release_matrix

debug_matrix: 	cppopt_matrix += -g -O0\
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
debug_matrix: target_matrix

ass:
	$(cpp_matrix)  -c -O3 $(cppopt_matrix) -g -Wa,-ahl $(cppflags_matrix) $(iquads_src)/matrix/matrix_function.cpp > $(iquads_src)/matrix/matrix_function.s

release_matrix: cppopt_matrix +=  -O3  -fopenmp
release_matrix: target_matrix

standalone_matrix: cppopt_matrix += -static
#standalone: we don't have static libary of boost ...
standalone_matrix: target_matrix

clean_matrix:
	rm $(iquads_src)/matrix/*.o; rm $(target_matrix)

target_matrix:	$(cppobjs_matrix)
	$(ar_matrix) $(target_matrix) $(cppobjs_matrix)

$(iquads_src)/matrix/matrix_function.o: $(iquads_src)/matrix/matrix_function.cpp
	$(cpp_matrix) -o $(iquads_src)/matrix/matrix_function.o -c $(cppopt_matrix) $(cppflags_matrix) $(iquads_src)/matrix/matrix_function.cpp

