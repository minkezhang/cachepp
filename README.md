cachepp
====

Overview
----

This is a **lightly** concurrent (i.e., coarse-grained locking mechanism) caching framework, in the same sense of "cache" as paging, L1, etc. This framework is designed 
so that different caching algorithms can be easily added, and to be flexible enough that the cache itself can store arbitrary data (by casting data into a byte vector).

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

### Cache

The `Cache` template implements a selection policy on the internal cache representation. Each selection policy will need to inherit from `Cache` and implement the specifics of the selection policy. The following functions will need to be implemented:

```
// update internal representation to track the relevant access
void access(const std::shared_ptr<T>& arg);

// select an entry in the internal cache to evict, but does NOT evict
void std::shared_ptr<T> select();

// given that arg is in the cache, give a recommendation on if the given line should be evicted -- 0 indicates the line should NOT be evicted
size_t heuristic(const std::shared_ptr<T>& arg);
```

All instantiated types of the `Cache` template (i.e., all possible `T` when calling `Cache<T>`) **must** inherit from `Line` to guarantee the standard interface. If `T` does not inherit `Line`, an `exceptionpp::InvalidOperation` will be thrown upon cache initialization.

#### Implementation

```
#ifndef MYCACHE_H
#define MYCACHE_H

template <typename T>
class MyCache : public cachepp::Cache<T> {
  // header declarations here
}

// must include the file where the functions are explicitly defined
#include "mycache.template"

#endif
```

See `include/src/simplecache.h` and `include/src/simplecache.template` for sample implementations.

### Line

All classes which inherits the `Line` interface (and therefore guarantees the functionality contained in the `Line` declaration) can be instantiated in the `Cache` template. That is, given `class MyLine : public Line`, `Cache<MyLine>` is automatically supported. The following functions will be need to be implemented:

```
// set the internal hash -- type is not tracked by Line
void set_hash();

// class-specific methods for loading and unloading the data 
void load_aux();
void unload_aux();

// checks if the checksum matches the hash
bool checksum_aux();
```

See `include/src/simpleline.h` and `src/simpleline.cc` for sample implementations.

Contact
----

* [github](https://github.com/cripplet/cachepp.git)
* [gmail](mailto:minke.zhang@gmail.com)
