#include <stdio.h>
#include <string.h>

#import "socket.h"

#define BACKLOG 4
#define PORT 6040

void forktosock(int s) {
    // Read from connection, write to stdout
    const int size = BUFSIZ;
    char str[size]; int bytes, total;

    // loop sends and recieves null-terminated strings.
    while (1) {
        // read from socket & print to stdout.
        total = 0;
        do {
            bytes = 0;
            bytes = read(s, str, size);
            total += bytes;
        } while (str[bytes - 1] != '\0' && bytes > 0); // end on read end or null terminator
        printf("\x1b[36mconn:\x1b[0m %s", str);
    }

    close(s);
}

void forktoin(int s) {
    // Read from connection, write to stdout
    const int size = BUFSIZ;
    char str[size]; int bytes;
    char cprefix[] = "you: ";

    // loop sends and recieves null-terminated strings.
    while (1) {
        do {
            bytes = read(STDIN_FILENO, str, size - 1);
            str[bytes++] = '\0'; // append with null byte
        } while (bytes == 0); // while nothing is read
        write(s, str, bytes);
    }

    close(s);
}

void forkreadwrite(int c) {
    // fork to read/write
    switch (fork()) {
        case -1:
            perror("chatd fork");
            exit(5);
            break;
        case 0:
            // call something that does input -> socket
            forktosock(c);
            exit(0);
            break;
        default:
            forktoin(c);
            exit(0);
            break;
    }
}

void conn_serve(char *ip) {
    int s, c;
    struct sockaddr_in sa;

    if ((s = getsock()) < 0) {perror("socket"); exit(1);}

    sa = *sockaddr(PORT, ip, &sa);

    if ((c = getconn(s, &sa)) < 0) {
        perror("connect");
        close(s); exit(2);}

    printf("\x1b[36mconnection established with server\x1b[0m\n");

    forkreadwrite(s);
}

void serve_conn() {
    int s, c;
    struct sockaddr_in sa;

    if ((s = getsock()) < 0) {perror("socket"); exit(1);}

    sa = *sockaddrn(PORT, INADDR_ANY, &sa);

    if (getbind(s, &sa) < 0) {
        perror("chatd bind"); exit(2);}

    listen(s, BACKLOG);

    while (1) {
        if ((c = getaccept(s, &sa)) < 0) {
            perror("chatd accept"); exit(4);
        }

        printf("\x1b[36mconnection established with client\x1b[0m\n");

        forkreadwrite(c);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s [serve | conn ip_addr]\n", argv[0]);
    } else if (strcmp(argv[1], "serve") == 0) {
        serve_conn();
    } else if (strcmp(argv[1], "conn") == 0) {
        conn_serve(argv[2]);
    }
    exit(0);
}