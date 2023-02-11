PROGRAM := negate_image

run: $(PROGRAM).out
	./$(PROGRAM).out images/?.png

$(PROGRAM).out: $(PROGRAM).c
	gcc -fopenmp -o $(PROGRAM).out $(PROGRAM).c -lgd

