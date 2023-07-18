#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKETCLIENT_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKETCLIENT_H_

#include <IClientSocket.h>

class UDPSocketClient : public IClientSocket {
public:
    explicit UDPSocketClient(SocketFD& socketfd);
    virtual ~UDPSocketClient();
    SocketResult Open(const SocketAddressIn& addr) override;
    SocketResult Write(const ByteBuffer& buffer) override;
    SocketResult Read(ByteBuffer& buffer) override;
    SocketResult Close() override;

private:
    SocketFD mSocketFd;
    SocketState mSocketState;
    SocketAddressIn mSocketAddress;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKETCLIENT_H_