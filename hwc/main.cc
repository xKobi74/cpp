#include <cstdio>

#include "qq.hpp"
#include "perf.hpp"

int getfile(int key) {
    return key;
}

void input(int &size, std::vector<int> &m) {
    int n, x;
    std::cin >> size;
    std::cin >> n; 
    assert(n > 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        m.push_back(x);
    }
}

/*
To run the perfect caching algorithm, use the command line argument "0 1", 
for qq+perfect use "1 1" 
and "1 0" or ""(nothing) for 2q
*/

int main(int argc, char *argv[], char *envp[]) {
    bool flqq = true, flperf = false;
    if (argc == 3) {
        flqq = (*argv[1]) == '1';
        flperf = (*argv[2]) == '1';
    }

    int cachesize;
    std::vector<int> in;
    input(cachesize, in);
    if (cachesize < 2)
        cachesize = 2;
    int lrucap = (cachesize  * 3 + 9) / 10;
    int incap = cachesize - lrucap;
    int outcap = 2 * cachesize;
    
    int nothing = -1; // any unavailable value of key
    cache::qq_t<int, int> qq(incap, lrucap, outcap, nothing, getfile);
    cache::perf_alg_t<int> perf(cachesize, in, nothing);
    
    int q1 = qq.hitscount(), p1 = perf.hitscount(), q2, p2, dq, dp;
    for (auto it = in.begin(); it != in.end(); ++it) {
        if (flqq) qq.update(*it);
        if (flperf) perf.update(*it);
        #if 0
        q2 = qq.hitscount(), p2 = perf.hitscount();
        dq = q2 - q1;
        dp = p2 - p1;
        p1 = p2;
        q1 = q2;
        if (1) {
            std::cout << *it << ": " << dq << " " << dp << "\n";
        }
        #endif
    }
    if (flqq) std::cout << qq.hitscount() << " ";
    if (flperf) std::cout << perf.hitscount();
    std::cout << "\n";
    return 0;
}