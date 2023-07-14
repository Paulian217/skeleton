#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <socket/UDPSocket.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

const constexpr int NO_OPTION = 0;

UDPSocketServer::UDPSocketServer(int& socketId) : mSocketId(-1) { mSocketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); }

UDPSocketServer::~UDPSocketServer() { Close(); }

SocketResult UDPSocketServer::Bind(const uint16_t& port, const std::string& ipAddr) {
    SocketResult res = -1;

    if (mSocketId < 0) {
        fprintf(stderr, "UDPSocketServer::%s() Socket is not created!\n", __func__);
        return res;
    }

    in_addr addr = {htonl(INADDR_ANY)};
    // res = inet_pton(AF_INET, ipAddr.data(), &addr.s_addr);
    // if (res < 0) {
    //     fprintf(stderr, "UDPSocketServer::%s() Ip Address: %s is not valid\n", __func__, ipAddr.c_str());
    //     return res;
    // }

    struct sockaddr_in sockaddr_in = {.sin_family = AF_INET, .sin_port = port};
    sockaddr_in.sin_addr.s_addr = htons(INADDR_ANY);
    res = bind(mSocketId, (sockaddr*)&sockaddr_in, sizeof(sockaddr_in));
    if (res < 0) {
        fprintf(stderr, "UDPSocketServer::%s() Socket bind is failed!\n", __func__);
    }

    mCurrentIpAddr = ipAddr;
    mCurrentIpPort = port;
    fprintf(stdout, "UDPSocketServer::%s() Socket(%d) is binded. - %s:%d\n", __func__, mSocketId, mCurrentIpAddr.c_str(), mCurrentIpPort);
    return res;
}

SocketResult UDPSocketServer::Listen(const size_t& maxClients /* = MAX_CLIENT */) {
    SocketResult res = -1;

    if (mSocketId < 0) {
        fprintf(stderr, "UDPSocketServer::%s() Socket is not created!\n", __func__);
        return res;
    }

    res = listen(mSocketId, maxClients);
    if (res < 0) {
        fprintf(stderr, "UDPSocketServer::%s() Socket(%d) is failed to listen! - %s:%d\n", __func__, mSocketId, mCurrentIpAddr.c_str(),
                mCurrentIpPort);
        return res;
    }
    fprintf(stdout, "UDPSocketServer::%s() Socket(%d) is now listening. - %s:%d\n", __func__, mSocketId, mCurrentIpAddr.c_str(), mCurrentIpPort);
    return res;
}

SocketFd UDPSocketServer::Accept() {
    struct sockaddr_in socketaddr;
    socklen_t socketaddr_len = static_cast<socklen_t>(sizeof(socketaddr));

    SocketFd socketId = accept(mSocketId, (struct sockaddr*)&socketaddr, &socketaddr_len);
    if (socketId < 0) {
        fprintf(stdout, "UDPSocketServer::%s() Socket(%d) is failed to accept! - %s:%d\n", __func__, mSocketId, mCurrentIpAddr.c_str(),
                mCurrentIpPort);
    }
    return socketId;
}

SocketResult UDPSocketServer::Read(const SocketFd& socketId, Buffer& buffer) {
    return recv(socketId, buffer.get().data(), sizeof(unsigned char), NO_OPTION);
}

SocketResult UDPSocketServer::Write(const SocketFd& socketId, Buffer& buffer) {
    return send(socketId, buffer.get().data(), buffer.size(), NO_OPTION);
}

SocketResult UDPSocketServer::Close() {
    SocketResult res = (mSocketId < 0) ? 0 : close(mSocketId);
    if (res >= 0) {
        mSocketId = -1;
    }
    return res;
}

SocketResult UDPSocketServer::Close(const SocketFd& socketId) {
    SocketResult res = (socketId < 0) ? 0 : close(socketId);
    return res;
}

SocketFd UDPSocketServer::GetSocketFd() const { return mSocketId; }

UDPSocketClient::UDPSocketClient(int& socketId) : mSocketId(-1) { mSocketId = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); }

UDPSocketClient::~UDPSocketClient() { Close(); }

SocketResult UDPSocketClient::Connect(const uint16_t& port, const std::string& ipAddr) {
    SocketResult res = -1;

    if (mSocketId < 0) {
        fprintf(stderr, "UDPSocketClient::%s() Socket is not created!\n", __func__);
        return res;
    }

    in_addr addr;
    res = inet_pton(AF_INET, ipAddr.data(), &addr.s_addr);
    if (res < 0) {
        fprintf(stderr, "UDPSocketClient::%s() Ip Address: %s is not valid\n", __func__, ipAddr.c_str());
        return res;
    }

    struct sockaddr_in sockaddr_in = {.sin_family = AF_INET, .sin_port = port};
    sockaddr_in.sin_addr = addr;
    res = connect(mSocketId, (sockaddr*)&sockaddr_in, sizeof(sockaddr_in));
    if (res < 0) {
        fprintf(stderr, "UDPSocketClient::%s() Socket connect is failed!\n", __func__);
    }

    mCurrentIpAddr = ipAddr;
    mCurrentIpPort = port;
    fprintf(stdout, "UDPSocketClient::%s() Socket(%d) is connected. - %s:%d\n", __func__, mSocketId, mCurrentIpAddr.c_str(), mCurrentIpPort);
    return res;
}

SocketResult UDPSocketClient::Read(Buffer& buffer) { return recv(mSocketId, buffer.get().data(), sizeof(unsigned char), NO_OPTION); }

SocketResult UDPSocketClient::Write(Buffer& buffer) { return send(mSocketId, buffer.get().data(), sizeof(unsigned char), NO_OPTION); }

SocketResult UDPSocketClient::Close() {
    SocketResult res = (mSocketId < 0) ? 0 : close(mSocketId);
    if (res >= 0) {
        mSocketId = -1;
    }
    return res;
}

SocketFd UDPSocketClient::GetSocketFd() const { return mSocketId; }
