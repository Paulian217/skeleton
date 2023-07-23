#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETCONFIGURATION_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETCONFIGURATION_H

#include <socket/SocketType.h>

class SocketConfigurable {
public:
    virtual SocketResult Configure(const int& opt, const int& optname, const void* data, const size_t& datalen) = 0;
};

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETCONFIGURATION_H
