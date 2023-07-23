#ifndef INCLUDE_SOCKET_UDPSOCKETCLIENT_H
#define INCLUDE_SOCKET_UDPSOCKETCLIENT_H

#include <socket/ISocketListener.h>
#include <socket/UDPSocketClientImpl.h>

#include <thread>

using Thread = std::thread;

class UDPSocketClientCondition;

class UDPSocketClient {
public:
    explicit UDPSocketClient(const std::shared_ptr<ISocketListener>& listener);
    virtual ~UDPSocketClient();

    SocketResult Connect(const SocketAddressIn& address);
    SocketResult Post(const ByteBuffer& buffer);
    SocketResult Disconnect();
    std::string GetIpAddress() const;
    uint32_t getPortNumber() const;

private:
    std::unique_ptr<Thread> mReceiver;
    std::unique_ptr<UDPSocketClientImpl> mImpl;
    std::unique_ptr<UDPSocketClientCondition> mCondition;
    const std::shared_ptr<ISocketListener> mListeners;
};

#endif  // INCLUDE_SOCKET_UDPSOCKETCLIENT_H
