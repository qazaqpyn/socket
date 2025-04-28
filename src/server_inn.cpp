#include <netinet/in.h>
#include <sys/socket.h>

#include <iostream>
#include <string_view>

#include "include/server.hpp"
#include "socket.hpp"

int Server::init(int port) {
  sockaddr_in server_address{};
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = INADDR_ANY;

  if (::bind(server_socket.get(),
             reinterpret_cast<struct sockaddr *>(&server_address),
             sizeof(server_addr)) < 0) {
    return -1;
  }

  if (::listen(server_socket.get(), 5) < 0) {
    return -2;
  }

  std::cout << "Server listening\n";

  return 1;
}

int Server::connect_client() {
  int client_fd = ::accept(server_socket.get(), nullptr, nullptr);
  if (client_fd < 0) {
    return -1;
  }

  client_socket.emplace(client_fd);

  return 1;
}

std::string Server::get_message() {
  std::string message;
  message.resize(1024);
  auto bytes_read =
      recv(client_socket->get(), message.data(), message.size() - 1, 0);

  if (bytes_read < 0) {
    throw std::system_error(errno, std::system_category(), "receive failed");
  } else if (bytes_read == 0) {
    std::cout << "clients disconnected before sending data\n";
    return "";
  } else {
    // ensure null termination
    message[bytes_read] = '\0';
    // shrink to fit actual data;
    message.resize(bytes_read);
    std::cout << "Message from client: " << message.data() << '\n';

    return message;
  }
}
