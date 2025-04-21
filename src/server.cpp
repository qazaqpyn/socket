//: server.cpp for receiving data over http
#include <netinet/in.h>

#include <iostream>

#include "include/socket.hpp"

int main() {
  try {
    // // AF_INET specifies IPv4 procotocol
    // // SOCK_STREAM tells that it's TCP
    Socket serverSocket(AF_INET, SOCK_STREAM, 0);

    // specifying the address
    // sockaddr_in data type for storing socket address
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    // htons the function used to convert unsigned int from machine byte order
    // to network byte order
    serverAddress.sin_port = htons(8080);
    // inaddr_any used when we dont want to bind our socket to any particular ip
    // => listen on all available IPs
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket.get(),
             reinterpret_cast<struct sockaddr *>(&serverAddress),
             sizeof(serverAddress)) < 0) {
      throw std::system_error(errno, std::system_category(), "Binding Failed");
    }

    if (listen(serverSocket.get(), 5) < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Failed connection");
    }

    std::cout << "Server listening\n";

    int cliendFd = accept(serverSocket.get(), nullptr, nullptr);
    if (cliendFd < 0) {
      throw std::system_error(errno, std::system_category(), "Accept failed");
    }

    // create a socket for accepted connection
    Socket clientSocket(std::move(cliendFd));

    std::cout << "Client connected\n";

    // receive data
    std::array<char, 1024> buffer{};
    auto bytesRead =
        recv(clientSocket.get(), buffer.data(), buffer.size() - 1, 0);

    if (bytesRead < 0) {
      throw std::system_error(errno, std::system_category(), "receive failed");
    } else if (bytesRead == 0) {
      std::cout << "clients disconnected before sending data\n";
    } else {
      // ensure null termination
      buffer[bytesRead] = '\0';
      std::cout << "Message from client: " << buffer.data() << '\n';
    }

    return 0;
    // create socket for ec
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";

    return 1;
  }
}