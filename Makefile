CXX = g++
CXXFLAGS = -Iinclude
LDFLAGS = -Llibs
LIBS = -lportsf -lfftw3
all: app

app: main.o Transformer.o StreamProcessor.o lookup_gens.o window_processors.o portsf_wrappers.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o Transformer.o StreamProcessor.o lookup_gens.o window_processors.o portsf_wrappers.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $@

Transformer.o: src/Transformer.cpp include/Transformer.h
	$(CXX) $(CXXFLAGS) -c src/Transformer.cpp -o $@

StreamProcessor.o: src/StreamProcessor.cpp include/StreamProcessor.h
	$(CXX) $(CXXFLAGS) -c src/StreamProcessor.cpp -o $@

lookup_gens.o: src/lookup_gens.cpp include/lookup_gens.h
	$(CXX) $(CXXFLAGS) -c src/lookup_gens.cpp -o $@

window_processors.o: src/window_processors.cpp include/window_processors.h
	$(CXX) $(CXXFLAGS) -c src/window_processors.cpp -o $@

portsf_wrappers.o: src/portsf_wrappers.cpp include/portsf_wrappers.h
	$(CXX) $(CXXFLAGS) -c src/portsf_wrappers.cpp -o $@

clean:
	rm -rf *.o app