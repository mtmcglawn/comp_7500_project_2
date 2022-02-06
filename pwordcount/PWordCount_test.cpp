#include <iostream>
#include "gtest/gtest.h"
extern "C" {
  #include "PWordCount.h"
}

using namespace std;

struct PWordCountTest : public testing::Test {
	//std::string output;
	void SetUp() {
    /*
    PWordCount();
		std::stringstream ss;
		ss << "Hello World\n"
			<< "Version: "
			<< Project_2_VERSION_MAJOR << "."
			<< Project_2_VERSION_MINOR << "."
			<< Project_2_VERSION_PATCH;
		output = ss.str();
    */
	}
	void TearDown() {}
};
	
TEST(PWordCount, DoesAssertWork){
	ASSERT_TRUE(1 == 1);
}

TEST(PWordCount, PWordCountReturnsInt){
	ASSERT_EQ(typeid(pWordCount()), typeid(int));
}

TEST(PWordCountTest, PWordCountReturnsZero){
  ASSERT_EQ(pWordCount(), 0);
}
/*
TEST_F(PWordCountTest, PWordCountPrintReturnsChar){
	ASSERT_EQ(typeid(getString()), typeid(char*));
}

TEST_F(PWordCountTest, PWordCountPrintReturnsCorrectString){
	ASSERT_STREQ(getString(), output.c_str());
}
*/


int main(int argc, char **argv) {

	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
