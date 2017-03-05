CC = gcc
CXX = g++
CXXFLAGS:= -std=c++11 -Wall -c -I./include/
LIBS =-lstdc++ -lm

SRC := $(wildcard src/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRC))
DS := $(patsubst %.cpp,%.d,$(SRC))
EXOBJS := $(patsubst %.cpp,%.o,$(SRC))
RM=rm -f

all : $(EXOBJS)
	$(CXX) -o KDTree $(EXOBJS) $(LIBS)
	$(RM) $(OBJS) $(EXOBJS) $(DS)

clean :
	clear
	$(RM) $(OBJS) $(EXOBJS) $(DS)
	$(RM) KDTree
	
default : all
