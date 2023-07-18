#include <arpa/inet.h>
#include <socket/UDPSocketServer.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

UDPSocketServer::UDPSocketServer(SocketFD& socketfd)
    : mSocketFd(socket(PF_INET, SOCK_DGRAM, 0)), mSocketState((mSocketFd != NO_SOCKFD) ? SocketState::CREATED : SocketState::CLOSED) {
    socketfd = mSocketFd;
}

UDPSocketServer::~UDPSocketServer() { Close(); }

SocketResult UDPSocketServer::Open(const SocketAddressIn& addr) {
    SocketResult result = 0;
    if (SocketState::CLOSED == mSocketState) {
        mSocketFd = socket(PF_INET, SOCK_DGRAM, 0);
        if (mSocketFd != NO_SOCKFD) {
            mSocketState = SocketState::CREATED;
        }
    }

    result = bind(mSocketFd, (struct sockaddr*)&addr.sockaddr_in, sizeof(addr.sockaddr_in));
    if (result < 0) {
        return result;
    }
    mSocketState = SocketState::OPENED;
    mSocketAddress = addr;
    return result;
}

SocketResult UDPSocketServer::Read(ByteBuffer& buffer, SocketAddressIn& addrin) {
    SocketResult result = -1;
    if (SocketState::OPENED != mSocketState) {
        fprintf(stderr, "UDPSocketServer::%s() not opened\n", __func__);
        return result;
    }

    struct sockaddr_in sockaddr_in;
    socklen_t socklen = sizeof(sockaddr_in);

    unsigned char buf[65535];
    auto recvsize = recvfrom(mSocketFd, buf, sizeof(buf), 0, (struct sockaddr*)&sockaddr_in, &socklen);
    if (recvsize == -1) {
        fprintf(stderr, "UDPSocketServer::%s() recvfrom error\n", __func__);
        return result;
    }

    buffer.assign(&buf[0], &buf[recvsize]);
    buffer.insert(buffer.end(), 0);

    addrin.sockaddr_in = sockaddr_in;
    result = 0;
    return result;
}

SocketResult UDPSocketServer::Write(const ByteBuffer& buffer, const SocketAddressIn& addrin) {
    SocketResult result = -1;
    if (SocketState::OPENED != mSocketState) {
        fprintf(stderr, "UDPSocketServer::%s() not opened\n", __func__);
        return result;
    }

    result = sendto(mSocketFd, buffer.data(), buffer.size(), 0, (struct sockaddr*)&addrin.sockaddr_in, sizeof(addrin.sockaddr_in));
    if (result == -1) {
        fprintf(stderr, "UDPSocketServer::%s() sendto error\n", __func__);
        return result;
    }
    return result;
}

SocketResult UDPSocketServer::Close() {
    SocketResult result = 0;
    if (SocketState::OPENED != mSocketState) {
        return result;
    }
    close(mSocketFd);
    mSocketFd = NO_SOCKFD;
    mSocketState = SocketState::CLOSED;
    return result;
}
