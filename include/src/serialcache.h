#ifndef _CACHEPP_SERIALCACHE_H
#define _CACHEPP_SERIALCACHE_H

#include <map>
#include <memory>

#include "src/globals.h"
#include "src/line.h"

namespace cachepp {
	/**
	 * This is the base Cache template
	 * 	this is NOT directly callable by the user
	 *	but is meant as a scaffold to quickly build other cache selection schemes
	 *
	 * typename T -- the type of the cache line, subclassed from Line in src/line.h
	 * typename D -- the type of the cache class auxiliary data
	 */
	template <typename T, typename D>
	class SerialCache {
		public:
			SerialCache(identifier size);

			/**
			 * ensures the cache contains T -- that is, T is loaded
			 */
			virtual void acquire(const std::shared_ptr<T>& arg);

			/**
			 * mark that the cache line is no longer in active use
			 */
			virtual void release(const std::shared_ptr<T>& arg);

			/**
			 * clears the cache of all lines
			 */
			void clear();

			/**
			 * updates cache internal tracker
			 */
			virtual void access(const std::shared_ptr<T>& arg, D aux) = 0;

		protected:
			identifier size;

			std::map<identifier, std::shared_ptr<T>> cache;

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
}

/**
 * include template instantiation
 *	cf. http://bit.ly/MQKzaI
 */
#include "src/templates/serialcache.template"

#endif
