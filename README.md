# C-Sockets-client-server-example

The server will accept any entering connection, display informations about it, reply with "Hello World!!!", then exit.
```
gcc -I. server.c -o server
./server [port]
```

The client will connect to a server, write its reply in standard output, then exits.
```
gcc -I. client.c -o client
./client [address] [port]
```
