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
    }
    std::unordered_map<KeyT, info_t> hashmap;
    typedef DataT (*getfile_t)(KeyT);

    2q_t(int cap, int nothing, getfile_t gf) {
        assert(cap > 1);
        nothing = noth;
        cache_t<DataT, KeyT> cache(cap, gf);
        int lrucap = (cap  * 3 + 9) / 10;
        int incap = cap - lrucap;
        int out = 2 * cap;
        fifo_alg_t<KeyT> in(incap, noth, false);
        fifo_alg_t<KeyT> out(outcap, noth, true);
        lru_alg_t<KeyT> lru(lrucap, noth);
    }

};

} //end of namespace cache
