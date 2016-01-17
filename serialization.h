#ifndef SERIALIZATION_H_
#define SERIALIZATION_H_

#include <stdint.h>

#include <vector>

namespace serialization {

uint32_t ToUint32(const uint8_t* data);
std::vector<uint8_t> FromUint32(uint32_t data);

}  // namespace serialization

#endif  // SERIALIZATION_H_
