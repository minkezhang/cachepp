#include <iostream>

#include "libs/cachepp/simpleline.h"
#include "src/lru.h"

int main() {
	std::cout << "This is a skeletal tutorial application for the cachepp caching framework." << std::endl << std::endl \
		<< "Please see https://github.com/cripplet/cachepp/blob/master/docs/overview.md for the tutorial." << std::endl;

	std::shared_ptr<LRUCache<cachepp::SimpleLine>> c (new LRUCache<cachepp::SimpleLine>(1));
	return(0);
}
