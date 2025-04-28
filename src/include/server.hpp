//: Server.hpp
#include <netinet/in.h>

#include <optional>

#include "socket.hpp"
class Server {
 private:
  sockaddr_in server_addr;
  Socket server_socket;
  std::optional<Socket> client_socket;

 public:
  Server(Socket&& socket) : server_socket(std::move(socket)) {}
  int init(int port);
  int connect_client();
  std::string get_message();
};