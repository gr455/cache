#include "../helper.h"

unsigned int bintoi(std::string bin, size_t bits){
	unsigned int dec = 0;
	for(int i = 0; i < bits; i++) dec = dec * 2 + (bin[i] - '0');
	// std::cout << bin << std::endl;
	return dec;
}