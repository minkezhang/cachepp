Implementing the Cache
====

Our first order of business is checking out what are the functions we need to implement to fulfill the interface. Let us take a look both at the raw header file 
[cacheinterface.h](../../include/src/cacheinterface.h) and the [API documentation](../api/cacheinterface.md):

```cpp
template <typename C, typename D, typename T>
class CacheInterface {
	public:
		virtual void acquire(...) = 0;
		virtual void release(...) = 0;
		virtual void clear() = 0;
		virtual void remove(...) = 0;
	private:
		virtual void access(...) = 0;
		virtual ... in(...) = 0;
		virtual void allocate(...) = 0;
		virtual ... select() = 0;
		virtual ... heuristic(...) = 0;
};
```

We decide that for this cache, we store all data `T` in a queue (`C`); since this is an LRU cache, we will not need any auxiliary data, so we will create an empty class 
`LRUCacheData` (`D`). Our header file as of now (see [simpleserialcache.h](../../include/src/simpleserialcache.h) for similar implementation, and 
[lru.h](../../refs/lru.h) for source file):

```cpp
/* /include/src/lru.h */

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <memory>
#include <vector>

#include "libs/cachepp/cacheinterface.h"
#include "libs/cachepp/globals.h"

class LRUCacheData {};

template <typename T>
class LRUCache : public cachepp::CacheInterface<...> {
	public:
		LRUCache(...);

		virtual void acquire(...) final;
		...

	private:

		virtual void access(...) final;
		...
};

#include "src/templates/lru.tpp"

#endif
```

Note that we have an additional `#include` statement at the end of the header -- if you wish to define the functions externally, you will need to add this at the end of 
the header file so that the compiler will know where to look for the function definitions.

Let us take a look at the documentation for `CacheInterface::heuristic` in the [API](../api/cacheinterface.md): we see that we do **not** necessarily need to implement 
this function if our cache does not call for it. We decide that, as we are in an LRU schema, we can skip this. (Note that it is also possible to write an LRU cache 
*with* this function implemented as well, but we have decided not to in this case just as an example.)

In `/include/src/templates/lru.tpp` then, we will add the constructor and the empty `heuristic` function (see 
[simpleserialcache.template](../../include/src/templates/simpleserialcache.template) for similar implementation and [lru.tpp](../../refs/lru.tpp) for source file):

```cpp
/* /include/src/templates/lru.tpp */

#ifndef LRUCACHE_TEMPLATE
#define LRUCACHE_TEMPLATE

#include <memory>
#include <vector>

#include "libs/cachepp/cacheinterface.h"
#include "libs/cachepp/globals.h"
#include "libs/exceptionpp/exception.h"

#include "src/lru.h"

template <typename T> LRUCache<T>::LRUCache(size) : cachepp::CacheInterface<...>::CacheInterface(size, false) {}

template <typename T> ... LRUCache<T>::heuristic(arg) { throw(exceptionpp::NotImplemented("LRUCache::heuristic")); }
template <typename T> void LRUCache<T>::release(arg) { throw(exceptionpp::NotImplemented("LRUCache::release")); }

#endif
```

The second argument in the `CacheInterface` constructor indicates this cache was **not** designed to be thread-safe. Note that we have added an (programmer's preference) 
exception in `LRUCache::heuristic` and `LRUCache::release` rather than opting for an empty function -- this will allow us to realize readily that this `heurisitic` will 
*not* be supported in `LRUCache` in the case of accidental invocation.

**NB** Keep in mind that the state of the cache at the destruction of the object **is not necessarily consistent with saved data** -- we do not require this consistency 
as part of the API due to the fact that this may be *undesirable* behavior. To ensure a call to save the data at destruction, add a call to `this->clear` at the 
destructor. Note that this can only be called in a class in which `CacheInterface::clear` is **not** a pure virtual function, due to the way in which destructors work in C++.

Let us consider `LRUCache::select`: according to the API, this will select an internal cache line and return that as the candidate to be evicted. As this is an LRU 
cache, we will model "least recent" as the head of the queue:

```cpp
template <typename T> ... LRUCache<T>::select() { return(this->cache.at(0)); }

template <typename T> void LRUCache<T>::remove(arg) {
	for(size_t i = 0; i < this->cache.size(); ++i) {
		if(this->cache.at(i) == arg) {
			this->cache.at(i)->unload();
			this->cache.erase(this->cache.begin() + i);
			return;
		}
	}
}

template <typename T> void LRUCache<T>::clear() {
	while(this->cache.size() != 0) {
		this->remove(this->cache.at(0));
	}
}

template <typename T> ... LRUCache<T>::in(arg) { return(arg->get_is_loaded()); }
```

We see that `LRUCache::remove`, `LRUCache::in`, and `LRUCache::clear` are straightforward queue iterating operators (this toy implementation uses a vector, but the idea 
is the same).

Next, let us consider implementing `CacheInterface::access` -- since this is an LRU cache, we will simply need to push the relevant element to the end of the queue:

```cpp
template <typename T> void LRUCache<T>::access(arg, aux) {
	for(size_t i = 0; i < this->cache.size(); ++i) {
		if(this->cache.at(i)->get_identifier() == arg->get_identifier()) {
			this->cache.erase(this->cache.begin() + i);
			break;
		}
	}
	this->cache.push_back(arg);
}
```

Finally, with all these tools, we can write `LRUCache::allocate` and `LRUCache::acquire`:

```cpp
template <typename T> void LRUCache<T>::allocate(arg) {
	if(this->cache.size() > this->get_size()) {
		this->remove(this->select());
	}
	arg->load();
	this->cache.push_back(arg);
}

template <typename T> void LRUCache<T>::acquire(arg, aux) {
	this->n_acquire++;
	if(!this->in(arg)) {
		this->n_miss++;
		this->allocate(arg);
	}
	this->access(arg, aux);
}
```

And we're done!

Further Reading
----

* Prev -- [Setting Up](intro.md)
* Next -- [Implementing the Line Interface](line.md)
