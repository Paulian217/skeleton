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
    (void)mImpl->Open(address);

    mReceiver = std::move(std::make_unique<std::thread>([this]() {
        while (!mCondition->quit.load()) {
            ByteBuffer buffer;
            if (mImpl->Read(buffer) != -1) {
                mListeners->onBufferReceived(buffer);
            }
        }
    }));

    mIsConnected = true;
    return result;
}

SocketResult UDPSocketClient::Send(const ByteBuffer& buffer) {
    SocketResult result = 0;
    std::future<int> future = std::async(std::launch::async, [&] { return mImpl->Write(buffer); });
    result = future.get();
    return result;
}

SocketResult UDPSocketClient::Disconnect() {
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

std::string UDPSocketClient::getIpAddress() const { return mImpl->getIpAddress(); }

uint32_t UDPSocketClient::getPortNumber() const { return mImpl->getPortNumber(); }
