#include <type_traits>

#include "libs/exceptionpp/exception.h"

#include "src/cache.h"

/**
 * Cache
 */

template <typename T> cachepp::Cache<T>::Cache(cachepp::identifier size) : size(size) {
	if(!std::is_base_of<cachepp::Line, T>::value) {
		throw(exceptionpp::InvalidOperation("cachepp::Cache<T>::Cache", "given typename T is not inherited from cachepp::Line"));
	}
}

template <typename T> void cachepp::Cache<T>::acquire(const std::shared_ptr<T>& arg) {
	this->l.lock();
	if(!this->in(arg)) {
		this->allocate(arg);
	}
	this->l.unlock();
}

/**
 * tests for membership in the cache
 */
template <typename T> bool cachepp::Cache<T>::in(const std::shared_ptr<T>& arg) {
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
template <typename T> void cachepp::Cache<T>::allocate(const std::shared_ptr<T>& arg) {
	this->l.lock();
	if(this->cache.size() > this->size) {
		this->cache.erase(this->select()->get_identifier());
	}
	this->cache.insert(std::pair<cachepp::identifier, std::shared_ptr<T>> (arg->get_identifier(), arg));
	this->l.unlock();
}

/**
 * selects a cache line for eviction
 *
 * default implementation may need to be overridden in derived classes
 */
template <typename T> std::shared_ptr<T> cachepp::Cache<T>::select() {
	cachepp::identifier heuristic = 0;
	cachepp::identifier target = 0;
	for(typename std::map<cachepp::identifier, std::shared_ptr<T>>::iterator it = this->cache.begin(); it != this->cache.end(); ++it) {
		if(heuristic >= this->heuristic(it->second)) {
			heuristic = this->heuristic(it->second);
			target = it->first;
		}
	}
	this->cache.at(target)->unload();
	return(this->cache.at(target));
}

/**
 * SimpleNChanceCache
 */

template <typename T> cachepp::SimpleNChanceCache<T>::SimpleNChanceCache(cachepp::identifier size) : cachepp::Cache<T>::Cache(size) {
	for(cachepp::identifier i = 0; i < this->size; ++i) {
		this->access_data.push_back(0);
	}
}

template <typename T> void cachepp::SimpleNChanceCache<T>::access(const std::shared_ptr<T>& arg) {
	this->access_data.at(this->hash(arg))++;
}

/**
 * takes in an object and returns an index to the auxiliary data
 */
template <typename T> cachepp::identifier cachepp::SimpleNChanceCache<T>::hash(const std::shared_ptr<T>& arg) {
	return(arg->get_identifier() % this->size);
}

template <typename T> size_t cachepp::SimpleNChanceCache<T>::heuristic(const std::shared_ptr<T>& arg) {
	return(this->access_data.at(this->hash(arg))--);
}
