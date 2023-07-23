#include <socket/UDPSocketClient.h>

#include <atomic>
#include <condition_variable>
#include <future>

class UDPSocketClientCondition {
public:
    std::atomic_bool quit;
    std::condition_variable condition;
    std::mutex mutex;
};

UDPSocketClient::UDPSocketClient(const std::shared_ptr<ISocketListener>& listener)
    : mReceiver(), mImpl(), mCondition(new UDPSocketClientCondition), mListeners(listener) {
    SocketFD socketfd;
    mImpl = std::move(std::make_unique<UDPSocketClientImpl>(socketfd));
}

UDPSocketClient::~UDPSocketClient() { Disconnect(); }

SocketResult UDPSocketClient::Connect(const SocketAddressIn& address) {
    SocketResult result = -1;

    result = mImpl->Open(address);
    mCondition->quit.store(false);

    mReceiver = std::make_unique<std::thread>([this]() {
        static auto repeats = 0;
        while (!mCondition->quit.load()) {
            repeats++;
            ByteBuffer buffer;
            if (repeats % 10000 == 0) {
                // printf("Read() ++\n");
            }
            if (mImpl->Read(buffer) != -1) {
                mListeners->onBufferReceived(buffer);
                printf("Read() 00 %s\n", buffer.data());
            } else if (repeats % 50000 == 0) {
                printf("Read() --\n");
            }
        }
    });
    return result;
}

SocketResult UDPSocketClient::Post(const ByteBuffer& buffer) {
    SocketResult result = 0;
    auto future = std::async([&] {
        if (!mCondition->quit.load()) {
            printf("Post() : %s\n", buffer.data());
            return mImpl->Write(buffer);
        }
        return -1;
    });
    result = future.get();
    // result = mImpl->Write(buffer);
    return result;
}

SocketResult UDPSocketClient::Disconnect() {
    SocketResult result = 0;
    mCondition->quit.store(true);

    if (mReceiver->joinable()) {
        mReceiver->join();
    }
    result = mImpl->Close();
    return result;
}

std::string UDPSocketClient::GetIpAddress() const { return mImpl->GetIpAddress(); }

uint32_t UDPSocketClient::getPortNumber() const { return mImpl->getPortNumber(); }
