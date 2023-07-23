#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_UDPSOCKETSERVERIMPL_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_UDPSOCKETSERVERIMPL_H

#include <socket/IServerSocket.h>

#include <thread>

class UDPSocketServerImpl : public IServerSocket {
public:
    explicit UDPSocketServerImpl(SocketFD& socketfd);
    virtual ~UDPSocketServerImpl();
    SocketResult Open(const SocketAddressIn& addr, const int32_t& maxClient = 0) override;
    SocketResult Read(ByteBuffer& buffer, SocketAddressIn& addrin) override;
    SocketResult Write(const ByteBuffer& buffer, const SocketAddressIn& addrin) override;
    SocketResult Close() override;
    SocketResult Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) override;

private:
    SocketFD mSocketFd;
    SocketState mSocketState;
    SocketAddressIn mSocketAddress;

    std::thread mThread;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_UDPSOCKETSERVERIMPL_H
