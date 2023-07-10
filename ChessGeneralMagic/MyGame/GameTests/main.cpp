#include "gtest/gtest.h"


int Addition(int x, int y)
{
	return x + y +1;
}

TEST(Addition, HandlesZeroInput)
{
	EXPECT_EQ(Addition(3, 5), 8);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}