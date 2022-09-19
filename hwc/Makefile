CXX ?= g++
CXXFLAGS ?= -O2 -DNDEBUG

compile:
	$(CXX) main.cc -o a.out $(CXXFLAGS)
testq: compile
	./a.out 1 0 < test2.txt
testp: compile
	./a.out 0 1 < test2.txt
testa: compile
	./a.out 1 1 < test2.txt
startq: 
	./a.out 1 0
startp: 
	./a.out 0 1
starta: 
	./a.out 1 1