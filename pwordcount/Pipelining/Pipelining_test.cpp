#include <iostream>
#include "gtest/gtest.h"
extern "C" {
#include "Pipelining.h"
}

using namespace std;


TEST(Pipelining, DoesAssertWork){
  ASSERT_TRUE(1 == 1);
}


TEST(Pipelining, PipeliningReturnsInt)
{
  char *file;
  char file_path[] = PIPELINING_DIR;
  file = file_path;
  testing::internal::CaptureStdout();
  ASSERT_EQ(typeid(pipelining(file)), typeid(int));
  std::string output = testing::internal::GetCapturedStdout();
}


TEST(Pipelining, PipeliningReturnsCorrectInt)
{
  char *file;
  char file_path[] = PIPELINING_DIR;
  file = file_path;
  testing::internal::CaptureStdout();
  ASSERT_EQ(pipelining(file), 0);
  std::string output = testing::internal::GetCapturedStdout();
}


int main(int argc, char **argv) {

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
