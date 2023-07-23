#include <socket/UDPSocketServer.h>

#include <atomic>
#include <condition_variable>
#include <future>

class UDPSocketServerCondition {
public:
    std::atomic_bool quit;
    std::condition_variable condition;
    std::mutex mutex;
};

UDPSocketServer::UDPSocketServer(const SocketHandler& handler) : mReceiver(), mImpl(), mCondition(new UDPSocketServerCondition), mHandler(handler) {
    SocketFD socketfd;
    mImpl = std::make_unique<UDPSocketServerImpl>(socketfd);
}

UDPSocketServer::~UDPSocketServer() { Shutdown(); }

SocketResult UDPSocketServer::Listen(const SocketAddressIn& address, const bool& poll) {
    SocketResult result = -1;
    result = mImpl->Open(address, 2);
    if (result == -1) {
        return result;
    }

    mCondition->quit.store(false);
    mReceiver = std::make_unique<std::thread>([this]() {
        while (!mCondition->quit.load()) {
            SocketAddressIn address;
            ByteBuffer buffer;
            if (mImpl->Read(buffer, address) != -1) {
                std::async([&]() { mHandler(this, address, buffer); });
            }
        }
    });
    return result;
}

SocketResult UDPSocketServer::Post(const SocketAddressIn& address, const ByteBuffer& buffer) {
    SocketResult result = -1;
    auto future = std::async([&] {
        if (!mCondition->quit.load()) {
            return mImpl->Write(buffer, address);
        }
        return -1;
    });
    result = future.get();
    return result;
}

SocketResult UDPSocketServer::Shutdown() {
    printf("Shutdown()");
    SocketResult result = 0;
    mCondition->quit.store(true);

    if (mReceiver->joinable()) {
        mReceiver->join();
    }
    result = mImpl->Close();
    return result;
}

std::string UDPSocketServer::GetIpAddress() const { return (mImpl != nullptr) ? mImpl->GetIpAddress() : "0.0.0.0"; }

uint32_t UDPSocketServer::GetPortNumber() const { return (mImpl != nullptr) ? mImpl->GetPortNumber() : 0; }
