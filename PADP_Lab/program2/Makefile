PROGRAM := matmul

run: $(PROGRAM).out
	./$(PROGRAM).out

matmul.out: $(PROGRAM).c
	gcc -fopenmp -o $(PROGRAM).out $(PROGRAM).c

