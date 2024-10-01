#ifndef LATYS_NETWORKING_PACKET_H
#define LATYS_NETWORKING_PACKET_H

#include <array>
#include <cstdint>
// why tho, mtu should not be hard limited like this?
constexpr size_t kMaxPacketSize = 2048;

struct Packet {
  std::array<uint8_t, kMaxPacketSize> data;
  std::size_t length;
};
#endif
