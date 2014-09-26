CC    := mpicc
CFLAGS = -g -O2 -Wall -std=c99 -fopenmp

TESTS = hello-mpi hello-omp

all: $(TESTS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(TESTS)
	-rm -rf *.dSYM

