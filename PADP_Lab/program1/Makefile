PROGRAM := monte_carlo

run: $(PROGRAM).out
	./$(PROGRAM).out

$(PROGRAM).out: $(PROGRAM).c
	gcc -fopenmp -o $(PROGRAM).out $(PROGRAM).c

