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
    (void)mImpl->Open(address);

    mReceiver = std::move(std::make_unique<std::thread>([this]() {
        while (!mCondition->quit.load()) {
            ByteBuffer buffer;
            // printf("TCPSocketClient::Read(), %d\n", mCondition->quit.load());
            if (mImpl->Read(buffer) != -1) {
                mListeners->onBufferReceived(buffer);
            }
        }
    }));

    mIsConnected = true;
    return result;
}

SocketResult TCPSocketClient::Send(const ByteBuffer& buffer) {
    SocketResult result = 0;
    std::future<int> future = std::async(std::launch::async, [&]() { return mImpl->Write(buffer); });
    result = future.get();
    return result;
}

SocketResult TCPSocketClient::Disconnect() {
    SocketResult result = 0;
    if (!mIsConnected) {
        return result;
    }

    mCondition->quit.store(true);

    if (mReceiver->joinable()) {
        mReceiver->join();
    }
    result = mImpl->Close();
    return result;
}

std::string TCPSocketClient::getIpAddress() const {
    return mImpl->getIpAddress();
}

uint32_t TCPSocketClient::getPortNumber() const {
    return mImpl->getPortNumber();
}
