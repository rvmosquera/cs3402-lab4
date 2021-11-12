#include <gtest/gtest.h>

#include <strstream>

#include "Parser.hpp"

using namespace utec::compilers;

class ParamTest : public testing::TestWithParam<std::pair<std::string, std::vector<std::string>>> {
};

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

TEST_P(ParamTest, basicTest) {
  std::istrstream str(GetParam().first.c_str());

  Parser parser(str, std::cout);
  EXPECT_EQ(parser.parse(), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(SimpleTest,
                         ParamTest,
                         testing::Values(
                          std::make_pair("34 - 3 * 42", std::vector<std::string>{"-92"}) ,
                          //std::make_pair("b", std::vector<std::string>{"caracter b unexpected"}),
                          std::make_pair("(34 - 3) * 42", std::vector<std::string>{"1302"}) ,
                          std::make_pair("34 - 3 - 42", std::vector<std::string>{"-11"})
                         ));

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}