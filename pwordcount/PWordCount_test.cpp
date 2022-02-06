#include <iostream>
#include "gtest/gtest.h"
extern "C" {
#include "PWordCount.h"
}

using namespace std;

struct PWordCountEmptyInputTest : public testing::Test {
  int inputCount;
  char* input[MAX_BUFFER_SIZE];
  void SetUp() {
    inputCount = 0;
  }
  void TearDown() {}
};

struct DISABLED_PWordCountOneInputFileDoesNotExistTest : public testing::Test {
  int inputCount;
  char* input[MAX_BUFFER_SIZE];
  void SetUp() {
    inputCount = 1;
    char hello[] = "Hello";
    input[0] = hello;
  }
  void TearDown() {}
};

struct DISABLED_PWordCountOneInputFileDoesExistTest : public testing::Test {
  int inputCount;
  char* input[MAX_BUFFER_SIZE];
  void SetUp() {
    inputCount = 1;
    char hello[] = "Hello";
    input[0] = hello;
  }
  void TearDown() {}
};

struct DISABLED_PWordCountTwoInputTest : public testing::Test {
  int inputCount;
  char* input[MAX_BUFFER_SIZE];
  void SetUp() {
    inputCount = 2;
    char hello[] = "Hello";
    char world[] = "World";
    input[0] = hello;
    input[1] = world;
  }
  void TearDown() {}
};

TEST(PWordCount, DoesAssertWork){
  ASSERT_TRUE(1 == 1);
}

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

TEST_F(DISABLED_PWordCountOneInputFileDoesNotExistTest, PWordCountEmptyInputReturnsZero){
  ASSERT_EQ(pWordCount(inputCount, input), 1);
}

TEST_F(DISABLED_PWordCountOneInputFileDoesExistTest, PWordCountEmptyInputReturnsZero){
  ASSERT_EQ(pWordCount(inputCount, input), 0);
}

TEST_F(DISABLED_PWordCountTwoInputTest, PWordCountEmptyInputReturnsZero){
  ASSERT_EQ(pWordCount(inputCount, input), 0);
}


int main(int argc, char **argv) {

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
