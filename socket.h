#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h> // inet stuffs (ipv4)
#include <arpa/inet.h> // inet_addr

// Connection
int _getconn(int s, struct sockaddr* sa) {
	return connect(s, sa, sizeof (struct sockaddr));
}

// Connection
int getconn(int s, struct sockaddr_in* sa) {
	return _getconn(s, (struct sockaddr *) sa);
}

// Connection
int get6conn(int s, struct sockaddr_in6* sa) {
	return _getconn(s, (struct sockaddr *) sa);
}

// Binding
int _getbind(int s, struct sockaddr* sa) {
	return bind(s, sa, sizeof (struct sockaddr));
}

// Binding
int getbind(int s, struct sockaddr_in* sa) {
	return _getbind(s, (struct sockaddr *) sa);
}

// Binding
int get6bind(int s, struct sockaddr_in6* sa) {
	return _getbind(s, (struct sockaddr *) sa);
}

int _getaccept(int s, struct sockaddr* sa) {
	size = sizeof (struct sockaddr);
	return accept(s, sa, (socklen_t *) &size);
}

int getaccept(int s, struct sockaddr_in* sa) {
	return _getaccept(s, (sockaddr *) sa);
}

int get6accept(int s, struct sockaddr_in6* sa) {
	return _getaccept(s, (sockaddr *) sa);
}

// ipv4 addr to int
/*int addrton(char *addr, struct sockaddr *sa) {
	inet_pton(AF_INET, addr, &sa->sin_addr);
}

// ipv6 addr to int
int addr6ton(char *addr, struct sockaddr *sa) {
	inet_pton(AF_INET6, addr, &sa->sin_addr);
}*/

// ipv4 struct
struct sockaddr_in *_sockaddr(int port, struct sockaddr_in *sa) {
	sa->sin_family = AF_INET;
	sa->sin_port = htons(port);
	return sa;
}

// ipv6 struct
struct sockaddr_in6 *_sock6addr(int port, struct sockaddr_in6 *sa) {
	sa->sin6_family = AF_INET6;
	sa->sin6_port = htons(port);
	return sa;
}

// fills ipv4 addr struct
struct sockaddr_in *sockaddr(int port, char *addr, struct sockaddr_in *sa) {
	sa = _sockaddr(port, sa);
	inet_pton(AF_INET, addr, &sa->sin_addr);
	return sa;
}

// fills ipv6 addr struct
struct sockaddr_in6 *sock6addr(int port, char *addr, struct sockaddr_in6 *sa) {
	sa = _sock6addr(port, sa);
	inet_pton(AF_INET6, addr, &sa->sin6_addr);
	return sa;
}

// fills ipv4 addr struct
struct sockaddr_in *sockaddrn(int port, int addr, struct sockaddr_in *sa) {
	sa = _sockaddr(port, sa);
	sa->sin_addr.s_addr = htonl(addr);
	return sa;
}

// fills ipv6 addr struct
struct sockaddr_in6 *sock6addrn(int port, int addr, struct sockaddr_in6 *sa) {
	sa = _sock6addr(port, sa);
	sa->sin6_addr.s6_addr[0] = htonl(addr);
	return sa;
}

// Socket: TCP
int _getsock(int n) {return socket(n, SOCK_STREAM, 0);}

// Socket: ip v4
int getsock() {return _getsock(PF_INET);}

// Socket: ip v6
int get6sock() {return _getsock(PF_INET6);}

