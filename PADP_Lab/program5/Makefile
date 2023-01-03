PROGRAM := message_passing

run: $(PROGRAM).out
	mpirun ./$(PROGRAM).out

$(PROGRAM).out: $(PROGRAM).c
	mpicc -o $(PROGRAM).out $(PROGRAM).c

