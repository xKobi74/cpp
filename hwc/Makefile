compile:
	g++ main.cc -o a.out -O2 -DNDEBUG
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