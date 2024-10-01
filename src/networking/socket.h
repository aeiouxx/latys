#ifndef LATYS_NETWORKING_SOCKET_H
#define LATYS_NETWORKING_SOCKET_H
#include <cstdint>
#include <string>

#ifdef PLATFORM_WINDOWS
#include <winsock2.h>
#endif

#include "packet.h"
// todo: async / coroutines ?
namespace latys::networking {
class Socket {
 public:
  Socket();
  ~Socket();

  bool Initialize(const std::string &src_ip, uint16_t src_port,
                  const std::string &dst_ip, uint16_t dst_port);
  bool Connect(const std::string &dst_ip, uint16_t dst_port);
  bool Send(const Packet &packet);
  bool Receive(Packet &packet);
  void Shutdown();

 private:
#ifdef PLATFORM_WINDOWS
  SOCKET socket_fd_;
#else
  int socket_fd_;
#endif
};
}  // namespace latys::networking
#endif
