#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <memory>
#include <vector>

#include "libs/cachepp/cacheinterface.h"
#include "libs/cachepp/globals.h"

class LRUCacheData {};

template <typename T>
class LRUCache : public cachepp::CacheInterface<std::vector<std::shared_ptr<T>>, LRUCacheData, T> {
	public:
		LRUCache(cachepp::identifier size);

		virtual void acquire(const std::shared_ptr<T>& arg, LRUCacheData aux) final;
		virtual void release(const std::shared_ptr<T>& arg) final;
		virtual void clear() final;
		virtual void remove(const std::shared_ptr<T>& arg) final;

	private:

		virtual void access(const std::shared_ptr<T>& arg, LRUCacheData aux) final;
		virtual bool in(const std::shared_ptr<T>& arg) final;
		virtual void allocate(const std::shared_ptr<T>& arg) final;
		virtual std::shared_ptr<T> select() final;
		virtual size_t heuristic(const std::shared_ptr<T>& arg) final;
};

#include "src/templates/lru.tpp"

#endif
