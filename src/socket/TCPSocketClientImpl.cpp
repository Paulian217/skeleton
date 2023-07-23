#include <fcntl.h>
#include <socket/TCPSocketClientImpl.h>
#include <unistd.h>

TCPSocketClientImpl::TCPSocketClientImpl(SocketFD& socketfd)
    : mSocketFd(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)),
      mSocketState((mSocketFd != NO_SOCKFD) ? SocketState::CREATED : SocketState::CLOSED),
      mSocketAddress() {}

TCPSocketClientImpl::~TCPSocketClientImpl() { printf("~TCPSocketClientImpl()\n"); }

SocketResult TCPSocketClientImpl::Open(const SocketAddressIn& addr) {
    SocketResult result = -1;
    if (SocketState::CLOSED == mSocketState) {
        mSocketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        mSocketState = (mSocketFd != NO_SOCKFD) ? SocketState::CREATED : SocketState::CLOSED;
    }

    result = connect(mSocketFd, (const struct sockaddr*)(&addr.sockaddr_in), sizeof(addr.sockaddr_in));
    if (result != -1) {
        int flags = fcntl(mSocketFd, F_GETFL, 0);
        fcntl(mSocketFd, F_SETFL, flags | SOCK_NONBLOCK);
        mSocketAddress = addr;
    }
    return result;
}

SocketResult TCPSocketClientImpl::Write(const ByteBuffer& buffer) {
    SocketResult result = -1;
    result = send(mSocketFd, buffer.data(), buffer.size(), 0);
    return result;
}

SocketResult TCPSocketClientImpl::Read(ByteBuffer& buffer) {
    auto readbytes = 0;
    buffer.assign(static_cast<size_t>(65535), static_cast<unsigned char>(0));
    readbytes = read(mSocketFd, buffer.data(), buffer.size());
    if (readbytes != -1) {
        buffer.resize(readbytes);
    }
    return readbytes;
}

SocketResult TCPSocketClientImpl::Close() {
    SocketResult result = 0;
    (void)close(mSocketFd);
    (void)shutdown(mSocketFd, SHUT_RDWR);
    return result;
}

SocketResult TCPSocketClientImpl::Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) {
    SocketResult result = -1;
    result = setsockopt(mSocketFd, opt, optname, data, datalen);
    return result;
}

std::string TCPSocketClientImpl::GetIpAddress() { return mSocketAddress.getIpv4(); }

uint32_t TCPSocketClientImpl::getPortNumber() { return mSocketAddress.getPort(); }
