CC=clang
# gnu99 is standard.

time:
	$(CC) $(CFLAGS) time.c -o time
	$(CC) $(CFLAGS) timed.c -o timed

clean:
	rm time timed