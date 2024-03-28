CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
TARGETS = primes primes-i no-comment

SOURCES_primes = primes.c
SOURCES_no-comment = no-comment.c
SOURCES_error = error.c error.h

HEADERS = error.h bitset.h

all: $(TARGETS)

primes: $(SOURCES_primes)
	$(CC) $(CFLAGS) -O2 -o $@ $^ error.o

primes-i: $(SOURCES_primes)
	$(CC) $(CFLAGS) -O2 -DUSE_INLINE -o $@ $^ error.o

no-comment: $(SOURCES_no-comment)
	$(CC) $(CFLAGS) -o $@ $^ error.o

error.o: $(SOURCES_error)
	$(CC) $(CFLAGS) -c -o error.o $(SOURCES_error)

run-primes: primes
	ulimit -s 102400 && ./primes

run-primes-i: primes-i
	ulimit -s 102400 && ./primes-i

run-no-comment: no-comment
	./no-comment no-comment.c
	./no-comment no-comment.c >no-comment-result

run: run-primes run-primes-i run-no-comment

clean:
	rm -f $(TARGETS)