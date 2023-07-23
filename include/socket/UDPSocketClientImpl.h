#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_UDPSOCKETCLIENTIMPL_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_UDPSOCKETCLIENTIMPL_H

#include <socket/IClientSocket.h>

class UDPSocketClientImpl : public IClientSocket {
public:
    explicit UDPSocketClientImpl(SocketFD& socketfd);
    virtual ~UDPSocketClientImpl();

    SocketResult Open(const SocketAddressIn& addr) override;
    SocketResult Write(const ByteBuffer& buffer) override;
    SocketResult Read(ByteBuffer& buffer) override;
    SocketResult Close() override;
    SocketResult Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) override;

    std::string GetIpAddress();
    uint32_t getPortNumber();

private:
    SocketFD mSocketFd;
    SocketState mSocketState;
    SocketAddressIn mSocketAddress;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_UDPSOCKETCLIENTIMPL_H
