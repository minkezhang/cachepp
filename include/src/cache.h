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
	class Cache {
		public:
			Cache(identifier size);

			/**
			 * ensures the cache contains T -- that is, T is loaded
			 */
			void acquire(const std::shared_ptr<Line>& arg);

			/**
			 * updates cache internal tracker
			 */
			virtual void access(const std::shared_ptr<Line>& arg) = 0;

		protected:
			identifier size;

			std::map<identifier, std::shared_ptr<Line>> cache;
			std::recursive_mutex l;

			bool in(const std::shared_ptr<Line>& arg);
			void allocate(const std::shared_ptr<Line>& arg);

			virtual std::shared_ptr<Line> select();

			/**
			 * takes in a cache line and returns a recommendation on if the line should be evicted
			 *	return value of 0 indicates the line should NOT be evicted
			 *
			 * by default, not implemented and will need to be overridden
			 */
			virtual size_t heuristic(const std::shared_ptr<Line>& arg) = 0;
	};

	/**
	 * essentially a clock algorithm WITHOUT the persistent hand -- uses Cache::Cache::select, which iterates from the beginning of cache on each invocation
	 */
	class SimpleNChanceCache : public Cache {
		public:
			SimpleNChanceCache(identifier size);
		private:
			std::vector<size_t> access_data;
			virtual identifier hash(const std::shared_ptr<Line>& arg);

			virtual size_t heuristic(const std::shared_ptr<Line>& arg);
	};
}

#endif
