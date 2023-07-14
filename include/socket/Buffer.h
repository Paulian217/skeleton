#ifndef _WORKSPACES_CPP_INCLUDE_SOCKET_BUFFER_H_
#define _WORKSPACES_CPP_INCLUDE_SOCKET_BUFFER_H_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

using ByteArray = std::vector<unsigned char>;

const constexpr size_t MAX_BUFFER = 1024;

class Buffer {
public:
    explicit Buffer(const size_t& reserved = MAX_BUFFER);
    explicit Buffer(const std::string& str);
    explicit Buffer(const ByteArray& bytes);
    virtual ~Buffer();
    size_t size() const;
    ByteArray& get();
    Buffer& resize(const size_t& len);
    void clear();

private:
    ByteArray mByteArray;
};

#endif  // _WORKSPACES_CPP_INCLUDE_SOCKET_BUFFER_H_