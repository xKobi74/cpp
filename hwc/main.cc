#include <cstdio>

#include "qq.hpp"
#include "perf.hpp"

int getfile(int key) {
    return key;
}

void input(int *size, std::vector<int> *m) {
    int n, x;
    int k = scanf("%d", size);
    if (k != 1)
        abort();
    k = scanf("%d", &n);
    if (k != 1)
        abort();
    assert(n > 1);
    for (int i = 0; i < n; ++i) {
        k += scanf("%d", &x);
        m->push_back(x);
    }
    if (k != n + 1)
        abort();
}

int main() {
    int cachesize;
    std::vector<int> in;
    input(&cachesize, &in);
    if (cachesize < 2)
        cachesize = 2;
    int lrucap = (cachesize  * 3 + 9) / 10;
    int incap = cachesize - lrucap;
    int outcap = 2 * cachesize;
    cache::qq_t<int, int> qq(incap, lrucap, outcap, -1, getfile);
    cache::perf_alg_t<int> perf(cachesize, &in);
    
    for (auto it = in.begin(); it != in.end(); ++it) {
        qq.update(*it);
        perf.update(*it);
    }
    
    printf("QQ hits: %d\n", qq.hitscount());
    printf("Perf hits: %d\n", perf.hitscount());
    return 0;
}