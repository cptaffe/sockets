#include <stdio.h>
#include <time.h>

#import "socket.h"

#define BACKLOG 4

void forkcomm(int c) {
    char msg[] = "hello.\n";
    write(c, msg, sizeof msg);

    char str[BUFSIZ]; int bytes;
    while ((bytes = read(c, &str, BUFSIZ)) > 0) {
        write(c, str, bytes); // print
    }
    close(c);
}

int main() {
    register int s, c;
    int b;
    struct sockaddr_in sa;
    time_t t;
    struct tm *tm;

    if ((s = getsock()) < 0) {
        perror("chatd socket");
        exit(1);
    }

    sa = *sockaddrn(13, INADDR_ANY, &sa);

    if (getbind(s, &sa) < 0) {
        perror("chatd bind"); exit(2);}

    // create daemon process
    switch (fork()) {
        case -1:
            perror("chatd fork");
            exit(3);
            break;
        default:
            close(s);
            exit(0);
            break;
        case 0:
            break;
    }

    listen(s, BACKLOG);

    while (1) {
        b = sizeof sa;

        if ((c = getaccept(s, &sa)) < 0) {
            perror("chatd accept"); exit(4);
        }

        switch (fork()) {
            case -1:
                perror("chatd fork");
                exit(5);
                break;
            case 0:
                close(s);
                forkcomm(c);
                exit(0);
                break;
        }
    }
}