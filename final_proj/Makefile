# Makefile for GPSNetwork demo

# compiler settings
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2

# executable name
TARGET    := prog

# source files
SRCS      := dijkstraVectorImp.cpp
OBJS      := $(SRCS:.cpp=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
