#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <vector>

namespace utility {

std::string JoinString(const std::vector<std::string>& strings,
                       char delimiter = '\x0');

}  // namespace utility

#endif  // UTILITY_H_
