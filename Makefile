CC=clang
# gnu99 is standard.

chat:
	$(CC) $(CFLAGS) chat.c -o chat
	$(CC) $(CFLAGS) chatd.c -o chatd

clean:
	rm chat chatd

restart:
	sudo pkill chatd
	sudo ./chatd