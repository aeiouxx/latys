#ifndef LATYS_NETWORKING_VIRTUAL_INTERFACE_H
#define LATYS_NETWORKING_VIRTUAL_INTERFACE_H
#include <cstdint>
#include <string>

#include "packet.h"
namespace latys::networking {
struct VirtualInterface {
 public:
  VirtualInterface() = default;
  ~VirtualInterface() = default;

  bool initialize(const std::string &name, uint16_t mtu);
  void shutdown();

  bool read(Packet &packet);
  bool write(const Packet &packet);

 private:
  struct Impl;
  Impl *impl_{nullptr};
};
}  // namespace latys::networking
#endif
