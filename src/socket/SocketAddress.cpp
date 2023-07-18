#include <arpa/inet.h>
#include <socket/SocketAddress.h>

SocketAddressIn::SocketAddressIn() : sockaddr_in() {}

SocketAddressIn::SocketAddressIn(const std::string& ipv4, const uint32_t& port)
    : sockaddr_in((struct sockaddr_in){.sin_family = PF_INET, .sin_port = htons(port), .sin_addr = {.s_addr = inet_addr(ipv4.c_str())}}) {}

SocketAddressIn::SocketAddressIn(const struct sockaddr_in& sockaddr_in) : sockaddr_in(sockaddr_in) {}

SocketAddressIn::~SocketAddressIn() {}
