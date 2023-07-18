#include <arpa/inet.h>
#include <socket/UDPSocketClient.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

UDPSocketClient::UDPSocketClient(SocketFD& socketfd)
    : mSocketFd(socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)), mSocketState((mSocketFd != NO_SOCKFD) ? SocketState::CREATED : SocketState::CLOSED) {
    socketfd = mSocketFd;
}

UDPSocketClient::~UDPSocketClient() { Close(); }

SocketResult UDPSocketClient::Open(const SocketAddressIn& addr) {
    SocketResult result = 0;
    mSocketAddress = addr;
    return result;
}

SocketResult UDPSocketClient::Write(const ByteBuffer& buffer) {
    SocketResult result = -1;
    auto sendsize =
        sendto(mSocketFd, buffer.data(), buffer.size(), 0, (struct sockaddr*)&mSocketAddress.sockaddr_in, sizeof(mSocketAddress.sockaddr_in));
    if (sendsize != -1) {
        result = 0;
    }
    return result;
}

SocketResult UDPSocketClient::Read(ByteBuffer& buffer) {
    SocketResult result = -1;

    unsigned char buf[65535];
    struct sockaddr_in sockaddr_in;
    socklen_t socklen = socklen_t();

    auto recvsize = recvfrom(mSocketFd, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr_in, &socklen);
    if (recvsize == -1) {
        fprintf(stderr, "UDPSocketClient::%s() receive error\n", __func__);
        return result;
    }

    buffer.assign(&buf[0], &buf[recvsize]);
    result = 0;
    return result;
}

SocketResult UDPSocketClient::Close() {
    SocketResult result = 0;
    if (mSocketFd == NO_SOCKFD) {
        return result;
    }
    close(mSocketFd);
    mSocketFd = NO_SOCKFD;
    return result;
}
