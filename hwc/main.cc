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
    
    #if 0
    if (flqq) cache::qq_t<int, int> qq(incap, lrucap, outcap, -1, getfile);
    if (flperf) cache::perf_alg_t<int> perf(cachesize, &in);
    #endif

    cache::qq_t<int, int> qq(incap, lrucap, outcap, -1, getfile);
    cache::perf_alg_t<int> perf(cachesize, in, -1);
    
    for (auto it = in.begin(); it != in.end(); ++it) {
        if (flqq) qq.update(*it);
        if (flperf) perf.update(*it);
    }
    
    if (flqq) std::cout << qq.hitscount() << " ";
    if (flperf) std::cout << perf.hitscount();
    std::cout << "\n";
    return 0;
}