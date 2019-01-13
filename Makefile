CC=clang
CPPCHECK=cppcheck
CFLAGS=-Wall -O3
LDFLAGS=-lSDL2
BINARY=raytracer
BINARY_TESTS=raytracer_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

raytracer: main.o math.o rasterizer.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

rasterizer.o: rasterizer.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

math.o: math.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

test: test.o math.o rasterizer.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o raytracer
