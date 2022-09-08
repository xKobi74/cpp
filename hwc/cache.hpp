#pragma once

#include <vector>
#include <assert.h>
#include <cstdio>

namespace cache {

template <typename DataT, typename KeyT> struct cache_t {
	int capacity;
	using VectorIt = typename std::vector<DataT>::iterator;
	std::vector<DataT> vector;
	typedef DataT (*getfile_t)(KeyT);
	getfile_t getfile;

	cache_t (int cap, getfile_t gf) : capacity(cap), getfile(gf) {}

	bool isfull() const {
		return vector.size() == capacity;
	}

	void print() {
		printf("Cache: ");
		for(VectorIt it = vector.begin(); it != vector.end(); ++it) 
			printf("%d ", *it);
		printf("\n");
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

	KeyT *get_data_ptr(int ind) {
		return &*(vector.begin() + ind);
	}
};

} //end of namespace cache