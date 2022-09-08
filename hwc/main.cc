#include "qq.hpp"

int getfile(int key) {
    return key;
}

int main() {
    cache::qq_t<int, int> qq(10, -1, getfile);
    qq.print();
    return 0;
}