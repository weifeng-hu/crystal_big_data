ROOT	= /home/wh288/Development/iqs/
CXX	= mpic++
COPT	= -O2
INCLUDE = -I$(ROOT)
HEADS	= tensor_class.h
CSRCS	= tensor_class.cpp 
COBJS	= $(CSRCS:.cpp=.o)
AR	= libtensor.a

$(AR):	$(COBJS) $(HEADS)
	ar -r $(AR) $(COBJS)

#tensor_class.o:	tensor_class.h tensor_class.cpp
#	$(CXX) -c $(COPT) $(INCLUDE) tensor_class.cpp

clean:
	rm *.o; rm libtensor.a
