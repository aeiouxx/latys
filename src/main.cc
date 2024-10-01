#include <cstdlib>
#include <iostream>

#include "config/config.h"
#include "version.h"

int main(int argc, char *argv[]) {
  using namespace latys::config;
  Config config;
  std::cout << "Version: " << latys::version::kFullVersion << std::endl;
  if (!TryLoadConfig("config.yaml", config)) {
    // log + fallback to default;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
