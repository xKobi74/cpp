#pragma once

#include <unordered_map>
#include <assert.h>
#include <iostream>

#include  "cache.hpp"
#include  "fifo.hpp"
#include  "lru.hpp"

namespace cache {

template <typename DataT, typename KeyT> class qq_t {
    int capacity;
    KeyT nothing;
    enum states_t {IN, OUT, LRU};
    struct info_t {
        states_t state;
        int index;
    };
    std::unordered_map<KeyT, info_t> hashmap;
    typedef DataT (*getfile_t)(KeyT);
    fifo_alg_t<KeyT> in;
    fifo_alg_t<KeyT> out;
    lru_alg_t<KeyT> lru;
    cache_t<DataT, KeyT> cache;
    int hits;

public:
    qq_t(int incap, int lrucap, int outcap, int noth, getfile_t gf) : cache(incap + lrucap, gf), in(incap, noth, false), out(outcap, noth, true), lru(lrucap, noth) {
        assert(cap > 1);
        nothing = noth;
        hits = 0;
    }

    void print() const {
        std::cout << "------QQ------\n";
        in.print();
        out.print();
        lru.print();
        std::cout << "--------------\n";
    }

    DataT const *update(KeyT key) {
        auto ptr = hashmap.find(key);
        KeyT extrael;
        int ind;
        if (ptr == hashmap.end()) {
            extrael = in.update(key);
            if (extrael == nothing)
                ind = cache.add_new_el(key);
            else {
                ind = hashmap[extrael].index;
                hashmap[extrael].state = OUT;
                cache.rewrite_el(key, ind);
                KeyT newextrael = out.update(extrael);
                if (newextrael != nothing)
                    hashmap.erase(newextrael);
            }
            hashmap[key] = info_t {IN, ind};
            return cache.get_data_ptr(ind);
        }
        //else
        info_t info = ptr->second;
        if (info.state == IN) {
            ++hits;
            return cache.get_data_ptr(info.index);
        }
        if (info.state == OUT) {
            out.delete_el(key);
            extrael = lru.update(key);
            if (extrael == nothing)
                ind = cache.add_new_el(key);
            if (extrael != nothing) {
                ind = hashmap[extrael].index;
                hashmap.erase(extrael);
                cache.rewrite_el(key, ind);
            }
            hashmap[key] = info_t {LRU, ind};
            return cache.get_data_ptr(ind);
        }
        // if (info.state == LRU)
        ++hits;
        lru.update(key);
        return cache.get_data_ptr(info.index);
    }
    int hitscount() const {
        return hits;
    }
};

} //end of namespace cache
