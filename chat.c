#include <stdio.h>
#import "socket.h"

void readmsg(int s, char *str, int size) {
	int bytes;
	do {
		bytes = read(s, str, size);
		write(STDOUT_FILENO, str, bytes);
	} while (str[bytes - 1] != '\0');
}

void sndmsg(int s, char *str, int size) {
	int bytes;
	do {
		bytes = read(STDIN_FILENO, str, size - 1);
		str[bytes++] = '\0';
		write(s, str, bytes);
	} while (bytes == 0);
}

int main(int argc, char *argv[]) {
	int s, conn, ch;
	struct sockaddr_in sa;

	// check args
	if (argc < 2) {
		printf("no address argument\n");
		exit(1);}

	if ((s = getsock()) < 0) {perror("socket"); exit(2);}

	sa = *sockaddr(13, argv[1], &sa);

	if ((conn = getconn(s, &sa)) < 0) {
		perror("connect");
		close(s); exit(3);}

	// Read from connection, write to stdout
	char str[BUFSIZ]; int bytes;

	char sprefix[] = "server: ";
	char cprefix[] = "you: ";

	while (1) {
		write(STDOUT_FILENO, sprefix, sizeof sprefix);
		readmsg(s, str, BUFSIZ);
		write(STDOUT_FILENO, cprefix, sizeof cprefix);
		sndmsg(s, str, BUFSIZ);
	}

	// close and return
	close(s);
	exit(0);
}