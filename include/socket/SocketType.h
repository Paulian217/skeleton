#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_SOCKETTYPE_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_SOCKETTYPE_H_

#include <string>
#include <vector>

using SocketFD = int;
using SocketResult = int;
using ByteBuffer = std::vector<unsigned char>;

const constexpr int NO_OPTION = 0;
const constexpr int NO_SOCKFD = -1;

enum class SocketInterface { UDP, TCP };

enum class SocketState { CREATED, OPENED, CLOSED };

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_SOCKETTYPE_H_