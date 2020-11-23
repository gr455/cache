#ifndef DM_H
#define DM_H
#define ADDR_SIZE 32

#include <bits/stdc++.h>
#include "cache.h"

/*	
	DIRECT MAPPED CACHE
	
	Interface for the Direct Mapped Cache

	The cache block:-
	{ at index <index> }: <1 bit valid><tag>
*/
class DirectMapped : public Cache {
private:
	std::string * mem; // only binary to be stored in the mem

public:

	DirectMapped(std::string mem[], size_t, size_t);
	~DirectMapped();

	bool assert_cache_hit(std::string); // returns hit or miss
	bool store(std::string);
	bool load(std::string);
	bool is_valid(std::string);
	void write_to_cache(std::string); // writes address to cache

};

#endif