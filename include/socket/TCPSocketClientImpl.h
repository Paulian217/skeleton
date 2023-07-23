#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_TCPSOCKETCLIENTIMPL_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_TCPSOCKETCLIENTIMPL_H

#include <socket/IClientSocket.h>

class TCPSocketClientImpl : public IClientSocket {
public:
    explicit TCPSocketClientImpl(SocketFD& socketfd);
    virtual ~TCPSocketClientImpl();

    SocketResult Open(const SocketAddressIn& addr) override;
    SocketResult Write(const ByteBuffer& buffer) override;
    SocketResult Read(ByteBuffer& buffer) override;
    SocketResult Close() override;
    SocketResult Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) override;

    std::string getIpAddress();
    uint32_t getPortNumber();

private:
    SocketFD mSocketFd;
    SocketState mSocketState;
    SocketAddressIn mSocketAddress;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_TCPSOCKETCLIENTIMPL_H