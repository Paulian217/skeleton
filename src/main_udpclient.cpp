#include <signal.h>
#include <socket/UDPSocket.h>

#include <atomic>
#include <sstream>
#include <thread>

using namespace std;

static atomic_bool thread_stop(true);
static void onSigTerm(int arg) { thread_stop.store(true); }

int main() {
    signal(SIGTERM, onSigTerm);
    thread th = thread([&]() {
        SocketFd socketId;
        UDPSocketClient client(socketId);
        if (client.Connect(8082, "127.0.0.1") < 0) {
            return;
        }

        int repeat = 0;
        thread_stop.store(false);
        Buffer received;
        Buffer sending;

        while (!thread_stop.load()) {
            received.clear();
            client.Read(received);

            stringstream strstream;
            strstream << "Hello Server : " << (repeat++);
            sending = Buffer(strstream.str());
            client.Write(sending);
        }

        client.Close();
    });

    if (th.joinable()) {
        th.join();
    }
    return 0;
}