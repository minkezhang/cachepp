cachepp
====

Overview
----

This is a caching framework designed so that different caching algorithms can be easily added, and to be flexible enough that the cache itself can store arbitrary data 
(by casting data into a byte vector).

While the supplied `Cache` template is not inherently concurrent, a concurrent instantiation of the template is underway.

Examples are included, but will be more well-documented in the future.

Installation
----

```
git clone https://github.com/cripplet/cachepp.git
cd cachepp
git submodule --init --recursive
make test
```

Updating
----

```
git pull
git submodule foreach --recursive git checkout master
git submodule foreach --recursive git pull
```

Usage
----

```
auto c = MyCache<MyLine>(100);
auto v = std::vector<MyLine> (...);

for(auto i = ...; ...; ++i) {
	// does nothing if the entry is already in the cache
	c.acquire(v.at(i));

	// process data
	v.at(i)->get_data()->...
}

// clear the cache and unloads all cache lines
c.clear();
```

### Line

A `Line` instance represents a cache line to be stored as data inside the `Cache` instantiation. We have decided to implement `Line` as a template, with one template 
parameter `T` representing the checksum type of the data -- that is, a fully instantiated `Line` class would need to also declare the checksum type:

```
class MyLine : Line<T> { ... };
```

The `Line` interface requires the following functions to be implemented:

```
// class-specific methods for loading and unloading the data 
void aux_load();
void aux_unload();

// hash the data into a checksum and returns the result to be processed
template <typename T> T hash();
```

#### Implementation

```
#ifndef MYLINE_H
#define MYLINE_H

// our checksum will hash our data into the char space
class MyLine : Line<char> {
	private:
		// read / write from / to file, perhaps
		virtual void aux_load();
		virtual void aux_unload();

		// add up elements of data and mod by 256
		virtual char hash();
};

#endif
```

See `include/src/simpleline.h` and `src/simpleline.cc` for sample implementations.

### Cache

The `Cache` template implements a selection policy on the internal cache representation. Each selection policy will need to inherit from `Cache` and implement the 
specifics of the selection policy. `Cache` requires two template parameters: `T` the specific instantiated `Line` class (e.g. `MyLine`, `SimpleLine`, etc.), and `D`, an 
auxiliary data structure used to pass additional arguments into `Cache::access`. This second type parameter is necessary in order as a method for more expressive 
allocation policies to learn data usage patterns **without** sacrificing the `Cache` interface.

In short, a fully instantiated `Cache` template will partially instantiate the `Cache` template and pass along the `Line` type `T`:

```
template<typename T>
class MyCache : Cache<T, MyCacheData> { ... };
```

In order to use this cache on data containers of type `MyLine`, the user will need to invoke

```
auto c = MyCache<MyLine>(...);
```

Note that `T` referred to in the `Cache` template **must** subclass `Line`, and therefore **must** indicate a type for the checksum. Failure to do so (`auto c = 
MyCache<NotALine>(...);` will result in most cases a compile-time error, and will result in undefined behavior.

`MyCache` must implement the following functions:

```
// update internal representation to track the relevant access
void access(const std::shared_ptr<T>& arg, D aux);

// select an entry in the internal cache to evict, but does NOT evict
void std::shared_ptr<T> select();

// given that arg is in the cache, give a recommendation on if the given line should be evicted -- 0 indicates the line should NOT be evicted
size_t heuristic(const std::shared_ptr<T>& arg);
```

#### Implementation

```
#ifndef MYCACHE_H
#define MYCACHE_H

class MyCacheData {};

template <typename T>
class MyCache : public cachepp::Cache<T, MyCacheData> {
	public:
		virtual void access(const std::shared_ptr<T>& arg, MyCacheData aux = MyCacheData());
	// ...
}

// must include the file where the functions are explicitly defined
#include "mycache.template"

#endif
```

Note that because the resulting concrete `Cache` end-product is still a **template**, the file which actually contains the function definitions will need to be 
**included** in the `.h` file, and **not** compiled.

This is in contrast to `Line` instances, which will result in **concrete classes** and therefore **will** need to be compiled (`.cc`).

See `include/src/simplecache.h` and `include/src/simplecache.template` for sample implementations.

Contact
----

* [github](https://github.com/cripplet/cachepp.git)
* [gmail](mailto:minke.zhang@gmail.com)
