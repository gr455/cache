#include "../include/dm.h"
#include "../helper.h"

std::string typeDM = "DirectMapped";
DirectMapped::DirectMapped(std::string mem[], size_t blocks, size_t block_size) : Cache(typeDM, blocks, block_size), mem(mem){}
DirectMapped::~DirectMapped(){
	delete[] this->mem;
}

bool DirectMapped::is_valid(std::string addr){
	return this->mem[this->Cache::address_index(addr)][0] == '1';
}

bool DirectMapped::assert_cache_hit(std::string addr){
	if(!this->DirectMapped::is_valid(addr)) return false;
	std::string block = this->mem[this->Cache::address_index(addr)];
	if(!this->Cache::cache_tag(block).compare(this->Cache::address_tag(addr))) return true;
	return false;
}

/* Writes with valid bit 1 */
void DirectMapped::write_to_cache(std::string addr){
	unsigned int index = this->Cache::address_index(addr);
	this->mem[index] = "1" + this->Cache::address_tag(addr);
	// std::cout << this->Cache::address_tag(addr) << std:: endl;
}

bool DirectMapped::load(std::string addr){
	// <Load implementation>
	bool hit = this->DirectMapped::assert_cache_hit(addr);
	if(!hit) this->DirectMapped::write_to_cache(addr);
	return hit;
}

bool DirectMapped::store(std::string addr){
	// <Store implementation>
	bool hit = this->DirectMapped::assert_cache_hit(addr);
	if(!hit) this->DirectMapped::write_to_cache(addr);
	return hit;
}
