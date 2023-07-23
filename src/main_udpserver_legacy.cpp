// echo_server.c
#include <socket/UDPSocketServerImpl.h>

void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    int str_len;
    socklen_t clnt_adr_sz;

    struct sockaddr_in serv_adr, clnt_adr;
    if (argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    UDPSocketServer server(sock);
    if (sock == -1)
        error_handling("UDP socket creation error");

    if (server.Open(SocketAddressIn("0.0.0.0", atoi(argv[1]))) == -1)
        error_handling("bind() error");

    while (1) {
        SocketAddressIn sockaddrin;
        ByteBuffer buffer;
        if (-1 == server.Read(buffer, sockaddrin)) {
            error_handling("read() error");
        }

        printf("Message from client: \"%s\"\n", buffer.data());

        if (-1 == server.Write(buffer, sockaddrin)) {
            error_handling("write() error");
        }
    }
    server.Close();
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}