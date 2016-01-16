#include "utility.h"

#include <string>
#include <iostream>

namespace utility {

std::string JoinString(const std::vector<std::string>& strings,
                       char delimiter) {
  if (strings.empty())
    return {};

  std::string joined;
  for (size_t i = 0; i < strings.size() - 1; ++i) {
    joined.append(strings[i]);
    if (delimiter != '\x0')
      joined.append(&delimiter, sizeof(delimiter));
  }

  joined.append(strings.back());

  return joined;
}

}  // namespace utility
