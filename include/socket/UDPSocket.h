#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKET_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKET_H_

#include <socket/ISocket.h>

#include <atomic>
#include <thread>

class UDPSocketServer : public IServerSocket {
public:
    explicit UDPSocketServer(int& socketId);
    virtual ~UDPSocketServer();

    SocketResult Bind(const uint16_t& port, const std::string& ipAddr = "0.0.0.0") override;
    SocketResult Listen(const size_t& maxClients = MAX_CLIENT) override;
    SocketFd Accept() override;
    SocketResult Read(const SocketFd& socketId, Buffer& buffer) override;
    SocketResult Write(const SocketFd& socketId, Buffer& buffer) override;
    SocketResult Close() override;
    SocketResult Close(const SocketFd& socketId) override;
    SocketFd GetSocketFd() const override;

private:
    int mSocketId;
    uint16_t mCurrentIpPort;
    std::string mCurrentIpAddr;
};

class UDPSocketClient : public IClientSocket {
public:
    explicit UDPSocketClient(int& socketId);
    virtual ~UDPSocketClient();

    SocketResult Connect(const uint16_t& port, const std::string& ipAddr) override;
    SocketResult Read(Buffer& buffer) override;
    SocketResult Write(Buffer& buffer) override;
    SocketResult Close() override;
    SocketFd GetSocketFd() const override;

private:
    int mSocketId;
    uint16_t mCurrentIpPort;
    std::string mCurrentIpAddr;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_UDPSOCKET_H_