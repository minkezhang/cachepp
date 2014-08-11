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
	 * typename C -- the internal cache type representation
	 * typename D -- the type of the cache class auxiliary data
	 * typename T -- the type of the cache line, subclassed from Line in src/line.h
	 */
	template <typename C, typename D, typename T>
	class CacheInterface {
		public:
			CacheInterface();

			/**
			 * ensures the cache contains T -- that is, T is loaded
			 */
			virtual void acquire(const std::shared_ptr<T>& arg) = 0;

			/**
			 * mark that the cache line is no longer in active use
			 */
			virtual void release(const std::shared_ptr<T>& arg) = 0;

			/**
			 * clears the cache of all lines which existed at the beginning of the call
			 */
			virtual void clear() = 0;

			/**
			 * updates cache internal tracker
			 */
			virtual void access(const std::shared_ptr<T>& arg, D aux) = 0;

			/**
			 * returns n_miss / n_acquire, or returns a RuntimeError if a divide-by-zero occurs
			 */
			identifier get_miss_rate();

		protected:
			identifier size;
			C cache;

			/**
			 * optional performance tracker objects
			 */
			std::atomic<identifier> n_acquire;
			std::atomic<identifier> n_miss;

			/**
			 * test for if the given arg is in the cache
			 */
			virtual bool in(const std::shared_ptr<T>& arg) = 0;

			/**
			 * allocates the input arg within the cache
			 */
			virtual void allocate(const std::shared_ptr<T>& arg) = 0;

			/**
			 * selection policy of the cache -- returns a line from the cache which MUST be evicted
			 */
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

#include "src/templates/cacheinterface.template"

#endif
