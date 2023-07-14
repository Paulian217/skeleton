#include <signal.h>
#include <socket/UDPSocket.h>

#include <atomic>
#include <map>
#include <mutex>
#include <sstream>
#include <thread>

using namespace std;

static mutex mtx;
static atomic_bool thread_stop(true);
static void onSigTerm(int arg) { thread_stop.store(true); }

int main() {
    signal(SIGTERM, onSigTerm);
    thread th = thread([&]() {
        SocketFd socketId;
        UDPSocketServer server(socketId);
        if (server.Bind(8082) < 0) {
            return;
        }

        if (server.Listen() < 0) {
            return;
        }

        map<SocketFd, thread> threadPool;

        int repeat = 0;
        thread_stop.store(false);
        while (!thread_stop.load()) {
            auto clientSocketId = server.Accept();
            thread socketRunner = thread([&, clientSocketId]() {
                Buffer received;
                Buffer sending;

                server.Read(clientSocketId, received);

                stringstream strstream;
                strstream << "Reply from UDPServer : " << string(received.get().begin(), received.get().end());
                sending = Buffer(strstream.str());
                server.Write(clientSocketId, sending);

                server.Close(clientSocketId);
                unique_lock<mutex> lock(mtx);
                threadPool.erase(clientSocketId);
            });

            unique_lock<mutex> lock(mtx);
            threadPool[clientSocketId] = std::move(socketRunner);
        }

        for (auto& pth : threadPool) {
            server.Close(pth.first);
            if (pth.second.joinable()) {
                pth.second.join();
            }
        }

        server.Close();
    });

    th.join();
    return 0;
}