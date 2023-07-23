#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_ISERVERSOCKET_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_ISERVERSOCKET_H

#include <socket/SocketAddress.h>
#include <socket/SocketConfigurable.h>

class IServerSocket : public SocketConfigurable {
public:
    virtual SocketResult Open(const SocketAddressIn &addr, const int32_t &maxClient = 0) = 0;
    virtual SocketResult Read(ByteBuffer &buffer, SocketAddressIn &addrin) = 0;
    virtual SocketResult Write(const ByteBuffer &buffer, const SocketAddressIn &addrin) = 0;
    virtual SocketResult Close() = 0;
    virtual SocketResult Configure(const int &opt, const int &optname, const void *data, const size_t &datalen) = 0;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_ISERVERSOCKET_H
