CC=clang
# gnu99 is standard.

chat:
	$(CC) $(CFLAGS) chat.c -o chat

clean:
	rm chat