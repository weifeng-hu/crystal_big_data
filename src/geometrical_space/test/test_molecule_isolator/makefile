shell	= /bin/sh
cpp	= g++
cppflags= -g -std=c++11
cppopt	= -O0
cppinc	= -I${IQUADS_SRC}
cppsrcs	= main.cpp
cppobjs	= $(cppsrcs:.cpp=.o)
lib	= 
target	= test

${target}:	${cppobjs}
	${cpp} -o ${target} ${cppobjs} ${lib}

main.o:	main.cpp
	${cpp} -c ${cppflags} ${cppopt} ${cppinc} main.cpp

clean:
	rm main.o ${target}
