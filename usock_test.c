#include <sys/socket.h>
#include <netinet/in.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "uloop.h"
#include "usock.h"

static struct uloop_fd server;
static const char *port = "10000";

static void server_cb(struct uloop_fd *fd, unsigned int events)
{
    struct sockaddr_in cli;
    unsigned int sl = sizeof(struct sockaddr_in);
    int sfd;

    sfd = accept(server.fd, (struct sockaddr *) &cli, &sl);
    if (sfd < 0) {
        fprintf(stderr, "Accept failed\n");
        return;
    }

    fprintf(stderr, "New connection\n");

    while (1) {
        int r;
        char buf[32];

	    fcntl(sfd, F_SETFL, fcntl(sfd, F_GETFL) & ~O_NONBLOCK);
        if ((r = read(sfd, buf, sizeof(buf))) <= 0) {
            if (errno == EAGAIN) {
                fprintf(stderr, "EAGAIN");
                continue;
            }

            fprintf(stderr, "Disconnected (%d): %s\n", r, strerror(errno));
            close(sfd);
            break;
        }
        buf[r] = 0;
        fprintf(stderr, "%s", buf);
        sleep(1);
    }

    uloop_fd_delete(&server);
    close(server.fd);
}

static int run_server(void)
{
#if 0
    server.cb = server_cb;
    server.fd = usock(USOCK_TCP | USOCK_SERVER | USOCK_IPV4ONLY, "127.0.0.1", port);
    if (server.fd < 0) {
        perror("usock");
        return 1;
    }

    uloop_init();
    uloop_fd_add(&server, ULOOP_READ);
    uloop_run();
#else
    server.fd = usock(USOCK_TCP | USOCK_IPV4ONLY, "shashakeaiduo.com", port);
    if (server.fd < 0) {
        perror("usock");
        return 1;
    }

    while (1) {
        int r;
        char buf[32];

        if ((r = read(server.fd, buf, sizeof(buf))) <= 0) {
            if (errno == EAGAIN) {
                fprintf(stderr, "EAGAIN");
                continue;
            }

            fprintf(stderr, "Disconnected (%d): %s\n", r, strerror(errno));
            close(server.fd);
            break;
        }
        buf[r] = 0;
        fprintf(stderr, "%s", buf);
        sleep(1);
    }

    close(server.fd);
#endif
    return 0;
}

static int usage(const char *name)
{
	fprintf(stderr, "Usage: %s -p <port>\n", name);
	return 1;
}

int main(int argc, char **argv)
{
	int ch;

	while ((ch = getopt(argc, argv, "p:")) != -1) {
		switch(ch) {
		case 'p':
			port = optarg;
			break;
		default:
			return usage(argv[0]);
		}
	}

	return run_server();
}
