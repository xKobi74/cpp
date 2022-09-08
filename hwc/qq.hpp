#pragma once

#include <unordered_map>
#include <assert.h>
#include <cstdio>

#include  "cache.hpp"
#include  "fifo.hpp"
#include  "lru.hpp"

namespace cache {

template <typename DataT, typename KeyT> struct qq_t {
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
    
    qq_t(int cap, int noth, getfile_t gf) : cache(cap, gf), in(cap - (cap  * 3 + 9) / 10, noth, false), out(2 * cap, noth, true), lru((cap  * 3 + 9) / 10, noth) {
        assert(cap > 1);
        nothing = noth;
    }

    void print() {
        printf("------QQ------\n");
        in.print();
        out.print();
        lru.print();
        printf("--------------\n");
    }

};

} //end of namespace cache
