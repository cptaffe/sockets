#include <stdio.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // inet stuffs (ipv4)
#include <arpa/inet.h> // inet_addr
#include <errno.h> // errors

// Socket: ip v4 w/ TCP
int get6sock() {
	return socket(PF_INET6, SOCK_STREAM, 0);
}

// Connection
int get6conn(int s, char *str) {
	struct sockaddr_in6 sa = {0};
	// Connection Struct
	sa.sin6_family = AF_INET6;
	sa.sin6_port = htons(13); // host to network endian conversion
	inet_pton(AF_INET6, str, &sa.sin6_addr); // stores network ordered addr in string (dot notation) to sa.sin_addr.s_addr (super convenient).

	return connect(s, (struct sockaddr *) &sa, sizeof sa);
}




int main(int argc, char *argv[]) {
	int s, conn, bytes;
	char buffer[BUFSIZ+1] = {0};

	// check args
	if (argc < 2) {
		printf("no address argument\n");
		return 1;}

	if ((s = get6sock()) < 0) {perror("socket"); ipv6 = 1;}

	if ((conn = get6conn(s, argv[1])) < 0) {
		if (errno != ECONNREFUSED) {perror("connect");}
		close(s); ipv6 = 2;}

	// Read from connection
	while ((bytes = read(s, buffer, BUFSIZ)) > 0) {
		write(1, buffer, bytes);}

	// close and return
	close(s);
	return 0;
}