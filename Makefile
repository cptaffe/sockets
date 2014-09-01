CC=clang
CFLAGS=-O3 -std=gnu99

time:
	$(CC) $(CFLAGS) time.c -o time
	$(CC) $(CFLAGS) timed.c -o timed

clean:
	rm time timed