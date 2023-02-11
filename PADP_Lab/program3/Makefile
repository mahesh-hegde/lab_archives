PROGRAM := sieve

run: $(PROGRAM).out
	./$(PROGRAM).out

$(PROGRAM).out: $(PROGRAM).cc
	g++ -O3 -fopenmp -o $(PROGRAM).out $(PROGRAM).cc

