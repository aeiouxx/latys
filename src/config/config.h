#ifndef LATYS_CONFIG_CONFIG_H
#define LATYS_CONFIG_CONFIG_H

#include <yaml-cpp/yaml.h>

#include <string>

// todo: Config is incredibly simplified, address representation should be
// improved to be platform independent
namespace latys::config {
struct NetworkConfig {
  std::string src_ip;
  uint16_t src_port;

  std::string dst_ip;
  uint16_t dst_port;
};
struct InterfaceConfig {
  std::string name;
  uint16_t mtu;
};
struct Config {
  NetworkConfig network;
  InterfaceConfig interface;
};

static bool TryLoadConfig(const std::string &path, Config &config) {
  try {
    YAML::Node root = YAML::LoadFile(path);
    config.network.src_ip = root["network"]["src_ip"].as<std::string>();
    config.network.src_port = root["network"]["src_port"].as<uint16_t>();
    config.network.dst_ip = root["network"]["dst_ip"].as<std::string>();
    config.network.dst_port = root["network"]["dst_port"].as<uint16_t>();

    config.interface.name = root["interface"]["name"].as<std::string>();
    config.interface.mtu = root["interface"]["mtu"].as<uint16_t>();
    return true;
  } catch (const YAML::BadFile &e) {
    return false;
  }
}
}  // namespace latys::config
#endif
