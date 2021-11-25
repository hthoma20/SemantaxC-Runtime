gpp_flags = -g
build_dir = build


allocator.o: build src/allocator.cpp src/allocator.h
	g++ $(gpp_flags) -c src/allocator.cpp -o $(build_dir)/allocator.o


build:
	mkdir build