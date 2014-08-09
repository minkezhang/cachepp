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

### `class Cache<T>`

### `class Line`

Contact
----

* [github](https://github.com/cripplet/cachepp.git)
* [gmail](mailto:minke.zhang@gmail.com)
