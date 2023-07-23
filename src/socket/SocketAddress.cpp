#include <arpa/inet.h>
#include <socket/SocketAddress.h>

SocketAddressIn::SocketAddressIn() : sockaddr_in() {}

SocketAddressIn::SocketAddressIn(const std::string& ipv4, const uint32_t& port)
    : sockaddr_in((struct sockaddr_in){
          .sin_family = AF_INET,
          .sin_port = htons(port),
          .sin_addr = {inet_addr(ipv4.c_str())}}) {}

SocketAddressIn::SocketAddressIn(const struct sockaddr_in& sockaddr_in) : sockaddr_in(sockaddr_in) {}

SocketAddressIn::~SocketAddressIn() {}

std::string SocketAddressIn::getIpv4() const {
    char ipv4[INET_ADDRSTRLEN];
    std::fill_n(ipv4, INET_ADDRSTRLEN, 0);
    inet_ntop(AF_INET, &(sockaddr_in.sin_addr.s_addr), ipv4, INET_ADDRSTRLEN);
    return ipv4;
}
uint32_t SocketAddressIn::getPort() const {
    uint32_t port = 0;
    switch (sockaddr_in.sin_family) {
    case AF_INET:
        port = static_cast<uint32_t>(ntohs(sockaddr_in.sin_port));
        break;
    case AF_INET6:
        port = static_cast<uint32_t>(ntohs(((struct sockaddr_in6*)&sockaddr_in)->sin6_port));
        break;
    default:
        break;
    }
    return port;
}
