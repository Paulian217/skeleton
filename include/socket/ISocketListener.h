#ifndef INCLUDE_SOCKET_ISOCKETLISTENER_H
#define INCLUDE_SOCKET_ISOCKETLISTENER_H

#include <socket/SocketType.h>

class ISocketListener {
public:
    virtual void onBufferReceived(const ByteBuffer& buffer) = 0;
};

#endif  // INCLUDE_SOCKET_ISOCKETLISTENER_H