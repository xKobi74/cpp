/*
#include "lru.hpp"

int main() {
    int n;
    scanf("%d", &n);
    cache::lru_alg_t<int> lru(1, -1);
    int x;
    for(int i = 0; i < n; ++i) {
        scanf("%d", &x);
        printf("%d\n", lru.update(x));
        lru.print();
    }

    return 0;
}
*/

#include "fifo.hpp"

int main() {
    int n;
    scanf("%d", &n);
    cache::fifo_alg_t<int> lru(10, -1, true);
    int x;
    for(int i = 0; i < 10; ++i) {
        printf("%d\n", lru.update(i));
        lru.print();
    }
    for(int i = 0; i < n; ++i) {
        scanf("%d", &x);
        lru.delete_el(x);
        lru.print();
    }
    return 0;
}