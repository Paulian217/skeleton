// uecho_client.c
#include <socket/UDPSocketClientImpl.h>

#include <iostream>

void error_handling(char* message);
int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_adr, from_adr;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    UDPSocketClient client(sock);
    if (sock == -1)
        error_handling("socket() error");

    SocketAddressIn sockaddrin(argv[1], atoi(argv[2]));
    if (client.Open(sockaddrin) == -1)
        error_handling("open() error");

    while (1) {
        std::string messagestr;
        std::cout << "Insert message(q to quit): ";
        std::cin >> messagestr;
        // fputs("Insert message(q to quit): ", stdout);
        // fgets(message, sizeof(message), stdin);
        // if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        //     break;
        if (!messagestr.compare("q") || !messagestr.compare("Q")) {
            break;
        }

        (void)client.Write(ByteBuffer(messagestr.begin(), messagestr.end()));

        ByteBuffer buffer;
        (void)client.Read(buffer);
        // buffer.insert(buffer.end(), 0);

        messagestr.assign(buffer.begin(), buffer.end());
        printf("Message from server: \"%s\"\n", messagestr.c_str());
    }
    client.Close();
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}