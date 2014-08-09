#ifndef _CACHEPP_CACHE_H
#define _CACHEPP_CACHE_H

#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "src/globals.h"

#include "src/line.h"

/**
 * cache scaffolding headers
 */

namespace cachepp {
	/**
	 * Basic cache class -- this is NOT directly usable by the user, but is meant as a scaffold to quickly build other cache selection schemes
	 */
	template <typename T>
	class Cache {
		public:
			Cache(identifier size);

			/**
			 * ensures the cache contains T -- that is, T is loaded
			 */
			void acquire(const std::shared_ptr<T>& arg);

			/**
			 * updates cache internal tracker
			 */
			virtual void access(const std::shared_ptr<T>& arg) = 0;

		protected:
			identifier size;

			std::map<identifier, std::shared_ptr<T>> cache;
			std::recursive_mutex l;

			bool in(const std::shared_ptr<T>& arg);
			void allocate(const std::shared_ptr<T>& arg);

			virtual std::shared_ptr<T> select();

			/**
			 * takes in a cache line and returns a recommendation on if the line should be evicted
			 *	return value of 0 indicates the line should NOT be evicted
			 *
			 * by default, not implemented and will need to be overridden
			 */
			virtual size_t heuristic(const std::shared_ptr<T>& arg) = 0;
	};

	/**
	 * essentially a clock algorithm WITHOUT the persistent hand -- uses Cache::Cache::select, which iterates from the beginning of cache on each invocation
	 */
	template <typename T>
	class SimpleNChanceCache : public Cache<T> {
		public:
			SimpleNChanceCache(identifier size);
			virtual void access(const std::shared_ptr<T>& arg);

		private:
			std::vector<size_t> access_data;
			virtual identifier hash(const std::shared_ptr<T>& arg);

			virtual size_t heuristic(const std::shared_ptr<T>& arg);
	};
}

/**
 * include template instantiation
 *	cf. http://bit.ly/MQKzaI
 */
#include "src/cache.tpp"

#endif
