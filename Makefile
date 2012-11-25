program: eval.c eval.h io.c io.h main.c tests.c tests.h
	mkdir -p bin
	cc -o bin/program eval.c eval.h io.c io.h main.c tests.c tests.h
clean:
	rm -rf *.o program bin
