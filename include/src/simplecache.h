#ifndef _CACHEPP_SIMPLECACHE_H
#define _CACHEPP_SIMPLECACHE_H

#include <vector>

#include "src/cache.h"
#include "src/globals.h"

namespace cachepp {
	class SimpleCacheData {};
	/**
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

			virtual identifier index(const std::shared_ptr<T>& arg);

			virtual size_t heuristic(const std::shared_ptr<T>& arg);
	};
}

#include "src/simplecache.template"

#endif
