#include <stdio.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // inet stuffs (ipv4)
#include <arpa/inet.h> // inet_addr

int main(int argc, char *argv[]) {
	int s, conn, bytes;
	struct sockaddr_in sa = {0};
	char buffer[BUFSIZ+1] = {0};

	// check args
	if (argc < 2) {
		printf("no address argument\n");
		return 1;
	}

	// Fork into 10 processes
	/*for (int i = 0; i < 10; i++) {
		int pid = fork();
		if (pid == 0) {
			break;
		}
	}*/

	// Socket: ip v4 w/ TCP
	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		perror("socket");
		return 1;
	}

	// Connection Struct
	sa.sin_family = AF_INET;
	sa.sin_port = htons(13); // host to network short
	// ip address 165.193.126.229
	sa.sin_addr.s_addr = inet_addr(argv[1]);

	// Connection
	conn = connect(s, (struct sockaddr *) &sa, sizeof sa);
	if (conn < 0) {
		perror("connect");
		close(s);
		return 2;
	}

	// Read from connection
	while ((bytes = read(s, buffer, BUFSIZ)) > 0) {
		write(1, buffer, bytes);
	}

	// close and return
	close(s);
	return 0;
}