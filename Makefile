build_program: build_lib io.c io.h main.c
	cc io.c main.c bin/libeval.a -o bin/tic-tac-toe 
build_test:  build_lib io.c tests.c tests.h test.c
	cc io.c tests.c test.c bin/libeval.a -o bin/test
build_lib: create_dir eval.c eval.h 
	cc -c eval.c -o bin/eval.o 
	ar crs bin/libeval.a bin/eval.o
run_test: build_lib build_test
	bin/test
create_dir:
	mkdir -p bin
	ctags -R
clean:
	rm -rf bin
