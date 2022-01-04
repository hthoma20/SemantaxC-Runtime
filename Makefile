gpp_flags = -g -Isrc
valgrind_flags = --leak-check=yes --error-exitcode=1

VPATH = src:test

runtime_headers = allocator.h types.h progcalls.h
runtime_sources = allocator.cpp types.cpp progcalls.cpp

runtime_objects = allocator.o types.o progcalls.o

test_headers = test_utils.h allocator_test.h progcalls_test.h
test_sources = test_utils.cpp allocator_test.cpp progcalls_test.cpp runtime_test.cpp

.DUMMY: runtests
runtests: tests
	valgrind $(valgrind_flags) ./tests

tests: $(test_headers) $(test_sources) $(runtime_objects)
	g++ $(gpp_flags) $(addprefix test/,$(test_sources)) $(runtime_objects) -o tests

.DUMMY: runtime
runtime: $(runtime_objects)

progcalls.o: progcalls.cpp progcalls.h allocator.o types.o 
	g++ $(gpp_flags) -c $< -o progcalls.o

types.o: types.cpp types.h allocator.o 
	g++ $(gpp_flags) -c $< -o types.o

allocator.o: allocator.cpp allocator.h
	g++ $(gpp_flags) -c $< -o allocator.o

.DUMMY: clean
clean:
	rm -f *.o tests
