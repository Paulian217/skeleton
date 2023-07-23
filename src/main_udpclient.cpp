// uecho_client.c
#include <socket/UDPSocketClient.h>
#include <socket/UDPSocketClientImpl.h>

#include <atomic>
#include <condition_variable>
#include <iostream>

const constexpr int MAX = 10000;

std::mutex mutex;
std::condition_variable condition;
int32_t received;

void error_handling(const std::string &message);

class SimpleSocketListener : public ISocketListener {
public:
    void onBufferReceived(const ByteBuffer &buffer) override {
        std::unique_lock<std::mutex> lock(mutex);
        received = atoi(reinterpret_cast<const char *>(buffer.data()));
        condition.notify_all();
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

    printf("Post packets begin ++\n");
    for (auto i = 0; i <= MAX; i++) {
        ByteBuffer buffer(16);
        sprintf((char *)buffer.data(), "%d", i);
        (void)client.Post(buffer);
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
    printf("Post packets end --\n");

    /* Wait until all response received ... */
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [&] {
        printf("received: %d\n", received);
        return received == MAX;
    });
    printf("Received all messages!\n");

    printf("Disconnect from %s:%u\n", client.GetIpAddress().c_str(), client.getPortNumber());
    (void)client.Disconnect();
    return 0;
}

void error_handling(const std::string &message) {
    fprintf(stderr, "%s\n", message.c_str());
    exit(1);
}