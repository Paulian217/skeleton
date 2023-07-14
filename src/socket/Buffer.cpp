#include <Buffer.h>

Buffer::Buffer(const size_t& reserved) : mByteArray(reserved) {}

Buffer::Buffer(const std::string& str) : mByteArray(str.begin(), str.end()) {}

Buffer::Buffer(const ByteArray& bytes) : mByteArray(bytes) {}

Buffer::~Buffer() {}

size_t Buffer::size() const { return mByteArray.size(); }

ByteArray& Buffer::get() { return mByteArray; }

Buffer& Buffer::resize(const size_t& len) {
    mByteArray.resize(len);
    return *this;
}

void Buffer::clear() { mByteArray.clear(); }
