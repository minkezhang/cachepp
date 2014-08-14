cachepp
====

can't think of a good pun

Overview
----

`cachepp` is a caching framework written in C++, designed for arbitrary eviction schemas and arbitrary data. The framework comes with several examples, a tutorial 
(pending), interface documentation, and **automated correctness and performance testing**. The goal is to provide a framework which is both robust enough to be an 
implementable production library for developers, and flexible enough to be an experimental testbed for researchers and students.

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

Documentation is currently being added. The root directory for all documentation is at [docs](docs/). The documentation index is found at [docs/index.md](docs/index.md)

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
