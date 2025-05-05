CXX      := g++
CXXFLAGS := -std=c++17 \
            -I"SFML-3.0.0/include"
LDFLAGS  := -L"SFML-3.0.0/lib" \
            -lsfml-graphics \
            -lsfml-window \
            -lsfml-system

SRC      := visualize_route_with_cities.cpp
TARGET   := prog

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	del $(TARGET) || rm -f $(TARGET)
