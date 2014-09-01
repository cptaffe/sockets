#include <stdio.h>
#import "socket.h"

int main(int argc, char *argv[]) {
	int s, conn, bytes;
	char buffer[BUFSIZ+1] = {0};
	struct sockaddr_in sa;

	// check args
	if (argc < 2) {
		printf("no address argument\n");
		return 1;}

	if ((s = GETSOCK()) < 0) {perror("socket"); return 1;}

	sa = *sockaddr(13, argv[1], &sa);

	if ((conn = getconn(s, &sa)) < 0) {
		perror("connect");
		close(s); return 2;}

	// Read from connection
	while ((bytes = read(s, buffer, BUFSIZ)) > 0) {
		write(1, buffer, bytes);}

	// close and return
	close(s);
	return 0;
}