#pragma once

#include <sys/socket.h>

#include <system_error>

class Socket {
 private:
  int _fd = -1;

 public:
  // Create a new socket
  Socket(int domain, int type, int protocol);

  // Take ownership of existing socket descriptor
  explicit Socket(int fd);

  // Destructor closes socket
  ~Socket();

  // Prevent copying
  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;

  // Allow moving
  Socket(Socket&& other) noexcept;
  Socket& operator=(Socket&& other) noexcept;

  // Get socket descriptor
  int get() const;
};