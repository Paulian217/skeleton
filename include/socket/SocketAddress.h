#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_SOCKETADDRESS_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_SOCKETADDRESS_H_

#include <netinet/in.h>
#include <netinet/ip.h>
#include <socket/SocketType.h>
#include <sys/socket.h>

#include <string>

class SocketAddressIn {
public:
    SocketAddressIn();
    explicit SocketAddressIn(const std::string& ipv4, const uint32_t& port);
    explicit SocketAddressIn(const struct sockaddr_in& sockaddr_in);
    virtual ~SocketAddressIn();

public:
    struct sockaddr_in sockaddr_in;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_SOCKETADDRESS_H_