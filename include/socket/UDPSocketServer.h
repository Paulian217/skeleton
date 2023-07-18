#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKETSERVER_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKETSERVER_H_

#include <socket/IServerSocket.h>

class UDPSocketServer : public IServerSocket {
public:
    explicit UDPSocketServer(SocketFD& socketfd);
    virtual ~UDPSocketServer();
    SocketResult Open(const SocketAddressIn& addr) override;
    SocketResult Read(ByteBuffer& buffer, SocketAddressIn& addrin) override;
    SocketResult Write(const ByteBuffer& buffer, const SocketAddressIn& addrin) override;
    SocketResult Close() override;

private:
    SocketFD mSocketFd;
    SocketState mSocketState;
    SocketAddressIn mSocketAddress;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKETSERVER_H_