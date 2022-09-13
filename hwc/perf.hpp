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
	KeyT nothing;
	struct pair_t {
		int ind;
		KeyT key;

		pair_t(int i, KeyT k) : ind(i), key(k) {}
		void equal(struct pair_t &p) {
			this->ind = p.ind;
			this->key = p.key;
		}
		bool less(struct pair_t p) {
			return (this->ind) < (p.ind);
		}
	};
	struct pair_t first, second; 

	perf_alg_t(int cap, std::vector<KeyT> &input, KeyT noth) : capacity(cap), hits(0), first(0, noth), second(0, noth), nothing(noth) {
		assert(cap > 1);
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
		int ind = nextplace(key);
		struct pair_t pair(ind, key); 
		if (isfull()) {
			set.erase(first.key);
			set.insert(key);
			if (second.less(pair))
				first.equal(pair);
			else {
				first.equal(second);
				second.equal(first);
			}
			return;
		}
		set.insert(key);
		if (first.key == nothing)
			first.equal(pair);
		else {
			if (second.key == nothing) {
				if (first.less(pair)) {
					second.equal(first);
					first.equal(pair);
				}
				else
					second.equal(pair);
			}
			if (first.less(pair)) {
				second.equal(first);
				first.equal(pair);
			} 
			else 
				if (second.less(pair))
					second.equal(pair);
		}
	}

	int hitscount() const {
		return hits;
	}
};

} //end of cache namespace