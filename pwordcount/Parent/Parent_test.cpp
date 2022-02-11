#include <iostream>
#include "gtest/gtest.h"
extern "C" {
#include "Parent.h"
}

using namespace std;


TEST(Parent, DoesAssertWork)
{
  ASSERT_TRUE(1 == 1);
}


struct ParentTest : public testing::Test
{
  char *file_name;
  int to_pipe[2];
  int from_pipe[2];
  char write_msg[MAX_BUFFER_SIZE];
  char read_msg[MAX_BUFFER_SIZE];
  pid_t pid;
  void SetUp()
  {
    static char file_path[] = PARENT_DIR;
    file_name = file_path;
    if (pipe(to_pipe) == -1) 
    {
      fprintf(stderr, "To Pipe creation failed");
    }
    if (pipe(from_pipe) == -1) 
    {
      fprintf(stderr, "From Pipe creation failed");
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Fork creation failed");
    }
  }
  void TearDown() {}
};

TEST_F(ParentTest, parentReturnsInt)
{
  if (pid == 0)
  {
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    char message[] = "259";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(typeid(parent(file_name, to_pipe, from_pipe, write_msg, read_msg)), typeid(int));
    std::string output = testing::internal::GetCapturedStdout();
  }
}

TEST_F(ParentTest, parentReturnsExpectedInt)
{
  if (pid == 0)
  {
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    char message[] = "259";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(parent(file_name, to_pipe, from_pipe, write_msg, read_msg), 0);
    std::string output = testing::internal::GetCapturedStdout();
  }
}

TEST_F(ParentTest, parentOutputsExpectedString)
{
  if (pid == 0)
  {
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    char message[] = "259";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
  }
  else
  {
    std::ostringstream expected;
    expected << "Process 1 is reading file \""
      << PARENT_DIR << "\" now...\n"
      << "Process 1 starts sending data to Process 2...\n"
      << "Process 1: The total number of words is 259\n";
    testing::internal::CaptureStdout();
    parent(file_name, to_pipe, from_pipe, write_msg, read_msg);
    std::string actual = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(actual.c_str(), expected.str().c_str());
  }
}


struct ParentSendDataTest : public testing::Test
{
  char *file_name;
  FILE *input_file;
  int to_pipe[2];
  char write_msg[MAX_BUFFER_SIZE];
  pid_t pid;
  void SetUp()
  {
    static char file_path[] = PARENT_DIR;
    file_name = file_path;
    input_file = fopen(file_name, "r");
    if (pipe(to_pipe) == -1) 
    {
      fprintf(stderr, "To Pipe creation failed");
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Fork creation failed");
    }
  }
  void TearDown() {}
};

TEST_F(ParentSendDataTest, parentOutputsExpectedString)
{
  if (pid == 0)
  {
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
  }
  else
  {
    std::ostringstream expected;
    expected << "Process 1 starts sending data to Process 2...\n";
    testing::internal::CaptureStdout();
    sendDataToChild(input_file, to_pipe, write_msg);
    std::string actual = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(actual.c_str(), expected.str().c_str());
  }
}


struct ParentReadDataTest : public testing::Test
{
  char *file_name;
  int to_pipe[2];
  int from_pipe[2];
  char write_msg[MAX_BUFFER_SIZE];
  char read_msg[MAX_BUFFER_SIZE];
  pid_t pid;
  void SetUp()
  {
    static char file_path[] = PARENT_DIR;
    file_name = file_path;
    if (pipe(to_pipe) == -1) 
    {
      fprintf(stderr, "To Pipe creation failed");
    }
    if (pipe(from_pipe) == -1) 
    {
      fprintf(stderr, "From Pipe creation failed");
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Fork creation failed");
    }
  }
  void TearDown() {}
};

TEST_F(ParentReadDataTest, parentOutputsExpectedString)
{
  if (pid == 0)
  {
    char message[] = "259";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
  }
  else
  {
    std::ostringstream expected;
    expected << "Process 1: The total number of words is 259\n";
    testing::internal::CaptureStdout();
    readDataFromChild(from_pipe, read_msg);
    std::string actual = testing::internal::GetCapturedStdout();
    ASSERT_STREQ(actual.c_str(), expected.str().c_str());
  }
}


int main(int argc, char **argv)
{

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
