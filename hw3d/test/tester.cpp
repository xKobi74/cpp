#include <fstream>
#include <gtest/gtest.h>
#include "3dlib.hpp"

TEST(Group, Name) {
  EXPECT_EQ(1, 1);
}


int main(int argc, char **argv) {
  
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}