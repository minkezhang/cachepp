#ifndef _CACHEPP_SIMPLECACHE_H
#define _CACHEPP_SIMPLECACHE_H

#include <vector>

#include "src/serialcache.h"
#include "src/globals.h"

namespace cachepp {
	class SimpleCacheData {};
	/**
	 * SimpleCache implements a partially instantiated Cache template
	 *	this is DIRECTLY callable by the user to be used as a cache
	 *
	 * essentially a clock algorithm WITHOUT the persistent hand
	 *	uses Cache::Cache::select, which iterates from the beginning of cache on each invocation
	 *
	 * compare with an n-chance algorithm
	 */
	template <typename T>
	class SimpleCache : public Cache<T, SimpleCacheData> {
		public:
			SimpleCache(identifier size);

			virtual void access(const std::shared_ptr<T>& arg, SimpleCacheData aux = SimpleCacheData());

		private:
			std::vector<size_t> access_data;

			identifier index(const std::shared_ptr<T>& arg);
			virtual size_t heuristic(const std::shared_ptr<T>& arg);
	};
}

#include "src/templates/simplecache.template"

#endif
