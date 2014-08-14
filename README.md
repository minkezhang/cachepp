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
git submodule update --init --recursive
make test
```

Updating
----

```
git pull
git submodule foreach --recursive git checkout master
git submodule foreach --recursive git pull
```

Documentation
----

Documentation is currently being added. The root directory for docs is at [docs](docs/).

* [table of contents](docs/index.md)
* [data structures] (in progress)
* [tutorial] (in progress)

Contact
----

* [github](https://github.com/cripplet/cachepp.git)
* [gmail](mailto:minke.zhang@gmail.com)
