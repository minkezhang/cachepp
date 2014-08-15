#ifndef LRUCACHE_TEMPLATE
#define LRUCACHE_TEMPLATE

#include <memory>
#include <vector>

#include "libs/cachepp/cacheinterface.h"
#include "libs/cachepp/globals.h"
#include "libs/exceptionpp/exception.h"

#include "src/lru.h"

template <typename T> LRUCache<T>::LRUCache(cachepp::identifier size) : cachepp::CacheInterface<std::vector<std::shared_ptr<T>>, LRUCacheData, T>::CacheInterface(size, false) {}
template <typename T> size_t LRUCache<T>::heuristic(const std::shared_ptr<T>& arg) { throw(exceptionpp::NotImplemented("LRUCache::heuristic")); }
template <typename T> void LRUCache<T>::release(const std::shared_ptr<T>& arg) { throw(exceptionpp::NotImplemented("LRUCache::release")); }

template <typename T> std::shared_ptr<T> LRUCache<T>::select() { return(this->cache.at(0)); }

template <typename T> void LRUCache<T>::remove(const std::shared_ptr<T>& arg) {
    for(size_t i = 0; i < this->cache.size(); ++i) {
        if(this->cache.at(i) == arg) {
            this->cache.at(i)->unload();
            this->cache.erase(this->cache.begin() + i);
            return;
        }
    }
}

template <typename T> void LRUCache<T>::clear() {
    while(this->cache.size() != 0) {
        this->remove(this->cache.at(0));
    }
}

template <typename T> bool LRUCache<T>::in(const std::shared_ptr<T>& arg) {
    return(arg->get_is_loaded());
}

template <typename T> void LRUCache<T>::access(const std::shared_ptr<T>& arg, LRUCacheData aux) {
    for(size_t i = 0; i < this->cache.size(); ++i) {
        if(this->cache.at(i) == arg) {
            this->cache.erase(this->cache.begin() + i);
            break;
        }
    }
    this->cache.push_back(arg);
}

template <typename T> void LRUCache<T>::allocate(const std::shared_ptr<T>& arg) {
    if(this->cache.size() > this->get_size()) {
        this->remove(this->select());
    }
    arg->load();
    this->cache.push_back(arg);
}

template <typename T> void LRUCache<T>::acquire(const std::shared_ptr<T>& arg, LRUCacheData aux) {
    this->n_acquire++;
    if(!this->in(arg)) {
        this->n_miss++;
        this->allocate(arg);
    }
}

#endif
