#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_ISERVERSOCKET_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_ISERVERSOCKET_H_

#include <socket/SocketAddress.h>

class IServerSocket {
public:
    virtual SocketResult Open(const SocketAddressIn& addr) = 0;
    virtual SocketResult Read(ByteBuffer& buffer, SocketAddressIn& addrin) = 0;
    virtual SocketResult Write(const ByteBuffer& buffer, const SocketAddressIn& addrin) = 0;
    virtual SocketResult Close() = 0;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_ISERVERSOCKET_H_
