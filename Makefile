
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude -g

CORE = src/field.c src/vector.c src/matrix.c

.PHONY: all test run clean sanitize

all: build/test_worklet1 build/test_matrix_types build/matrix_classifier

build:
	mkdir -p build

build/test_worklet1: $(CORE) tests/test_worklet1.c | build
	$(CC) $(CFLAGS) $(CORE) tests/test_worklet1.c -o $@

build/test_matrix_types: src/field.c src/matrix.c src/matrix_types.c tests/test_matrix_types.c | build
	$(CC) $(CFLAGS) src/field.c src/matrix.c src/matrix_types.c tests/test_matrix_types.c -o $@

build/matrix_classifier: src/field.c src/matrix.c src/matrix_types.c src/main.c | build
	$(CC) $(CFLAGS) src/field.c src/matrix.c src/matrix_types.c src/main.c -o $@

test: all
	./build/test_worklet1
	./build/test_matrix_types

run: build/matrix_classifier
	./build/matrix_classifier

clean:
	rm -rf build

sanitize:
	$(MAKE) clean
	$(MAKE) all CFLAGS="-std=c11 -Wall -Wextra -Wpedantic -Iinclude -g -fsanitize=address,undefined -fno-omit-frame-pointer"
	$(MAKE) test CFLAGS="-std=c11 -Wall -Wextra -Wpedantic -Iinclude -g -fsanitize=address,undefined -fno-omit-frame-pointer"