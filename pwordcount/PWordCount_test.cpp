#include <iostream>
#include "gtest/gtest.h"
extern "C" {
#include "PWordCount.h"
}

using namespace std;


TEST(PWordCount, DoesAssertWork){
  ASSERT_TRUE(1 == 1);
}


struct PWordCountEmptyInputTest : public testing::Test {
  int inputCount;
  char* input[MAX_BUFFER_SIZE];
  void SetUp() {
    inputCount = 0;
  }
  void TearDown() {}
};

TEST_F(PWordCountEmptyInputTest, PWordCountReturnsInt){
  testing::internal::CaptureStdout();
  ASSERT_EQ(typeid(pWordCount(inputCount, input)), typeid(int));
  std::string output = testing::internal::GetCapturedStdout();
}

TEST_F(PWordCountEmptyInputTest, PWordCountEmptyInputReturnsZero){
  testing::internal::CaptureStdout();
  ASSERT_EQ(pWordCount(inputCount, input), 1);
  std::string output = testing::internal::GetCapturedStdout();
}


int main(int argc, char **argv) {

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
