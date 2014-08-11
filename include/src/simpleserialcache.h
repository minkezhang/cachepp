#ifndef _CACHEPP_SIMPLESERIALCACHE_H
#define _CACHEPP_SIMPLESERIALCACHE_H

#include <vector>

#include "src/serialcache.h"
#include "src/globals.h"

namespace cachepp {
	class SimpleSerialCacheData {};
	/**
	 * SimpleSerialCache implements a partially instantiated Cache template
	 *	this is DIRECTLY callable by the user to be used as a cache
	 *
	 * essentially a clock algorithm WITHOUT the persistent hand
	 *	uses Cache::Cache::select, which iterates from the beginning of cache on each invocation
	 *
	 * compare with an n-chance algorithm
	 */
	template <typename T>
	class SimpleSerialCache : public SerialCache<SimpleSerialCacheData, T> {
		public:
			SimpleSerialCache(identifier size);

		private:
			std::vector<size_t> access_data;

			virtual identifier index(const std::shared_ptr<T>& arg);
			virtual size_t heuristic(const std::shared_ptr<T>& arg);
			virtual void access(const std::shared_ptr<T>& arg, SimpleSerialCacheData aux);
	};
}

#include "src/templates/simpleserialcache.template"

#endif
