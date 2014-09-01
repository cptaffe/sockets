CC=clang
CFLAGS=-O3 -std=c11

time:
	$(CC) $(CFLAGS) time.c -o time
	$(CC) $(CFLAGS) timed.c -o timed

clean:
	rm time timed