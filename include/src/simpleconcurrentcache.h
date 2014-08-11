#ifndef _CACHEPP_SIMPLECONCURRENTCACHE_H
#define _CACHEPP_SIMPLECONCURRENTCACHE_H

#include <memory>
#include <vector>

#include "src/concurrentcache.h"
#include "src/globals.h"

namespace cachepp {
	class SimpleConcurrentCacheData {};

	template <typename T>
	class SimpleConcurrentCache : public ConcurrentCache<SimpleConcurrentCacheData, T> {
		public:
			SimpleConcurrentCache(identifier size);

		private:
			std::vector<size_t> access_data;

			virtual identifier index(const std::shared_ptr<T>& arg);
			virtual size_t heuristic(const std::shared_ptr<T>& arg);
			virtual void access(const std::shared_ptr<T>& arg, SimpleConcurrentCacheData aux);
	};
}

#include "src/templates/simpleconcurrentcache.template"

#endif
