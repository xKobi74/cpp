#pragma once

#include <list>
#include <unordered_map>
#include <assert.h>

namespace cache {

template <typename KeyT> struct lru_alg_t {
    int capacity;
    KeyT nothing;
    using ListIt = typename std::list<KeyT>::iterator;
    std::list<KeyT> list;
    std::unordered_map<KeyT, ListIt> hashmap;

    lru_alg_t(int cap, KeyT noth) : capacity(cap), nothing(noth) {}

    void print() {
        for (ListIt it = list.begin(); it != list.end(); ++it)
            printf("%d ", *it);
        printf("\n");
    }

    bool isfull() {
        return list.size() == capacity;
    }

    ListIt add_new_el(KeyT key) {
        list.push_front(key);
        hashmap[key] = list.begin();
        return hashmap[key];
    }

    KeyT update(KeyT key) {
        if (key == nothing)
            return nothing;
        auto ptr = hashmap.find(key);
        if (ptr == hashmap.end()) {
            KeyT extrael = nothing;
            if (isfull()) {
                extrael = list.back();
                list.pop_back();
                hashmap.erase(extrael);
            }
            add_new_el(key);
            hashmap[key] = list.begin();
            return extrael;
        }
        list.erase(ptr->second);
        hashmap[key] = add_new_el(key);
        return nothing;
    }
};

} //end of namespace lirs
