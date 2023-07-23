// echo_server.c
#include <signal.h>
#include <socket/UDPSocketServer.h>

UDPSocketServer* server;

void error_handling(char* message);
void signal_handle(int sig) { server->Shutdown(); }

int main(int argc, char* argv[]) {
    signal(SIGINT, signal_handle);
    signal(SIGTERM, signal_handle);
    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    UDPSocketServer::SocketHandler handler = [&](UDPSocketServer* self, const auto& address, const auto& buffer) {
        printf("Received Buffer: %s\n", buffer.data());
        self->Post(address, buffer);
    };
    UDPSocketServer socketServer(handler);
    server = &socketServer;

    if (socketServer.Listen(SocketAddressIn("0.0.0.0", atoi(argv[1])), true) == -1) {
        error_handling("Fail to listen");
    }

    socketServer.Shutdown();
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}