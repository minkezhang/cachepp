#ifndef _CACHE_H
#define _CACHE_H

#include <map>
#include <memory>
#include <mutex>

namespace cachepp {
	// number of unique IDs supported by the cache
	typedef uint32_t identifier;
	template <typename T>
	class Cache {
		public:
			Cache(identifier size);

			/**
			 * ensures the cache contains T -- that is, T is loaded
			 */
			void acquire(const std::shared_ptr<T>& arg);

		private:
			identifier size;

			std::map<identifier, std::shared_ptr<T>> cache;
			std::recursive_mutex l;

			bool in(const std::shared_ptr<T>& arg);
			void allocate(const std::shared_ptr<T>& arg);

			std::shared_ptr<T> select();

			virtual size_t heuristic(const std::shared_ptr<T>& arg);
			virtual identifier hash(const std::shared_ptr<T>& arg);
	};
}

#endif
