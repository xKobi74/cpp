#pragma once

#include <vector>
#include <assert.h>
#include <cstdio>

namespace cache {

template <typename DataT, typename KeyT> struct cache_t {
	int capacity;
	using VectorIt = typename std::vector<DataT>::iterator;
    using constVectorIt = typename std::vector<DataT>::const_iterator;
	std::vector<DataT> vector;
	typedef DataT (*getfile_t)(KeyT);
	getfile_t getfile;

	cache_t (int cap, getfile_t gf) : capacity(cap), getfile(gf) {}

	bool isfull() const {
		return vector.size() == capacity;
	}

	void print() const {
		std::cout << "Cache: ";
		for(constVectorIt it = vector.begin(); it != vector.end(); ++it) 
			std::cout << *it;
		std::cout << "\n";
	}

	int add_new_el(KeyT key) {
		assert(isfull() == false);
		vector.push_back(getfile(key));
		return vector.size() - 1;
	}

	void rewrite_el(KeyT key, int ind) {
		assert(ind < vector.size());
		vector[ind] = getfile(key);
	} 

	DataT const *get_data_ptr(int ind) const {
		return &(*(vector.begin() + ind));
	}
};

} //end of namespace cache