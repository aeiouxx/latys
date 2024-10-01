#include "virtual-interface.h"

namespace latys::networking {

struct VirtualInterface::Impl {
#ifdef PLATFORM_WINDOWS
  WINTUN_ADAPTER_HANDLE adapter_;
  WINTUN_SESSION_HANDLE session_;
#else
  int tun_fd_{-1};
#endif
};

VirtualInterface::VirtualInterface() noexcept {
  impl_ = new Impl();
}

}  // namespace latys::networking
