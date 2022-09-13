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
	struct pair_t {
		int ind;
		KeyT key;

		pair_t(int i, KeyT k) : ind(i), key(k) {}
		void equal(struct pair_t &p) {
			this->ind = p.ind;
			this->key = p.key;
		}
		bool less(struct pair_t p) const {
			return (this->ind) < (p.ind);
		}
	};

	class two_ordered_pairs_t {
		KeyT nothing;
		struct pair_t first, second; 

	public:
		
		two_ordered_pairs_t(KeyT noth) : first(-1, noth), second(-1, noth), nothing(noth) {};
		KeyT update(struct pair_t &pair) {
			KeyT extrael = nothing;
			if (second.key == nothing) {
				if (first.key == nothing) 
					first.equal(pair);
				else {
					if (first.less(pair)) {
						second.equal(first);
						first.equal(pair);
					}
					else if (second.less(pair))
						second.equal(pair);
				}
			}
			else {
				extrael = second.key;
				if (first.less(pair)) {
					second.equal(first);
					first.equal(pair);
				}
				else if (second.less(pair)) {
					second.equal(pair);
				}
			}
			return extrael;
		}
	};

	class two_ordered_pairs_t lasttwo;

public:

	perf_alg_t(int cap, std::vector<KeyT> &input, KeyT noth) : capacity(cap), hits(0), lasttwo(noth), nothing(noth) {
		assert(cap > 1);
		int requestscount = input.size();
		int key;
		for (int i = 0; i < requestscount; ++i) {
			key = input[i];
			hashmap[key].push(i);
		}
	}

	KeyT nextplace(KeyT const key) const {
		assert(hashmap.find(key) != hashmap.end());
		auto q = hashmap.find(key)->second;
		if (q.empty())
			return requestscount + 1;
		return q.front();
	}

	bool isfull() const {
		return set.size() == capacity;
	}	

	void update(KeyT key) {
		hashmap[key].pop();
		if (set.find(key) != set.end()) {
			++hits;
			return;
		}
		int ind = nextplace(key);
		struct pair_t pair(ind, key);
		KeyT extrael = lasttwo.update(pair); 
		if (isfull())
			set.erase(extrael);
		set.insert(key);
	}

	int hitscount() const {
		return hits;
	}
};

} //end of cache namespace