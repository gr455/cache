#include <bits/stdc++.h>
#include "../include/cache.h"
#include "../helper.h"
#define ADDR_SIZE 32

Cache::Cache(std::string type, size_t blocks, size_t block_size) : blocks(blocks), block_size(block_size) {}
Cache::~Cache(){}

size_t Cache::get_b_count(){ return this->blocks; }
size_t Cache::get_b_size(){ return this->block_size; }
char * Cache::get_type(){ return this->type; }

inline size_t Cache::index_bit_count(){
	return (size_t)ceil(log(this->blocks)/log(2));
}

inline size_t Cache::offset_bit_count(){
	return (size_t)ceil(log(this->block_size)/log(2));
}

inline size_t Cache::tag_bit_count(){
	return ADDR_SIZE - this->offset_bit_count() - this->index_bit_count();
}

std::string Cache::cache_tag(std::string addr){
	size_t bits = this->index_bit_count();
	size_t offset_bits = this->offset_bit_count();
	return addr.substr(1, this->tag_bit_count());
}

unsigned int Cache::address_index(std::string addr){
	size_t bits = this->index_bit_count();
	size_t offset_bits = this->offset_bit_count();
	std::string t = addr.substr(ADDR_SIZE - bits - offset_bits , this->index_bit_count());
	// std::cout << t << std::endl;
	return bintoi(t, bits);
}

// 00011111111111 1111111111010100 00

std::string Cache::address_tag(std::string addr){
	size_t bits = this->index_bit_count();
	size_t offset_bits = this->offset_bit_count();
	return addr.substr(0, this->tag_bit_count());
}

unsigned int Cache::address_bit_offset(std::string addr){
	size_t offset_bits = this->offset_bit_count();
	return bintoi(addr.substr(ADDR_SIZE - offset_bits, ADDR_SIZE - 1), offset_bits);
}