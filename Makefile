gpp_flags = -g
valgrind_flags = --leak-check=yes --error-exitcode=1

runtest: buildtest
	valgrind $(valgrind_flags) ./build/test

buildtest: allocator.o test/allocator_test.cpp
	g++ $(gpp_flags) test/allocator_test.cpp build/allocator.o -o build/test

allocator.o: build src/allocator.cpp src/allocator.h
	g++ $(gpp_flags) -c src/allocator.cpp -o build/allocator.o

build:
	mkdir build

clean:
	rm -rf build
