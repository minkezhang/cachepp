cachepp
====

can't think of a good pun

Overview
----

`cachepp` is a caching **framework** written in C++, designed for easy creation of caches with arbitrary eviction schemas and storing arbitrary data. The framework comes 
with several examples, a [tutorial](docs/tutorial/index.md) (pending), interface [api documentation](docs/api/index.md), and **automated correctness and performance 
testing**. The goal is to provide a framework which is both robust enough to be used in a production library for developers, and flexible enough to be an experimental 
testbed for researchers and students.

Installation
----

```bash
git clone https://github.com/cripplet/cachepp.git
cd cachepp
git submodule update --init --recursive
make test # this will take a while
```

Updating
----

```bash
git pull
git submodule foreach --recursive git checkout master
git submodule foreach --recursive git pull
```

Documentation
----

Documentation is currently being added. The root directory for all documentation is at [docs](docs/). The documentation index is found at [docs/index.md](docs/index.md)

### Quick Links

* [index](docs/index.md)
* [beginner's guide](docs/overview.md) -- start here
* [applications](docs/applications.md) -- a few talked-through examples of how to use `cachepp` in the real world
* [api](docs/api/index.md) -- a guide to the API
* [tutorial](docs/tutorial/index.md) (in progress) -- how to start a project, from creating the appropriate directory hierarchy to developing a cache to testing for
	correctness and performance

Contact
----

* [github](https://github.com/cripplet/cachepp.git)
* [gmail](mailto:minke.zhang@gmail.com)
* issues and feature requests should be directed to the project [issues](https://github.com/cripplet/cachepp/issues) page
