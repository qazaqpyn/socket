//: Socket.cpp
#include <sys/socket.h>
#include <unistd.h>

#include <system_error>

class Socket {
 private:
  int _fd = -1;

 public:
  Socket(int domain, int type, int protocol) {
    _fd = socket(domain, type, protocol);

    if (_fd < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Socket creation failed");
    }
  }

  Socket(int fd) : _fd(fd) {
    if (_fd < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Socket creation failed");
    }
  }

  ~Socket() {
    if (_fd >= 0) {
      close(_fd);
    }
  }

  // prevent copying
  Socket(const Socket &) = delete;
  Socket &operator=(const Socket &) = delete;

  // allow moving
  Socket(Socket &&other) noexcept : _fd(other._fd) { other._fd = -1; }

  Socket &operator=(Socket &&other) noexcept {
    if (this != &other) {
      if (_fd >= 0) {
        close(_fd);
      }
      _fd = other._fd;
      other._fd = -1;
    }
    return *this;
  }

  int get() const { return _fd; }
};