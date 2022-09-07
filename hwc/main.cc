#include "lru.hpp"

int main() {
    int n;
    scanf("%d", &n);
    cache::lru_alg_t<int> lru(4, -1);
    int x;
    for(int i = 0; i < n; ++i) {
        scanf("%d", &x);
        printf("%d\n", lru.update(x));
        lru.print();
    }

    return 0;
}