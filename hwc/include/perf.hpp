#pragma once

#include <queue>
#include <unordered_map>
#include <set>
#include <cstdio>
#include <assert.h>

namespace cache {

template <typename KeyT> class perf_alg_t {
	int capacity, requestscount;
	int maxvalue;
	std::unordered_map<KeyT, std::queue<KeyT>> hashmap;
	std::set<KeyT> set;
	int hits;
	KeyT nothing;

	struct pair_t {
		KeyT key;
		int ind;
		pair_t(KeyT k, int i) : key(k), ind(i) {}
		bool operator<(const pair_t &rhs) const {
			return ind < rhs.ind;
    	}
    	void print() {
    		std::cout << key << "(" << ind << ")" << std::endl;
    	}
	};
	std::set<pair_t> setp;


public:

	perf_alg_t(int cap, std::vector<KeyT> &input, KeyT noth) : capacity(cap), hits(0), nothing(noth) {
		assert(cap > 0);
		requestscount = input.size();
		maxvalue = requestscount;
		int key;
		for (int i = 0; i < requestscount; ++i) {
			key = input[i];
			hashmap[key].push(i);
		}
	}

	bool isfull() const {
		return set.size() == capacity;
	}

	KeyT nextplace(KeyT const key) { // only maxvalue value changes
		assert(hashmap.find(key) != hashmap.end());
		auto q = hashmap.find(key)->second;
		if (q.empty()) {
			return maxvalue++;
		}
		return q.front();
	}

	void update(KeyT key) {
		struct pair_t oldpair(key, nextplace(key));
		hashmap[key].pop();
		if (set.find(key) != set.end()) {
			set.erase(key);
			setp.erase(oldpair);
			++hits;
		}
		if (isfull()) {
			pair_t extrapair = *setp.rbegin(); 
			set.erase(extrapair.key);
			setp.erase(extrapair);
		}
		struct pair_t pair(key, nextplace(key));
		set.insert(key);
		setp.insert(pair);
	}

	int hitscount() const {
		return hits;
	}

	void print() { // only maxvalue value changes
		std::cout << "SET: ";
		for (auto it = set.begin(); it != set.end(); ++it)
			std::cout << *it << "(" << nextplace(*it) << ")" << " ";
		std::cout << "SETP: ";
		for (auto it = setp.begin(); it != setp.end(); ++it)
			std::cout << (*it).key << "(" << (*it).ind << ")" << " ";
		std::cout << "\n";
	}
};

} //end of cache namespace