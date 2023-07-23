#ifndef INCLUDE_SOCKET_TCPSOCKETCLIENT_H
#define INCLUDE_SOCKET_TCPSOCKETCLIENT_H

#include <socket/ISocketListener.h>
#include <socket/TCPSocketClientImpl.h>

#include <thread>

using Thread = std::thread;

class TCPSocketClientCondition;

class TCPSocketClient {
public:
    explicit TCPSocketClient(const std::shared_ptr<ISocketListener>& listener);
    virtual ~TCPSocketClient();

    SocketResult Connect(const SocketAddressIn& address);
    SocketResult Send(const ByteBuffer& buffer);
    SocketResult Disconnect();
    std::string getIpAddress() const;
    uint32_t getPortNumber() const;

private:
    bool mIsConnected = false;
    std::unique_ptr<Thread> mReceiver;
    std::unique_ptr<TCPSocketClientImpl> mImpl;
    std::unique_ptr<TCPSocketClientCondition> mCondition;
    const std::shared_ptr<ISocketListener> mListeners;
};

#endif  // INCLUDE_SOCKET_TCPSOCKETCLIENT_H
