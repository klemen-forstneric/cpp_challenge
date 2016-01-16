#include "gtest/gtest.h"

#include "serialization.h"

TEST(SerializationTest, CheckThatUint32GetsSerializedAsLittleEndian) {
  uint32_t number = 0xAABBCCDD;
  std::vector<uint8_t> serialized = serialization::FromUint32(number);

  EXPECT_EQ(4, serialized.size());

  EXPECT_EQ(0xDD, serialized[0]);
  EXPECT_EQ(0xCC, serialized[1]);
  EXPECT_EQ(0xBB, serialized[2]);
  EXPECT_EQ(0xAA, serialized[3]);
}

TEST(SerializationTest, CheckThatDataGetsDeserializedAsLittleEndian) {
  std::vector<uint8_t> data{0xDD, 0xCC, 0xBB, 0xAA};
  uint32_t deserialized = serialization::ToUint32(data.data());

  EXPECT_EQ(0xAABBCCDD, deserialized);
}
