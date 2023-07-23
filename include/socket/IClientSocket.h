#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_ICLIENTSOCKET_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_ICLIENTSOCKET_H

#include <socket/SocketAddress.h>
#include <socket/SocketConfigurable.h>

class IClientSocket : public SocketConfigurable {
public:
    virtual SocketResult Open(const SocketAddressIn& addr) = 0;
    virtual SocketResult Write(const ByteBuffer& buffer) = 0;
    virtual SocketResult Read(ByteBuffer& buffer) = 0;
    virtual SocketResult Close() = 0;
    virtual SocketResult Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) = 0;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_ICLIENTSOCKET_H