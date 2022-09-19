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
	KeyT nothing;

public:

	perf_alg_t(int cap, std::vector<KeyT> &input, KeyT noth) : capacity(cap), hits(0), nothing(noth) {
		assert(cap > 0);
		requestscount = input.size();
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
			return requestscount;
		return q.front();
	}

	void update(KeyT key) {
		hashmap[key].pop();
		if (set.find(key) != set.end()) {
			++hits;
			return;
		}
		if (isfull()) {
			KeyT max = nothing, el;
			int imax = -1, iit;
			for (auto it = set.begin(); it != set.end(); ++it) {
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

	void print() const {
		std::cout << "SET: ";
		for (auto it = set.begin(); it != set.end(); ++it)
			std::cout << *it << "(" << nextplace(*it) << ")" << " ";
		std::cout << "\n";
	}
};

} //end of cache namespace