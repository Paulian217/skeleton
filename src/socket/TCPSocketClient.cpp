#include <socket/TCPSocketClient.h>

#include <atomic>
#include <condition_variable>
#include <future>

class TCPSocketClientCondition {
public:
    std::atomic_bool quit;
    std::condition_variable condition;
    std::mutex mutex;
};

TCPSocketClient::TCPSocketClient(const std::shared_ptr<ISocketListener>& listener)
    : mReceiver(), mImpl(), mCondition(new TCPSocketClientCondition), mListeners(listener) {
    SocketFD socketfd;
    mImpl = std::move(std::make_unique<TCPSocketClientImpl>(socketfd));
}

TCPSocketClient::~TCPSocketClient() {
    Disconnect();
    printf("~TCPSocketClient()\n");
}

SocketResult TCPSocketClient::Connect(const SocketAddressIn& address) {
    SocketResult result = -1;

    result = mImpl->Open(address);
    mCondition->quit.store(false);

    mReceiver = std::move(std::make_unique<std::thread>([this]() {
        while (!mCondition->quit.load()) {
            ByteBuffer buffer;
            if (mImpl->Read(buffer) != -1) {
                mListeners->onBufferReceived(buffer);
            }
        }
    }));

    return result;
}

SocketResult TCPSocketClient::Post(const ByteBuffer& buffer) {
    SocketResult result = 0;
    auto future = std::async([&] {
        if (!mCondition->quit.load()) {
            return mImpl->Write(buffer);
        }
        return -1;
    });
    result = future.get();
    return result;
}

SocketResult TCPSocketClient::Disconnect() {
    SocketResult result = 0;

    mCondition->quit.store(true);

    if (mReceiver->joinable()) {
        mReceiver->join();
    }
    result = mImpl->Close();
    return result;
}

std::string TCPSocketClient::GetIpAddress() const { return (mImpl != nullptr) ? mImpl->GetIpAddress() : "0.0.0.0"; }

uint32_t TCPSocketClient::GetPortNumber() const { return (mImpl != nullptr) ? mImpl->getPortNumber() : 0; }
