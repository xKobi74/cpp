CXX ?= g++
CXXFLAGS ?= -O2 -DNDEBUG

compile:
	$(CXX) main.cc -o q.out $(CXXFLAGS) -DQQ
	$(CXX) main.cc -o p.out $(CXXFLAGS) -DPERF
	$(CXX) main.cc -o a.out $(CXXFLAGS) -DQQ -DPERF
