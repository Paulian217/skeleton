#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_ISOCKET_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_ISOCKET_H_

#include <socket/ISocketListener.h>

#include <string>

using SocketResult = int;
using SocketFd = int;

const constexpr size_t MAX_CLIENT = 2;

class IServerSocket {
public:
    virtual SocketResult Bind(const uint16_t& port, const std::string& ipAddr) = 0;
    virtual SocketResult Listen(const size_t& maxClients) = 0;
    virtual SocketFd Accept() = 0;
    virtual SocketResult Read(const SocketFd& socketId, Buffer& buffer) = 0;
    virtual SocketResult Write(const SocketFd& socketId, Buffer& buffer) = 0;
    virtual SocketResult Close() = 0;
    virtual SocketResult Close(const SocketFd& socketId) = 0;
    virtual SocketFd GetSocketFd() const = 0;
};

class IClientSocket {
public:
    virtual SocketResult Connect(const uint16_t& port, const std::string& ipAddr) = 0;
    virtual SocketResult Read(Buffer& buffer) = 0;
    virtual SocketResult Write(Buffer& buffer) = 0;
    virtual SocketResult Close() = 0;
    virtual SocketFd GetSocketFd() const = 0;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_ISOCKET_H_