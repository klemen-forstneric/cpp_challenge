#include "serialization.h"

#include <iostream>

namespace {

constexpr uint32_t kNumBitsInAByte = 8;

}  // namespace

namespace serialization {

uint32_t ToUint32(const uint8_t* data) {
  uint32_t deserialized = 0;

  for (size_t i = 0; i < sizeof(uint32_t); ++i)
    deserialized |= static_cast<uint32_t>(data[i]) << i * kNumBitsInAByte;

  return deserialized;
}

std::vector<uint8_t> FromUint32(uint32_t data) {
  std::vector<uint8_t> serialized;
  serialized.reserve(sizeof(data));

  for (size_t i = 0; i < sizeof(data); ++i) {
    serialized.push_back(static_cast<uint8_t>(data));
    data >>= 8;
  }

  return serialized;
}

}  // namespace serialization
