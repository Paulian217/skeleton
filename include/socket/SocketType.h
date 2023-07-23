#ifndef __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETTYPE_H
#define __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETTYPE_H

#include <string>
#include <vector>

using SocketFD = int;
using SocketResult = int;
using ByteBuffer = std::vector<unsigned char>;

const constexpr int NO_OPTION = 0;
const constexpr int NO_SOCKFD = -1;

enum class SocketInterface { UDP,
                             TCP };

enum class SocketState { CREATED,
                         OPENED,
                         LISTENING,
                         CONNECTING,
                         CLOSED };

enum class SocketReturn { OK,
                          ENDOFFILE,
                          ERROR };

#endif  // __WORKSPACE_UTM_INCLUDE_SOCKET_SOCKETTYPE_H
