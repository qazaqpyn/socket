//: client.cpp for sending data over http

#include <netinet/in.h>

#include <iostream>
#include <string_view>

#include "include/socket.hpp"

int main() {
  try {
    Socket clientSocket(AF_INET, SOCK_STREAM, 0);

    // specify address
    sockaddr_in serverAdr{};
    serverAdr.sin_family = AF_INET;
    serverAdr.sin_port = htons(8080);
    serverAdr.sin_addr.s_addr = INADDR_ANY;

    // sending connection request
    if (connect(clientSocket.get(),
                reinterpret_cast<struct sockaddr *>(&serverAdr),
                sizeof(serverAdr)) < 0) {
      throw std::system_error(errno, std::system_category(),
                              "Connection failed");
    }
    std::cout << "Connected to server\n";

    // seding data usign string_view for efficient string handling
    std::string_view message = "Hello from client";
    auto sentBytes =
        send(clientSocket.get(), message.data(), message.size(), 0);

    if (sentBytes < 0) {
      throw std::system_error(errno, std::system_category(), "Send failed");
    }

    std::cout << "Successfully sent " << sentBytes << " bytes\n";

    // Auto closed with destructors
    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}