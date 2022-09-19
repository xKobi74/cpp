#pragma once

#include <queue>
#include <unordered_map>
#include <set>
#include <cstdio>
#include <assert.h>

namespace cache {

template <typename KeyT> class perf_alg_t {
	int capacity, requestscount;
	std::set<KeyT> set;
	std::unordered_map<KeyT, std::queue<KeyT>> hashmap;
	int hits;

public:

	perf_alg_t(int cap, std::vector<KeyT> &input) : capacity(cap), hits(0) {
		assert(cap > 0);
		int requestscount = input.size();
		int key;
		for (int i = 0; i < requestscount; ++i) {
			key = input[i];
			hashmap[key].push(i);
		}
	}

	bool isfull() const {
		return set.size() == capacity;
	}

	KeyT nextplace(KeyT const key) const {
		assert(hashmap.find(key) != hashmap.end());
		auto q = hashmap.find(key)->second;
		if (q.empty())
			return requestscount + 1;
		return q.front();
	}

	void update(KeyT key) {
		hashmap[key].pop();
		if (set.find(key) != set.end()) {
			++hits;
			return;
		}
		if (isfull()) {
			KeyT max = *(set.begin()), el;
			int imax = nextplace(max), iit;
			for (auto it = ++(set.begin()); it != set.end(); ++it) {
				el = *it;
				iit = nextplace(el);
				if (iit > imax) {
					imax = iit;
					max = el;
				}
			}
			set.erase(max);
		}
		set.insert(key);
	}

	int hitscount() const {
		return hits;
	}
};

} //end of cache namespace