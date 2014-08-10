#ifndef _CACHEPP_CACHEINTERFACE_H
#define _CACHEPP_CACHEINTERFACE_H

#include <map>
#include <memory>

#include "src/globals.h"
#include "src/line.h"

namespace cachepp {
	/**
	 * This is the base Cache interface template
	 * 	this is NOT directly callable by the user
	 *	but is meant as a scaffold to quickly build other cache selection schemes
	 *
	 * typename T -- the type of the cache line, subclassed from Line in src/line.h
	 * typename D -- the type of the cache class auxiliary data
	 * typename C -- the internal cache type representation
	 */
	template <typename T, typename D, typename C>
	class CacheInterface {
		public:
			/**
			 * ensures the cache contains T -- that is, T is loaded
			 */
			virtual void acquire(const std::shared_ptr<T>& arg) = 0;

			/**
			 * mark that the cache line is no longer in active use
			 */
			virtual void release(const std::shared_ptr<T>& arg) = 0;

			/**
			 * clears the cache of all lines
			 */
			virtual void clear() = 0;

			/**
			 * updates cache internal tracker
			 */
			virtual void access(const std::shared_ptr<T>& arg, D aux) = 0;

		protected:
			identifier size;
			C cache;

			virtual bool in(const std::shared_ptr<T>& arg) = 0;
			virtual void allocate(const std::shared_ptr<T>& arg) = 0;

			virtual std::shared_ptr<T> select() = 0;

			/**
			 * takes in a cache line and returns a recommendation on if the line should be evicted
			 *	return value of 0 indicates the line should NOT be evicted
			 *
			 * by default, not implemented and will need to be overridden
			 */
			virtual size_t heuristic(const std::shared_ptr<T>& arg) = 0;
	};
}

#endif
