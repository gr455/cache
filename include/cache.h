#ifndef CACHE_H
#define CACHE_H

#include <bits/stdc++.h>

/*
	CACHE

	Interface for the base class Cache

	Declares common features for all cache types
*/
class Cache {
private:
	char * type; // cache type
	size_t blocks; // number of blocks in the cache
	size_t block_size; // size of each block

public:
	Cache(std::string, size_t, size_t);
	~Cache();

	size_t get_b_count();
	size_t get_b_size();
	char * get_type();

	/* Seperators for index, offset and tag from byte address */
	size_t index_bit_count();
	size_t offset_bit_count();
	size_t tag_bit_count();
	std::string cache_tag(std::string);
	unsigned int address_index(std::string);
	std::string address_tag(std::string);
	unsigned int address_bit_offset(std::string);
};

#endif