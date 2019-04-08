#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "main.h"


static bool socket_to_client(int fd, char *name, int port)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    server = gethostbyname(name);
    if (!server)
        ERROR("Could not resolve hostname");
    ZERO(serv_addr);
    serv_addr.sin_family = AF_INET;
    bcopy(
        (char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length
    );
    serv_addr.sin_port = htons(port);
    return (connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0);
}

static void get_answer(int fd)
{
    char buffer[256];
    int n;

    write(1, "Server said: ", 13);
    while ((n = read(fd, buffer, 256)) > 0)
        write(1, buffer, n);
    write(1, "\n", 1);
}


void request(char *name, int port)
{
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        ERROR("Could not open socket");
    if (!socket_to_client(fd, name, port))
        ERROR("Could connect socket");
    get_answer(fd);
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        ERROR("Invalid usage");
    request(argv[1], atoi(argv[2]));
    return (EXIT_SUCCESS);
}
