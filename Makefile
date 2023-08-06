CXX=g++
CXXFLAGS=-std=c++20 -pedantic -Wall
EXE=ARKRaider

all: $(EXE)

$(EXE): ARKRaider.cpp Ark.cpp Util.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ -static

clean:
	rm -f $(EXE)
