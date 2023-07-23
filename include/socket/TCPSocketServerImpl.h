#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_TCPSOCKETSERVER_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_TCPSOCKETSERVER_H

#include <socket/IServerSocket.h>

#include <map>

class TCPSocketServer : public IServerSocket {
public:
    explicit TCPSocketServer(SocketFD &socketfd);
    virtual ~TCPSocketServer();

    SocketResult Open(const SocketAddressIn &addr, const int32_t &maxClient = 0) override;
    SocketResult Read(ByteBuffer &buffer, SocketAddressIn &addrin) override;
    SocketResult Write(const ByteBuffer &buffer, const SocketAddressIn &addrin) override;
    SocketResult Close() override;
    SocketResult Configure(const int &opt, const int &optname, const void *data, const size_t &datalen) override;

private:
    SocketFD mSocketFd;
    SocketState mSocketState;
    SocketAddressIn mSocketAddress;
    std::map<SocketFD, SocketAddressIn> mClientSocketAddress;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_TCPSOCKETSERVER_H