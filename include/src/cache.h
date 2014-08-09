#ifndef _CACHE_H
#define _CACHE_H

#include <map>
#include <memory>
#include <mutex>
#include <vector>

namespace cachepp {
	// number of unique IDs supported by the cache
	typedef uint32_t identifier;

	template <typename T>
	/**
	 * Basic cache class -- this is NOT directly usable by the user, but is meant as a scaffold to quickly build other cache selection schemes
	 */
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
			virtual void access(const std::shared_ptr<T>& arg);

		private:
			identifier size;

			std::map<identifier, std::shared_ptr<T>> cache;
			std::recursive_mutex l;

			bool in(const std::shared_ptr<T>& arg);
			void allocate(const std::shared_ptr<T>& arg);

			virtual std::shared_ptr<T> select();

			virtual size_t heuristic(const std::shared_ptr<T>& arg);
	};

	/**
	 * essentially a clock algorithm WITHOUT the persistent hand -- uses Cache::Cache::select, which iterates from the beginning of cache on each invocation
	 */
	template<typename T>
	class SimpleNChanceCache : public Cache<T> {
		public:
			SimpleNChanceCache(identifier size);
		private:
			std::vector<size_t> access_data;
			virtual identifier hash(const std::shared_ptr<T>& arg);

			virtual size_t heuristic(const std::shared_ptr<T>&arg);
	};
}

#endif
