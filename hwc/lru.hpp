#pragma once

#include <list>
#include <unordered_map>
#include <assert.h>
#include <cstdio>

namespace cache {

template <typename KeyT> class lru_alg_t {
    int capacity;
    KeyT nothing;
    using ListIt = typename std::list<KeyT>::iterator;
    using constListIt = typename std::list<KeyT>::const_iterator;
    std::list<KeyT> list;
    std::unordered_map<KeyT, ListIt> hashmap;

public:
    
    lru_alg_t(int cap, KeyT noth) : capacity(cap), nothing(noth) {}

    void print() const {
        std::cout << "LRU: ";
        for (constListIt it = list.begin(); it != list.end(); ++it)
            std::cout << *it;
        std::cout << "\n";
    }

    bool isfull() const {
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

} //end of namespace cache
