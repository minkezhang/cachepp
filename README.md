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

Documentation is currently being added. The root directory for all documentation is at [docs](docs/). The documenation index is found at [docs/index.md](docs/index.md)

#### Quick Resources:

* [index](docs/index.md)
* [beginner's guide](docs/overview.md) (in progress)

	What's the point of `cachepp`? Why would this be useful? A quick overview and links for further reading.

* [applications](docs/applications.md) (in progress)

	A few talked-through examples of how to use `cachepp` in the real world.

* [data structures](docs/api/index.md) (in progress)

	A guide to the API.
	
* [tutorial](docs/tutorial/index.md) (in progress)

	How to start a project -- from creating the appropriate directory hierarchy to developing a cache to testing for correctness and performance.

Contact
----

* [github](https://github.com/cripplet/cachepp.git)
* [gmail](mailto:minke.zhang@gmail.com)
