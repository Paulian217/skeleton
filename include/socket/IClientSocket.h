#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_ICLIENTSOCKET_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_ICLIENTSOCKET_H_

#include <socket/SocketAddress.h>

class IClientSocket {
public:
    virtual SocketResult Open(const SocketAddressIn& addr) = 0;
    virtual SocketResult Write(const ByteBuffer& buffer) = 0;
    virtual SocketResult Read(ByteBuffer& buffer) = 0;
    virtual SocketResult Close() = 0;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_ICLIENTSOCKET_H_