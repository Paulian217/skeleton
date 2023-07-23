#include <arpa/inet.h>
#include <fcntl.h>
#include <socket/UDPSocketClientImpl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

UDPSocketClientImpl::UDPSocketClientImpl(SocketFD& socketfd)
    : mSocketFd(socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)),
      mSocketState((mSocketFd != NO_SOCKFD) ? SocketState::CREATED : SocketState::CLOSED) {
    socketfd = mSocketFd;
}

UDPSocketClientImpl::~UDPSocketClientImpl() { Close(); }

SocketResult UDPSocketClientImpl::Open(const SocketAddressIn& addr) {
    SocketResult result = 0;
    int flags = fcntl(mSocketFd, F_GETFL, 0);
    fcntl(mSocketFd, F_SETFL, flags | SOCK_NONBLOCK);
    mSocketAddress = addr;
    return result;
}

SocketResult UDPSocketClientImpl::Write(const ByteBuffer& buffer) {
    SocketResult result = -1;
    auto sendsize = sendto(mSocketFd, buffer.data(), buffer.size(), 0, (struct sockaddr*)&mSocketAddress.sockaddr_in,
                           sizeof(mSocketAddress.sockaddr_in));
    result = (sendsize != -1) ? 0 : -1;
    return result;
}

SocketResult UDPSocketClientImpl::Read(ByteBuffer& buffer) {
    SocketResult result = -1;

    buffer.resize(1024);
    unsigned char buf[1024];
    struct sockaddr_in sockaddr_in;
    socklen_t socklen = socklen_t();

    auto recvsize = recvfrom(mSocketFd, buffer.data(), buffer.size(), 0, (struct sockaddr*)&sockaddr_in, &socklen);
    if (recvsize == -1) {
        buffer.clear();
        return result;
    }

    // buffer.assign(&buf[0], &buf[recvsize]);
    result = 0;
    return result;
}

SocketResult UDPSocketClientImpl::Close() {
    SocketResult result = 0;
    if (mSocketFd == NO_SOCKFD) {
        return result;
    }

    (void)close(mSocketFd);

    result = shutdown(mSocketFd, SHUT_RDWR);
    mSocketFd = NO_SOCKFD;
    return result;
}

SocketResult UDPSocketClientImpl::Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) {
    return setsockopt(mSocketFd, opt, optname, data, datalen);
}

std::string UDPSocketClientImpl::getIpAddress() {
    return mSocketAddress.getIpv4();
}

uint32_t UDPSocketClientImpl::getPortNumber() {
    return mSocketAddress.getPort();
}
