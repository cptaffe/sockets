CC=clang
# gnu99 is standard.

time:
	$(CC) $(CFLAGS) time.c -o time
	$(CC) $(CFLAGS) timed.c -o timed

time6:
	$(CC) $(CFLAGS) time6.c -o time6
	$(CC) $(CFLAGS) time6d.c -o time6d

clean:
	rm time timed
	rm time6 time6d