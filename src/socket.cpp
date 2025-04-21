#include "include/socket.hpp"

#include <unistd.h>

Socket::Socket(int domain, int type, int protocol) {
  _fd = socket(domain, type, protocol);
  if (_fd < 0) {
    throw std::system_error(errno, std::system_category(),
                            "Socket creation failed");
  }
}

Socket::Socket(int fd) : _fd(fd) {
  if (_fd < 0) {
    throw std::system_error(errno, std::system_category(),
                            "Invalid socket descriptor");
  }
}

Socket::~Socket() {
  if (_fd >= 0) {
    close(_fd);
  }
}

Socket::Socket(Socket&& other) noexcept : _fd(other._fd) { other._fd = -1; }

Socket& Socket::operator=(Socket&& other) noexcept {
  if (this != &other) {
    if (_fd >= 0) {
      close(_fd);
    }
    _fd = other._fd;
    other._fd = -1;
  }
  return *this;
}

int Socket::get() const { return _fd; }