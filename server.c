#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "main.h"

static bool socket_to_server(int fd, int port, int limit)
{
    struct sockaddr_in server_addr;

    ZERO(server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    return (
        bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0 &&
        listen(fd, limit) == 0
    );
}

static int get_next_client(int fd)
{
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    char *client_ip;
    int result;

    ZERO(client_addr);
    result = accept(fd, (struct sockaddr *)&client_addr, &len);
    client_ip = inet_ntoa(client_addr.sin_addr);
    printf("Connection from: %s:%u\n", client_ip, ntohs(client_addr.sin_port));
    return (result);
}

static void answer_client(int fd)
{
    dprintf(fd, "Hello World!!!\n");
}

void server(int port)
{
    int fd;
    int client_fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        ERROR("Could not open socket");
    if (!socket_to_server(fd, port, 5))
        ERROR("Could not bind listening socket");
    client_fd = get_next_client(fd);
    answer_client(client_fd);
    close(client_fd);
    close(fd);
}

extern char *program_invocation_name;

static void usage(int fd)
{
    dprintf(
        fd,
        "stoopid that's not how it works!!\n"
        "plz do %s [port]\n",
        program_invocation_name
    );
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        usage(1);
        ERROR("Invalid usage");
    }
    server(atoi(argv[1]));
    return (EXIT_SUCCESS);
}
