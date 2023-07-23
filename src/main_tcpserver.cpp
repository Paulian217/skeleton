
// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <condition_variable>
#include <future>
#include <map>
#include <mutex>
#include <sstream>
#include <vector>
#define PORT 8080

#include <socket/SocketAddress.h>

std::atomic<bool> stopflag(false);
static void sighandler(int sig) {
    printf("signal handler: %d\n", sig);
    stopflag.store(true);
}

std::map<int, std::future<int>> futures;

static int asynchandler(int socketfd, const SocketAddressIn& sockaddr) {
    while (true) {
        int valread;
        char buffer[16] = {0};
        memset(buffer, 0, sizeof(buffer));
        valread = read(socketfd, buffer, 16);
        if (valread == 0) {
            printf("EOF!\n");
            break;
        }
        printf("buffer: %s, valread: %d\n", buffer, valread);
        send(socketfd, buffer, sizeof(buffer), 0);
    }
    // closing the connected socket
    printf("Client socket(%d) disconnected! - %s:%u\n", socketfd, sockaddr.getIpv4().c_str(), sockaddr.getPort());
    close(socketfd);
    return socketfd;
}

int main(int argc, char const* argv[]) {
    // signal(SIGTERM, sighandler);
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("server_socket: %d\n", server_fd);

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_KEEPALIVE | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::mutex mutex;
    std::condition_variable condition;

    while (!stopflag.load()) {
        printf("wait for accept\n");
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        printf("wakeup for accept\n");
        SocketAddressIn sockaddr(address);
        fprintf(stdout, "Client socket(%d) accepted! - %s:%u\n", new_socket, sockaddr.getIpv4().c_str(), sockaddr.getPort());
        std::async(std::launch::async, asynchandler, new_socket, sockaddr);
    }

    close(server_fd);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}