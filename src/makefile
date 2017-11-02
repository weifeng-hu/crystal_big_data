iquads_root	= $(IQUADS_ROOT)
iquads_src	= $(iquads_root)/src/
iquads_bin	= $(iquads_root)/bin/
iquads_lib	= $(iquads_root)/lib/
boost_lib	= $(BOOST_ROOT)/stage/lib
boost_include	= $(BOOST_ROOT)/

cc_iquads	= gcc
cpp_iquads	= g++
fc_iquads	= gfortran
ar_iquads	= ar -r
install_iquads	= install

# use -fPIC since shared libraries will be created
cflags_iquads	= -I$(iquads_src) -I$(boost_include) -I/usr/include -I/usr/local/include -fPIC -fopenmp
cppflags_iquads	= -I$(iquads_src) -I$(boost_include) -I/usr/include -I/usr/local/include -fPIC -fopenmp -std=c++11
fflags_iquads	= -fPIC

# iquads relies on openmp.
# Uptill now, machine code natively compiled on armv7 crashes and relates to defective openmp libraries, unless no optimization is used.
# Check the machine, we don't use any optimization on arm machines, but x86 and x86_64 are fine

copt_iquads	=
cppopt_iquads	=
fopt_iquads	=

uname_m_iquads	= $(shell uname -m)
machine_iquads	= $(uname_m_iquads)

ifeq ($(findstring arm, $(machine_iquads) ),arm)
$(info arm detected ... set opt as -O0)
copt_iquads	+= -O0
cppopt_iquads	+= -O0
fopt_iquads	+= -O0
# this covers x86 and x86_64
endif

ifeq ($(findstring x86, $(machine_iquads) ),x86)
$(info x86/x86_64 detected ... set opt as -O3)
copt_iquads	+= -O3
cppopt_iquads	+= -O0
fopt_iquads	+= -O0
endif

# Also specifically add machine mode for armv7, ONLY applies to GNU compilers!!!
ifeq ($(findstring armv7, $(machine_iquads) ),armv7)
$(info armv7 detected ... append opt as -mcpu=cortex-a15)
copt_iquads	+= -mcpu=cortex-a15 
cppopt_iquads	+= -mcpu=cortex-a15 
fopt_iquads	+= -mcpu=cortex-a15
endif
 
ifeq ($(findstring x86, $(machine_iquads) ),x86)
$(info x86/x86_64 detected ... opt unchanged)
copt_iquads	+= 
cppopt_iquads	+= 
fopt_iquads	+= 
endif

lib_iquads	= -L$(boost_lib) -lboost_filesystem -lboost_date_time -lboost_system

# blas and lapack libraries
# arm doesn't have mkl, so other blas and lapack are used
ifeq ($(findstring arm, $(machine_iquads) ),arm)
$(info arm detected, append open-source math libs)
lib_iquads	+= -llapack -lblas
endif

ifeq ($(findstring x86, $(machine_iquads) ),x86)
$(info x86/x86_64 detected ... append intel math libs)
lib_iquads	+= -lmkl_intel_lp64 -lmkl_sequential -lmkl_core
endif

lib_iquads	+= -lrt -lpthread -lgfortran -lm -lc

#include sub module makefiles

default: release

include blas/makefile
include matrix/makefile
include interface_to_third_party/makefile
include electron_correlation/makefile
include manybody_expansion/makefile

debug:
	mkdir -p $(iquads_lib);\
	make debug_blas;\
	make debug_matrix;\
	make debug_third_party;\
	make debug_electron_correlation;\
	make debug_manybody_expansion

release: 
	mkdir -p $(iquads_lib);\
	make release_blas;\
	make release_matrix;\
	make release_third_party;\
	make release_electron_correlation;\
	make release_manybody_expansion

clean:
	make clean_blas;\
	make clean_matrix;\
	make clean_third_party;\
	make clean_electron_correlation;\
	make clean_manybody_expansion;\
	rm -rf $(iquads_lib)/*

