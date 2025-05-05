# Makefile for GPSNetwork demo

# compiler settings
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2

# executable name
TARGET    := navigator

# source files
SRCS      := navigator.cpp
OBJS      := $(SRCS:.cpp=.o)

# default cities (override on the command‐line)
SRC ?= Aldoria
DST ?= Frostfall

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# run with `make run SRC=CityA DST=CityB`
run: $(TARGET)
	./$(TARGET) $(SRC) $(DST)

clean:
	rm -f $(TARGET) $(OBJS)
