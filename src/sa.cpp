#include "../include/sa.h"
#include "../helper.h"

std::string typeSA = "SetAssociative";
SetAssociative::SetAssociative(std::string ** mem, size_t blocks, size_t block_size, size_t ways, int ** eviction) : Cache(typeSA, blocks, block_size), mem(mem), ways(ways), eviction_table(eviction){
	for(unsigned int i = 0; i < this->get_b_count(); i++){
		for(unsigned int j = 0; j < this->ways; j++) this->eviction_table[i][j] = j;
	}
}
SetAssociative::~SetAssociative(){
	delete[] this->mem;
	delete[] this->eviction_table;
}

bool SetAssociative::is_valid(std::string addr, size_t way){
	return this->mem[this->Cache::address_index(addr)][way][0] == '1';
}

bool SetAssociative::assert_cache_hit(std::string addr){
	std::string * block = this->mem[this->Cache::address_index(addr)];
	/* Linear search on ways */
	for(size_t i = 0; i < this->ways; i++){
		if(!this->Cache::cache_tag(block[i]).compare(this->Cache::address_tag(addr)) && SetAssociative::is_valid(addr, i)) return true;
	}
	return false;
}

/* Implements LRU */
int SetAssociative::cache_evict_way(std::string addr){
	int ** table = this->eviction_table;
	int index = this->Cache::address_index(addr);

	int e_way = table[index][0];
	for(int i = 0; i < this->ways - 1; i++){
		table[index][i] = table[index][i+1];
	}
	table[index][this->ways - 1] = e_way;

	return e_way;
}

/* Writes with valid bit 1 */
void SetAssociative::write_to_cache(std::string addr){
	unsigned int index = this->Cache::address_index(addr);
	/* Write data to invalid block. If all blocks valid, then use LRU for eviction */
	for(size_t i = 0; i < this->ways; i++){
		if(!this->SetAssociative::is_valid(addr, i)){
			this->mem[index][i] = "1" + this->Cache::address_tag(addr);
			return;
		}
	}
	int r_way = this->SetAssociative::cache_evict_way(addr);
	
	this->mem[index][r_way] = "1" + this->Cache::address_tag(addr);
}

bool SetAssociative::load(std::string addr){
	// <Load implementation>
	bool hit = this->SetAssociative::assert_cache_hit(addr);
	if(!hit) this->SetAssociative::write_to_cache(addr);
	return hit;
}

bool SetAssociative::store(std::string addr){
	// <Store implementation>
	bool hit = this->SetAssociative::assert_cache_hit(addr);
	if(!hit) this->SetAssociative::write_to_cache(addr);
	return hit;
}

