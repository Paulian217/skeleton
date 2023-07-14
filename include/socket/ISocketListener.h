#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_ISOCKETLISTENER_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_ISOCKETLISTENER_H_

#include <socket/Buffer.h>

class ISocketListener {
public:
    virtual void onBufferReceived(const Buffer& buffer) = 0;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_ISOCKETLISTENER_H_
