#include "socket.h"

#if defined(PLATFORM_WINDOWS)
#include <basetsd.h>
#include <ws2tcpip.h>
typedef SSIZE_T ssize_t;
#pragma comment(lib, "Ws2_32.lib")
#elif defined(PLATFORM_LINUX)
#include <arpa/inet.h>
#include <fnctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#else
ASSERT(false, "Unsupported platform");
#endif

namespace latys::networking {
Socket::Socket() : socket_fd_(-1) {
}

Socket::~Socket() {
  Shutdown();
}

bool Socket::Initialize(const std::string &src_ip, uint16_t src_port,
                        const std::string &dst_ip, uint16_t dst_port) {
#ifdef PLATFORM_WINDOWS
  WSADATA wsa_data;
  if (int result = WSAStartup(MAKEWORD(2, 2), &wsa_data); result != 0) {
    return false;
  }
#endif

  socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_fd_ == -1) {
    return false;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(src_port);

#ifdef PLATFORM_WINDOWS
  InetPton(AF_INET, src_ip.c_str(), &addr.sin_addr);
#else
  inet_pton(AF_INET, src_ip.c_str(), &addr.sin_addr);
#endif

  if (bind(socket_fd_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) ==
      -1) {
    return false;
  }

  if (listen(socket_fd_, SOMAXCONN) == -1) {
    return false;
  }

  return true;
}

bool Socket::Connect(const std::string &dst_ip, uint16_t dst_port) {
  int clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (clientSocket == -1) {
    return false;
  }
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(dst_port);
#ifdef PLATFORM_WINDOWS
  InetPton(AF_INET, dst_ip.c_str(), &addr.sin_addr);
#else
  inet_pton(AF_INET, dst_ip.c_str(), &addr.sin_addr);
#endif

  if (connect(clientSocket, reinterpret_cast<sockaddr *>(&addr),
              sizeof(addr)) == -1) {
    return false;
  }
#ifdef PLATFORM_WINDOWS
  closesocket(socket_fd_);
#else
  close(socket_fd_);
#endif
  socket_fd_ = clientSocket;
  return true;
}

void Socket::Shutdown() {
  if (socket_fd_ < 0) {
    return;
  }
#ifdef PLATFORM_WINDOWS
  closesocket(socket_fd_);
  WSACleanup();
#else
  close(socket_fd_);
#endif
}

bool Socket::Send(const Packet &packet) {
  ssize_t sent =
      send(socket_fd_, reinterpret_cast<const char *>(packet.data.data()),
           packet.length, 0);
  return sent == static_cast<ssize_t>(packet.length);
}

bool Socket::Receive(Packet &packet) {
  ssize_t received =
      recv(socket_fd_, reinterpret_cast<char *>(packet.data.data()),
           kMaxPacketSize, 0);
  if (received <= 0) {
    return false;
  }
  packet.length = received;
  return true;
}
}  // namespace latys::networking
