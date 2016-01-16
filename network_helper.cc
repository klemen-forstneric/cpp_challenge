#include "network_helper.h"

#include <string>

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace network_helper {

std::vector<std::string> GetActiveAdaptersIPs() {
  std::vector<std::string> ip_addresses;

  ifaddrs* ifaddr;
  if (getifaddrs(&ifaddr) == -1)
    return {};

  char ip_address[NI_MAXHOST];
  for (ifaddrs* ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == nullptr)
      continue;

    if (getnameinfo(ifa->ifa_addr, sizeof(sockaddr_in), ip_address, NI_MAXHOST,
                    NULL, 0, NI_NUMERICHOST) != 0) {
      return {};
    }

    if (ifa->ifa_addr->sa_family == AF_INET)
      ip_addresses.push_back(ip_address);
  }

  return ip_addresses;
}

}  // namespace network_helper
