#include <iostream>
#include "gtest/gtest.h"
extern "C" {
#include "Child.h"
}

using namespace std;

TEST(Child, DoesAssertWork)
{
  ASSERT_TRUE(1 == 1);
}


struct ChildTest : public testing::Test
{
  int to_pipe[2];
  int from_pipe[2];
  char write_msg[MAX_BUFFER_SIZE];
  char read_msg[MAX_BUFFER_SIZE];
  pid_t pid;
  void SetUp()
  {
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

TEST_F(ChildTest, childReturnsInt)
{
  if (pid > 0)
  {
    char message[] = "This is four words";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
    wait(nullptr);
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    wait(nullptr);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(typeid(child(to_pipe, from_pipe, write_msg, read_msg)), typeid(int));
    std::string output = testing::internal::GetCapturedStdout();
  }
}

TEST_F(ChildTest, childReturnsExpectedInt)
{
  if (pid > 0)
  {
    char message[] = "This is four words";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
    wait(nullptr);
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    wait(nullptr);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(child(to_pipe, from_pipe, write_msg, read_msg), 4);
    std::string output = testing::internal::GetCapturedStdout();
  }
}


struct ChildReceiveDataTest : public testing::Test
{
  int from_pipe[2];
  char read_msg[MAX_BUFFER_SIZE];
  pid_t pid;
  void SetUp()
  {
    if (pipe(from_pipe) == -1) 
    {
      fprintf(stderr, "Pipe creation failed");
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Fork creation failed");
    }
  }
  void TearDown() {}
};

TEST_F(ChildReceiveDataTest, receiveDataReturnsInt)
{
  if (pid > 0)
  {
    char message[] = "This is four words";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
    wait(nullptr);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(typeid(receiveDataFromParent(from_pipe, read_msg)), typeid(int));
    std::string output = testing::internal::GetCapturedStdout();
  }
}

TEST_F(ChildReceiveDataTest, receiveDataReturnsExpectedInt)
{
  if (pid > 0)
  {
    char message[] = "This is four words";
    for (size_t index = 0; index < strlen(message); index++)
    {
      read_msg[index] = message[index];
    }
    close(from_pipe[READ_END]);
    write(from_pipe[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(from_pipe[WRITE_END]);
    wait(nullptr);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(receiveDataFromParent(from_pipe, read_msg), 4);
    std::string output = testing::internal::GetCapturedStdout();
  }
}


struct ChildSendDataTest : public testing::Test
{
  int to_pipe[2];
  char write_msg[MAX_BUFFER_SIZE];
  pid_t pid;
  void SetUp()
  {
    if (pipe(to_pipe) == -1) 
    {
      fprintf(stderr, "Pipe creation failed");
    }
    pid = fork();
    if (pid < 0)
    {
      fprintf(stderr, "Fork creation failed");
    }
  }
  void TearDown() {}
};

TEST_F(ChildSendDataTest, sendDataReturnsCharStar)
{
  if (pid > 0)
  {
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    wait(nullptr);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(typeid(sendDataToParent(to_pipe, write_msg, 1)), typeid(char*));
    std::string output = testing::internal::GetCapturedStdout();
  }
}

TEST_F(ChildSendDataTest, sendDataReturnsExpectedCharStar)
{
  if (pid > 0)
  {
    int message_size = 0;
    close(to_pipe[WRITE_END]);
    while ((message_size = read(to_pipe[READ_END], write_msg, MAX_BUFFER_SIZE)) > 0){}
    close(to_pipe[READ_END]);
    wait(nullptr);
  }
  else
  {
    testing::internal::CaptureStdout();
    ASSERT_EQ(sendDataToParent(to_pipe, write_msg, 1), "1");
    std::string output = testing::internal::GetCapturedStdout();
  }
}


int main(int argc, char **argv)
{

  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
