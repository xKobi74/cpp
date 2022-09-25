#include <fstream>
#include <gtest/gtest.h>
#include "qq.hpp"
#include "perf.hpp"

int getfile(int key) {
    return key;
}

void readfile(const char *file, int &size, std::vector<int> &m) {
    std::ifstream fin;
    fin.open(file);
    ASSERT_TRUE(fin.is_open());
    int n, x;
    fin >> size;
    fin >> n; 
    ASSERT_GT(size, 1);
    for (int i = 0; i < n; ++i) {
        fin >> x;
        m.push_back(x);
    } 
}

int qq_run(const char *file) {
	int cachesize;
    std::vector<int> in;
    readfile(file, cachesize, in);
    int lrucap = (cachesize  * 3 + 9) / 10;
    int incap = cachesize - lrucap;
    int outcap = 2 * cachesize;
    
    int nothing = -10000000; // any unavailable value of key
    cache::qq_t<int, int> qq(incap, lrucap, outcap, nothing, getfile);
    
    for (auto it = in.begin(); it != in.end(); ++it)
        qq.update(*it);
 
    return qq.hitscount();
}

int perf_run(const char *file) {
	int cachesize;
    std::vector<int> in;
    readfile(file, cachesize, in);
    
    int nothing = -1; // any unavailable value of key
    cache::perf_alg_t<int> perf(cachesize, in, nothing);
    
    for (auto it = in.begin(); it != in.end(); ++it)
        perf.update(*it);
    
    return perf.hitscount();
}


TEST(QQ, OneFile) {
  ASSERT_EQ(qq_run("../test/1.txt"), 9);
}

TEST(PERF, OneFile) {
  ASSERT_EQ(perf_run("../test/1.txt"), 9);
}

TEST(QQ, SmallCache) {
  ASSERT_EQ(qq_run("../test/2.txt"), 5);
}

TEST(PERF, SmallCache) {
  ASSERT_EQ(perf_run("../test/2.txt"), 7);
}

TEST(QQ, NoRequests) {
  ASSERT_EQ(qq_run("../test/3.txt"), 0);
}

TEST(PERF, NoRequests) {
  ASSERT_EQ(perf_run("../test/3.txt"), 0);
}

TEST(QQ, AllQQifs) {
  ASSERT_EQ(qq_run("../test/4.txt"), 4);
}

TEST(PERF, AllQQifs) {
  ASSERT_EQ(perf_run("../test/4.txt"), 16);
}

TEST(QQ, BigTestWithNegativeNumbers) {
  EXPECT_EQ(qq_run("../test/5.txt"), 19);
}

TEST(PERF, BigTestWithNegativeNumbers) {
  EXPECT_EQ(perf_run("../test/5.txt"), 107);
}

TEST(QQ, FewFiles) {
  ASSERT_EQ(qq_run("../test/6.txt"), 1);
}

TEST(PERF, FewFiles) {
  ASSERT_EQ(perf_run("../test/6.txt"), 1);
}

TEST(QQ, ManyFiles) {
  EXPECT_EQ(qq_run("../test/7.txt"), 107874);
}

TEST(PERF, ManyFiles) {
  EXPECT_EQ(perf_run("../test/7.txt"), 113501);
}

TEST(QQ, CycleRequests) {
  EXPECT_EQ(qq_run("../test/8.txt"), 685);
}

TEST(PERF, CycleRequests) {
  EXPECT_EQ(perf_run("../test/8.txt"), 810);
}

TEST(PERF, SimpleTest) {
  EXPECT_EQ(perf_run("../test/9.txt"), 7);
}



int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}