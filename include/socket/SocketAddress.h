#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETADDRESS_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETADDRESS_H

#include <netinet/in.h>
#include <netinet/ip.h>
#include <socket/SocketType.h>
#include <sys/socket.h>

#include <string>

class SocketAddressIn {
public:
    SocketAddressIn();
    explicit SocketAddressIn(const std::string &ipv4, const uint32_t &port);
    explicit SocketAddressIn(const struct sockaddr_in &sockaddr_in);
    virtual ~SocketAddressIn();

    std::string getIpv4() const;
    uint32_t getPort() const;

public:
    struct sockaddr_in sockaddr_in;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETADDRESS_H