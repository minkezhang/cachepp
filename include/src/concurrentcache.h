#ifndef _CACHEPP_CONCURRENTCACHE_H
#define _CACHEPP_CONCURRENTCACHE_H

#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "src/cacheinterface.h"
#include "src/globals.h"

namespace cachepp {
	/**
	 * this is a subclass of the base Cache template and is IS thread-safe
	 */
	template <typename D, typename T>
	class ConcurrentCache : public CacheInterface<std::map<identifier, std::shared_ptr<T>>, D, T> {
		public:
			ConcurrentCache(identifier size);

			/**
			 * ensures that the given arg is in the cache, and ensures that the given arg cannot be unloaded until release is called
			 */
			virtual void acquire(const std::shared_ptr<T>& arg) final;

			/**
			 * releases a hold on the cache line containing arg -- this cache line can now be evicted
			 */
			virtual void release(const std::shared_ptr<T>& arg) final;

			/**
			 * deletes things
			 */
			virtual void clear() final;

		protected:
			/**
			 * locks that protect the cache line from concurrent access
			 */
			std::vector<std::shared_ptr<std::recursive_mutex>> cache_l;
			std::recursive_mutex l;

			virtual bool in(const std::shared_ptr<T>& arg) final;
			virtual void allocate(const std::shared_ptr<T>& arg) final;
			virtual std::shared_ptr<T> select() final;

			/**
			 * hash arg->get_identity() and returns an index to cache_l
			 */
			virtual identifier index(const std::shared_ptr<T>& arg) = 0;
	};
}

#include "src/templates/concurrentcache.template"

#endif
