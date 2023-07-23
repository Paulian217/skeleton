// uecho_client.c
#include <socket/UDPSocketClient.h>
#include <socket/UDPSocketClientImpl.h>

#include <atomic>
#include <condition_variable>
#include <iostream>

const constexpr int MAX = 5000;

std::mutex mutex;
std::condition_variable condition;
std::atomic_int32_t received;

void error_handling(const std::string &message);

class SimpleSocketListener : public ISocketListener {
public:
    void onBufferReceived(const ByteBuffer &buffer) override {
        received.store(atoi(reinterpret_cast<const char *>(buffer.data())));
        condition.notify_one();
    }
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    std::string ipv4(argv[1]);
    uint32_t port = atoi(argv[2]);

    UDPSocketClient client(std::make_shared<SimpleSocketListener>());

    printf("Connect to %s:%u\n", ipv4.c_str(), port);
    (void)client.Connect(SocketAddressIn(ipv4, port));

    for (auto i = 0; i <= MAX; i++) {
        ByteBuffer buffer(16);
        sprintf((char *)buffer.data(), "%d", i);
        (void)client.Send(buffer);
    }

    /* Wait until all response received ... */
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [&] { return received.load() == MAX; });

    printf("Disconnect from %s:%u\n", client.getIpAddress().c_str(), client.getPortNumber());
    (void)client.Disconnect();
    return 0;
}

void error_handling(const std::string &message) {
    fprintf(stderr, "%s\n", message.c_str());
    exit(1);
}