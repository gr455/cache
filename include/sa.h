#ifndef SA_H
#define SA_H
#define ADDR_SIZE 32

#include <bits/stdc++.h>
#include "cache.h"

/*	
	N-WAY SET ASSOCIATIVE CACHE
	
	Interface for the Set Associative Cache

	The cache block:-
	{ at index <index> }: <1 bit valid><tag>, <1 bit valid><tag> ...
*/
class SetAssociative : public Cache {
private:
	std::string ** mem; // only binary to be stored in the mem
	int ** eviction_table; // stores a priority queue of indices based on recent usage
	size_t ways; // number of ways
 
 	// returns the way index to be evicted based on least recent usage
	int cache_evict_way(std::string);

public:

	SetAssociative(std::string ** mem, size_t, size_t, size_t, int **);
	~SetAssociative();

	bool assert_cache_hit(std::string); // returns hit or miss
	bool store(std::string);
	bool load(std::string);
	bool is_valid(std::string, size_t); // checks valid bit
	void write_to_cache(std::string); // writes address to cache

};

#endif