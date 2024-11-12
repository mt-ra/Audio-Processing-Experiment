CXX = g++
CXXFLAGS = -Iinclude
LDFLAGS = -Llibs
LIBS = -lportsf -lfftw3
all: app

app: main.o Transformer.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o Transformer.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

Transformer.o: src/Transformer.cpp include/Transformer.h
	$(CXX) $(CXXFLAGS) -c src/Transformer.cpp -o $@

clean:
	rm -rf *.o app