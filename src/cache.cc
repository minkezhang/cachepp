#include "libs/exceptionpp/exception.h"

#include "src/cache.h"

/**
 * Cache
 */

cachepp::Cache::Cache(cachepp::identifier size) : size(size) {}

void cachepp::Cache::acquire(const std::shared_ptr<cachepp::Line>& arg) {
	this->l.lock();
	if(!this->in(arg)) {
		this->allocate(arg);
	}
	this->l.unlock();
}

/**
 * tests for membership in the cache
 */
bool cachepp::Cache::in(const std::shared_ptr<cachepp::Line>& arg) {
	this->l.lock();
	bool succ = false;
	try {
		this->cache.at(arg->get_identifier());
	} catch(const std::out_of_range& e) {
	}
	this->l.unlock();
	return(succ);
}

/**
 * the function which actually loads the data into the cache
 */
void cachepp::Cache::allocate(const std::shared_ptr<cachepp::Line>& arg) {
	this->l.lock();
	if(this->cache.size() > this->size) {
		this->cache.erase(this->select()->get_identifier());
	}
	this->cache.insert(std::pair<cachepp::identifier, std::shared_ptr<cachepp::Line>> (arg->get_identifier(), arg));
	this->l.unlock();
}

/**
 * selects a cache line for eviction
 *
 * default implementation may need to be overridden in derived classes
 */
std::shared_ptr<cachepp::Line> cachepp::Cache::select() {
	cachepp::identifier heuristic = 0;
	cachepp::identifier target = 0;
	for(typename std::map<cachepp::identifier, std::shared_ptr<cachepp::Line>>::iterator it = this->cache.begin(); it != this->cache.end(); ++it) {
		if(heuristic >= this->heuristic(it->second)) {
			heuristic = this->heuristic(it->second);
			target = it->first;
		}
	}
	this->cache.at(target)->unload();
	return(this->cache.at(target));
}

/**
 * takes in a cache line and returns a recommendation on if the line should be evicted
 *	return value of 0 indicates the line should NOT be evicted
 *
 * by default, not implemented and will need to be overridden
 */

/**
 * SimpleNChanceCache
 */

cachepp::SimpleNChanceCache::SimpleNChanceCache(cachepp::identifier size) : cachepp::Cache::Cache(size) {
	for(cachepp::identifier i = 0; i < this->size; ++i) {
		this->access_data.push_back(0);
	}
}

/**
 * takes in an object and returns an index to the auxiliary data
 */
cachepp::identifier cachepp::SimpleNChanceCache::hash(const std::shared_ptr<cachepp::Line>& arg) {
	return(arg->get_identifier() % this->size);
}

size_t cachepp::SimpleNChanceCache::heuristic(const std::shared_ptr<cachepp::Line>& arg) {
	return(this->access_data.at(this->hash(arg))--);
}

int main() {
	return(0);
}

