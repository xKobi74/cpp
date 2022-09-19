#pragma once 

#include <list>
#include <unordered_map>
#include <assert.h>
#include <iostream>

namespace cache {

template <typename KeyT> class fifo_alg_t {
	int capacity;
	KeyT nothing;
	using ListIt = typename std::list<KeyT>::iterator;
    using constListIt = typename std::list<KeyT>::const_iterator;
	std::list<KeyT> list;
	std::unordered_map<KeyT, ListIt> hashmap;
	bool sdfl; //selective delete flag

public:

	fifo_alg_t(int cap, KeyT noth, bool fl = false) : capacity(cap), nothing(noth), sdfl(fl) {}

	void print() const {
		std::cout << "FIFO: ";
		for (constListIt it = list.begin(); it != list.end(); ++it)
			std::cout << *it << " ";
		std::cout << "\n";
	}

	bool isfull() const {
		return list.size() == capacity;
	}

	ListIt add_new_el(KeyT key) {
		list.push_front(key);
		if (sdfl)
			hashmap[key] = list.begin();
		return list.begin();
	}

	void delete_el(KeyT key) {
		assert(sdfl == true);
		auto ptr = hashmap.find(key);
		assert(ptr != hashmap.end());
		list.erase(ptr->second);
		hashmap.erase(key);
	}

	KeyT update(KeyT key) {
		if (key == nothing)
			return nothing;
		assert(hashmap.find(key) == hashmap.end());
		if (isfull()) {
			KeyT extrael = list.back();
			list.pop_back();
			hashmap.erase(extrael);
			add_new_el(key);
			return extrael;
		}
		add_new_el(key);
		return nothing;
	}

};

} //end of namespace cache