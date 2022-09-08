#include <cstdio>

#include "qq.hpp"

int getfile(int key) {
    return key;
}

int main() {
    cache::qq_t<int, int> qq(10, -1, getfile);
    qq.print();
    for(int i = 0; i < 10; ++i) {
        printf("%d\n", *(qq.update(i)));
        qq.print();
    }
    printf("%d\n", *(qq.update(7)));
    qq.print();
    printf("%d\n", *(qq.update(1)));
    qq.print();
    printf("%d\n", *(qq.update(1)));
    qq.print();
    for(int i = 10; i < 30; ++i) {
        printf("%d\n", *(qq.update(i)));
        qq.print();
    }
    for(int i = 10; i < 20; ++i) {
        printf("%d\n", *(qq.update(i)));
        qq.print();
    }
    printf("%d\n", *(qq.update(18)));
    qq.print();
    printf("%d\n", *(qq.update(18)));
    qq.print();
    printf("%d\n", *(qq.update(16)));
    qq.print();

    printf("Hits: %d\n", qq.hitscount());
    return 0;
}