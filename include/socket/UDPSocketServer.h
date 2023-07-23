#ifndef INCLUDE_SOCKET_UDPSOCKETSERVER_H
#define INCLUDE_SOCKET_UDPSOCKETSERVER_H

#include <socket/ISocketListener.h>
#include <socket/UDPSocketServerImpl.h>

#include <functional>
#include <thread>

// class UDPSocketServer;
class UDPSocketServerCondition;

using Thread = std::thread;

class UDPSocketServer {
public:
    using SocketHandler = std::function<void(UDPSocketServer*, const SocketAddressIn&, const ByteBuffer&)>;

public:
    explicit UDPSocketServer(const SocketHandler& handler);
    virtual ~UDPSocketServer();

    SocketResult Listen(const SocketAddressIn& address, const bool& poll);
    SocketResult Post(const SocketAddressIn& address, const ByteBuffer& buffer);
    SocketResult Shutdown();

    std::string GetIpAddress() const;
    uint32_t GetPortNumber() const;

private:
    std::unique_ptr<Thread> mReceiver;
    std::unique_ptr<UDPSocketServerImpl> mImpl;
    std::unique_ptr<UDPSocketServerCondition> mCondition;
    std::vector<std::shared_ptr<ISocketListener>> mListeners;
    const SocketHandler mHandler;
};

#endif  // INCLUDE_SOCKET_UDPSOCKETSERVER_H
