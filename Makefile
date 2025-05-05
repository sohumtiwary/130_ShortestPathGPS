CXX      := g++
CXXFLAGS := -std=c++17 \
            -I"D:/Google Drive/sjsu-storage/SEM 6/CMPE 130/final_proj/SFML-3.0.0/include"

LDFLAGS  := -L"D:/Google Drive/sjsu-storage/SEM 6/CMPE 130/final_proj/SFML-3.0.0/lib" \
            -lsfml-graphics \
            -lsfml-window \
            -lsfml-system

SRC      := visualize_route_with_cities.cpp
TARGET   := visualize_route_with_cities.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	del $(TARGET)  # or rm -f $(TARGET)
