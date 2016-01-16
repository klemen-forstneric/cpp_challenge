#include "gtest/gtest.h"

#include "utility.h"

namespace {

constexpr char kSeparator = ';';

}  // namespace

TEST(UtilityTest, JoiningEmptyVectorGivesEmptyString) {
  std::vector<std::string> empty;
  std::string output = utility::JoinString(empty, kSeparator);

  EXPECT_TRUE(output.empty());
}

TEST(UtilityTest, JoiningOneStringGivesTheSameString) {
  std::string expected_string = "prvi";
  std::vector<std::string> strings{expected_string};

  std::string output = utility::JoinString(strings, kSeparator);
  EXPECT_EQ(expected_string, output);
}

TEST(UtilityTest, JoiningStringsDoesntAddSeparatorAtEnd) {
  std::vector<std::string> strings{"prvi", "drugi", "tretji"};
  std::string output = utility::JoinString(strings, kSeparator);

  EXPECT_NE(kSeparator, output.back());
}

TEST(UtilityTest, JoiningStringsWithoutSeparatorShouldAppendThem) {
  std::vector<std::string> strings{"prvi", "drugi", "tretji"};
  std::string output = utility::JoinString(strings);

  EXPECT_EQ("prvidrugitretji", output);
}
