CXX	= mpic++
COPT	= -O2
BOOST	= /home/wh288/Development/boost_1_53_0/
INCLUDES	= -I$(BOOST) -I./
BOOSTLIB	= $(BOOST)/stage/lib -lboost_mpi
HEADS	= bomd_main.h bomd_data.h get_value.h timeframe_class.h
CSRCS	= bomd_main.cpp bomd_data.cpp get_value.cpp run_bomd.cpp timeframe_class.cpp integration.cpp
COBJS	= $(CSRCS:.cpp=.o)

LIBS	= $(BOOSTLIB)

PGM	= bomd

$(PGM):	$(CSRCS) $(HEADS)
	$(CXX) $(COPT) -o $(PGM) $(INCLUDE) $(COBJS) -L$(LIBS)

bomd_main.o:	bomd_main.cpp
	$(CXX) $(COPT) -c $(INCLUDES) bomd_main.cpp

bomd_data.o:	bomd_data.cpp bomd_data.h
	$(CXX) $(COPT) -c $(INCLUDES) bomd_data.cpp

get_value.o:	get_value.cpp get_value.h
	$(CXX) $(COPT) -c $(INCLUDES) get_value.cpp

run_bomd.o:	run_bomd.cpp bomd_data.h bomd_data.cpp
	$(CXX) $(COPT) -c $(INCLUDES) run_bomd.cpp

timeframe_class.o:	timeframe_class.cpp time_frame_class.h
	$(CXX) $(COPT) -c $(INCLUDES) timeframe_class.cpp

integration.o:	integration.cpp
	$(CXX) $(COPT) -c $(INCLUDES) integration.cpp
