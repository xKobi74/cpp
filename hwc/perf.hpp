#pragma once

#include <queue>
#include <unordered_map>
#include <set>
#include <cstdio>
#include <assert.h>

namespace cache {

template <typename KeyT> struct perf_alg_t {
	int capacity, requestscount;
	std::set<KeyT> set;
	std::unordered_map<KeyT, std::queue<KeyT>> hashmap;
	int hits;

	perf_alg_t(int cap, std::vector<KeyT> *inputptr) : capacity(cap), hits(0) {
		assert(cap > 0);
		auto input = *inputptr;
		requestscount = input.size();
		auto ptr = hashmap.end();
		int key;
		for (int i = 0; i < requestscount; ++i) {
			key = input[i];
			ptr = hashmap.find(key);
			if (ptr == hashmap.end()) 
				hashmap[key].push(key);
			else 
				(ptr->second).push(key);
		}
	}

	bool isfull() {
		return set.size() == capacity;
	}

	KeyT nextplace(KeyT key) {
		assert(hashmap.find(key) != hashmap.end());
		if (hashmap[key].empty())
			return requestscount + 1;
		return hashmap[key].front();
	}

	void update(KeyT key) {
		hashmap[key].pop();
		if (set.find(key) != set.end()) {
			++hits;
			return;
		}
		if (isfull()) {
			KeyT max = *(set.begin());
			for (auto it = ++(set.begin()); it != set.end(); ++it)
				if (nextplace(*it) > nextplace(max))
					max = *it;
			if (max == key) {
				++hits;
				return;
			}
			set.erase(max);
		}
		set.insert(key);
	}

	int hitscount() {
		return hits;
	}
};

} //end of cache namespace