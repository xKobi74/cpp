#pragma once

#include <queue>
#include <unordered_map>
#include <set>
#include <cstdio>
#include <assert.h>

namespace cache {

template <typename KeyT> class perf_alg_t {
	int capacity, requestscount;
	std::unordered_map<KeyT, std::queue<KeyT>> hashmap;
	std::set<KeyT> set;
	int hits;
	KeyT nothing;

	struct pair_t {
		KeyT key;
		int ind;
		pair_t(KeyT k, int i) : key(k), ind(i) {}
		bool operator<(const pair_t &rhs) const {
			if (ind == rhs.ind)
				return key < rhs.key;
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
		if (q.empty()) {
			return requestscount;
		}
		return q.front();
	}

	void delete_key_previos_info(KeyT key) {
		struct pair_t previospair(key, nextplace(key));
		hashmap[key].pop();
		if (set.find(key) != set.end()) {
			set.erase(key);
			setp.erase(previospair);
			++hits;
		}
	}

	void delete_extra_element() {
		if (isfull()) {
			pair_t extrapairptr = *setp.rbegin(); 
			set.erase(extrapairptr.key);
			setp.erase(extrapairptr);
		}
	}

	void add_key_info(KeyT key) {
		struct pair_t pair(key, nextplace(key));
		set.insert(key);
		setp.insert(pair);
	}

	void update(KeyT key) {
		delete_key_previos_info(key);
		delete_extra_element();
		add_key_info(key);
	}

	int hitscount() const {
		return hits;
	}

	void print() const { 
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