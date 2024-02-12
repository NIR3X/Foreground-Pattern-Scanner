AR = ar
CXX = g++
CXXFLAGS = -std=c++2a -Wall -O2 -march=x86-64 -fno-rtti
LDFLAGS = -s -static -lwinhttp -lntdll

SRC = ForegroundPatternScanner.cpp
OBJ = $(SRC:.cpp=.o)
DEST = ForegroundPatternScanner.exe

build: fast_patterns_scanner file_mapping $(OBJ)
	$(CXX) $(OBJ) FastPatternsScanner.cpp/FastPatternsScanner.a FileMapping.cpp/FileMapping.a -o $(DEST) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

fast_patterns_scanner:
	$(MAKE) -C FastPatternsScanner.cpp

file_mapping:
	$(MAKE) -C FileMapping.cpp

clean:
	$(MAKE) -C FastPatternsScanner.cpp clean
	$(MAKE) -C FileMapping.cpp clean
	rm -f $(OBJ) $(DEST)
