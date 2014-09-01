#include <stdio.h>
#include <time.h>

#import "socket.h"

#define BACKLOG 4

int main() {
    register int s, c;
    int b;
    struct sockaddr_in sa;
    time_t t;
    struct tm *tm;
    FILE *client;

    if ((s = getsock()) < 0) {
        perror("socket");
        return 1;
    }

    sa = *sockaddrn(13, INADDR_ANY, &sa);

    if (getbind(s, &sa) < 0) {
        perror("bind"); return 2;}

    switch (fork()) {
        case -1:
            perror("fork");
            return 3;
            break;
        default:
            close(s);
            return 0;
            break;
        case 0:
            break;
    }

    listen(s, BACKLOG);

    for (;;) {
        b = sizeof sa;

        if ((c = getaccept(s, &sa)) < 0) {
            perror("timed accept"); return 4;}

        if ((client = fdopen(c, "w")) == NULL) {
            perror("timed fdopen"); return 5;}

        if ((t = time(NULL)) < 0) {
            perror("timed time"); return 6;}

        tm = gmtime(&t);
        fprintf(client, "%.4i-%.2i-%.2iT%.2i:%.2i:%.2iZ\n",
            tm->tm_year + 1900,
            tm->tm_mon + 1,
            tm->tm_mday,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec);

        fclose(client);
    }
}