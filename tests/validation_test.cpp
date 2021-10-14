#include <gtest/gtest.h>

#include <strstream>

#include "Parser.hpp"

using namespace utec::compilers;

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

TEST(SimpleTest, basicTest) {
  std::istrstream str("aaaaaab");

  Parser parser(str, std::cout);
  EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest2, basicTest2) {
  std::istrstream str("b");

  Parser parser(str, std::cout);
  EXPECT_FALSE(parser.parse());
}

TEST(SimpleTest2, basicTest4) {
  std::istrstream str("a");

  Parser parser(str, std::cout);
  EXPECT_FALSE(parser.parse());
}

TEST(SimpleTest3, basicTest3) {
  std::istrstream str("aaaaaabbbbbb");

  Parser parser(str, std::cout);
  EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest3, basicTest5) {
  std::istrstream str("ab");

  Parser parser(str, std::cout);
  EXPECT_TRUE(parser.parse());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}