// Client side C/C++ program to demonstrate Socket
// programming
#if 0
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#else
#include <socket/TCPSocketClient.h>

#include <condition_variable>
#include <iostream>
#endif

#define IP_ADDRESS "127.0.0.1"
#define PORT 8080

#if 0
int main(int argc, char const* argv[]) {
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    for (auto i = 0; i < 10000; i++) {
        char buffer[1024] = {0};
        int bufferlen = sprintf(buffer, "%d", i);
        send(client_fd, buffer, bufferlen, 0);
        printf("Hello message sent\n");
        valread = read(client_fd, buffer, 1024);
        usleep(1000);
        // printf("buffer: %s, valread: %d\n", buffer, valread);
        // printf("received\n");
    }

    sleep(2);

    // closing the connected socket
    close(client_fd);
    return 0;
}

#else

#include <atomic>

std::mutex mutex;
std::condition_variable condition;
std::atomic_int32_t received;

class SimpleSocketListener : public ISocketListener {
public:
    void onBufferReceived(const ByteBuffer& buffer) {
        auto value = (atoi(reinterpret_cast<const char*>(buffer.data())));
        received.store(value);
        fprintf(stdout, "onBufferReceived: %s, %d\n", buffer.data(), value);
        if (received == 10000) {
            condition.notify_one();
        }
    }
};

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    std::string ipv4(argv[1]);
    uint32_t port = atoi(argv[2]);

    TCPSocketClient client(std::make_shared<SimpleSocketListener>());

    printf("Connect to %s:%u\n", ipv4.c_str(), port);
    (void)client.Connect(SocketAddressIn(ipv4, port));

    const uint32_t MAX = 10000;

    for (auto i = 0; i <= MAX; i++) {
        ByteBuffer buffer(16);
        sprintf((char*)buffer.data(), "%d", i);
        (void)client.Send(buffer);

        // std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    /* Wait until all response received ... */
    // std::unique_lock<std::mutex> lock(mutex);
    // condition.wait(lock, [&] { return received == MAX; });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    printf("Disconnect from %s:%u\n", client.getIpAddress().c_str(), client.getPortNumber());
    (void)client.Disconnect();
    return 0;
}
#endif
